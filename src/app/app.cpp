#include "app/app.h"
#include "model/assetsfactory.h"

#include <nanogui/layout.h>

void App::init()
{
    //Init Screen presenter
    _screenPresenter = std::make_shared<ScreenPresenter>();

    _screenView = new ScreenView();
    _screenPresenter->setScreenView(_screenView);

    //Init Canvas presenter
    _canvasPresenter = std::make_shared<CanvasPresenter>(_screenPresenter);
    _screenPresenter->addChildPresenter(_canvasPresenter);

    _canvasWindow = new nanogui::Window(_screenView.get(), "Canvas");
    _canvasWindow->setPosition(Eigen::Vector2i(300, 0));
    _canvasWindow->setFixedSize(Eigen::Vector2i(600, 600));
    _canvasWindow->setLayout(new nanogui::GroupLayout());

    nanogui::ref<CanvasView> canvasView = new CanvasView(_canvasWindow.get(), 600, 550);
    _canvasPresenter->setCanvasView(canvasView);

    //Init Universe presenter
    _universePresenter = std::make_shared<UniversePresenter>(_screenPresenter);
    _screenPresenter->addChildPresenter(_universePresenter);
    nanogui::ref<View> view = new View(_screenView.get(), "Universe");
    _universePresenter->setView(view);

    //Init RenderableObject presenter
    _renderableObjectPresenter = std::make_shared<RenderableObjectPresenter>(_screenPresenter);
    _screenPresenter->addChildPresenter(_renderableObjectPresenter);
    view = new View(_screenView.get(), "Renderable Object");
    _renderableObjectPresenter->setView(view);

    //Init App

    initUniverse();
    initScene();

    _canvasPresenter->setUniverse(_universe);
    _universePresenter->setUniverse(_universe);
    _renderableObjectPresenter->setUniverse(_universe);

    _canvasPresenter->init();
    _universePresenter->init();
    _renderableObjectPresenter->init();

    _screenPresenter->init();
}

void App::initUniverse()
{
    _universe = std::make_shared<Universe>();

    std::cout << "Shader phong" << std::endl;
    std::shared_ptr<ShaderWrapper> shaderWrapper;
    shaderWrapper = AssetsFactory::instance().importShader("../resources/shaders/phong.vert",
                                 "../resources/shaders/phong.frag");
    _universe->addShaderWrapper(shaderWrapper);
    _universe->addShaderStrategy(AssetsFactory::instance().createShaderStrategy(shaderWrapper, "Phong"));

    std::cout << "Shader skybox" << std::endl;
    shaderWrapper = AssetsFactory::instance().importShader("../resources/shaders/skybox.vert",
                                 "../resources/shaders/skybox.frag");
    _universe->addShaderWrapper(shaderWrapper);
    _universe->addShaderStrategy(AssetsFactory::instance().createShaderStrategy(shaderWrapper, "Skybox"));

    std::cout << "Shader environment" << std::endl;
    shaderWrapper = AssetsFactory::instance().importShader("../resources/shaders/environmentmap.vert",
                                 "../resources/shaders/environmentmap.frag");
    _universe->addShaderWrapper(shaderWrapper);
    _universe->addShaderStrategy(AssetsFactory::instance().createShaderStrategy(shaderWrapper, "Environment"));

    std::cout << "Shader gouraud" << std::endl;
    shaderWrapper = AssetsFactory::instance().importShader("../resources/shaders/shader.vert",
                                 "../resources/shaders/shader.frag");
    _universe->addShaderWrapper(shaderWrapper);
    _universe->addShaderStrategy(AssetsFactory::instance().createShaderStrategy(shaderWrapper, "Gouraud"));

    std::cout << "Shader toon" << std::endl;
    shaderWrapper = AssetsFactory::instance().importShader("../resources/shaders/toon.vert",
                                 "../resources/shaders/toon.frag");
    _universe->addShaderWrapper(shaderWrapper);
    _universe->addShaderStrategy(AssetsFactory::instance().createShaderStrategy(shaderWrapper, "Toon"));
/*
    std::cout << "Shader edge" << std::endl;
    shaderWrapper = AssetsFactory::instance().importShader("../resources/shaders/edgefilter.vert",
                                 "../resources/shaders/edgefilter.frag");
    AssetsFactory::instance().createNewScreenSpaceShaderStrategy(EDGEFILTER, 5, "edgeFilter");

    std::cout << "Shader gaussian" << std::endl;
    shaderWrapper = AssetsFactory::instance().importShader("../resources/shaders/edgefilter.vert",
                                 "../resources/shaders/verticalgaussianblurfilter.frag");
    AssetsFactory::instance().createNewScreenSpaceShaderStrategy(GAUSSIANBLURFILTER, 6,
                                                       "verticalGaussianBlur");

    std::cout << "Shader gaussian" << std::endl;
    shaderWrapper = AssetsFactory::instance().importShader("../resources/shaders/edgefilter.vert",
                                 "../resources/shaders/horizontalgaussianblurfilter.frag");
    AssetsFactory::instance().createNewScreenSpaceShaderStrategy(GAUSSIANBLURFILTER, 7,
                                                       "horizontalGaussianBlur");
*/

    std::shared_ptr<DDTexture> texture2D;
    texture2D = AssetsFactory::instance().importTexture("../resources/images/Texture/dice.jpg", "dice");
    _universe->addTexture(texture2D);
    texture2D = AssetsFactory::instance().importTexture("../resources/images/Texture/Minion.png", "minion");
    _universe->addTexture(texture2D);
    texture2D = AssetsFactory::instance().importTexture("../resources/images/Texture/Mozart.png", "mozart");
    _universe->addTexture(texture2D);

    std::shared_ptr<CubeTexture> textureCube;
    textureCube = AssetsFactory::instance().importCubeMapTexture("../resources/images/Skybox/space_", "space");
    _universe->addCubeTexture(textureCube);
    textureCube = AssetsFactory::instance().importCubeMapTexture("../resources/images/Skybox/sky_", "sky");
    _universe->addCubeTexture(textureCube);

    _universe->addMesh(Mesh::createSquare("Square"));
    _universe->addMesh(Mesh::createCube(1, "Cube"));
    //_universe->addMesh(Mesh::createSphere(8, "Sphere"));
    //_universe->addMesh(Mesh::createCylinder(8, "Cylinder"));

    std::shared_ptr<Mesh> mesh;
    mesh = AssetsFactory::instance().importMeshs("../resources/meshes/minion.obj")[0];
    _universe->addMesh(mesh);
    mesh = AssetsFactory::instance().importMeshs("../resources/meshes/mozart.obj")[0];
    _universe->addMesh(mesh);
}

void App::initScene()
{
    _scene = std::make_shared<Scene>();
    _scene->build(*_universe);

    _universe->addScene(_scene);
    _universe->setCurrentScene(_scene);

}
