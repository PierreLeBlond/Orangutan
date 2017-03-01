#include "app/nanogui/app.h"
#include "model/assetsfactory.h"

#include <nanogui/layout.h>

void App::init()
{
    _screenView = new ScreenView();


    _windowView = new nanogui::Window(_screenView.get(), "Canvas");
    _windowView->setPosition(Eigen::Vector2i(300, 0));
    _windowView->setFixedSize(Eigen::Vector2i(600, 600));
    _windowView->setLayout(new nanogui::GroupLayout());

    _canvasView = new CanvasView(_windowView.get(), 600, 600);

    _screenView->drawAll();
    _screenView->setVisible(true);

    _canvasView->start();
}

void App::initUniverse()
{
    std::cout << "Shader phong" << std::endl;
    std::shared_ptr<ShaderWrapper> shaderWrapper;
    shaderWrapper = AssetsFactory::instance().importShader("../resources/shaders/phong.vert",
                                 "../resources/shaders/phong.frag");
    _universe.addShaderWrapper(shaderWrapper);
    _universe.addShaderStrategy(AssetsFactory::instance().createShaderStrategy(shaderWrapper, "Phong"));

    std::cout << "Shader skybox" << std::endl;
    shaderWrapper = AssetsFactory::instance().importShader("../resources/shaders/skybox.vert",
                                 "../resources/shaders/skybox.frag");
    _universe.addShaderWrapper(shaderWrapper);
    _universe.addShaderStrategy(AssetsFactory::instance().createShaderStrategy(shaderWrapper, "Skybox"));

    std::cout << "Shader environment" << std::endl;
    shaderWrapper = AssetsFactory::instance().importShader("../resources/shaders/environmentmap.vert",
                                 "../resources/shaders/environmentmap.frag");
    _universe.addShaderWrapper(shaderWrapper);
    _universe.addShaderStrategy(AssetsFactory::instance().createShaderStrategy(shaderWrapper, "Environment"));

    std::cout << "Shader gouraud" << std::endl;
    shaderWrapper = AssetsFactory::instance().importShader("../resources/shaders/shader.vert",
                                 "../resources/shaders/shader.frag");
    _universe.addShaderWrapper(shaderWrapper);
    _universe.addShaderStrategy(AssetsFactory::instance().createShaderStrategy(shaderWrapper, "Gouraud"));

    std::cout << "Shader toon" << std::endl;
    shaderWrapper = AssetsFactory::instance().importShader("../resources/shaders/toon.vert",
                                 "../resources/shaders/toon.frag");
    _universe.addShaderWrapper(shaderWrapper);
    _universe.addShaderStrategy(AssetsFactory::instance().createShaderStrategy(shaderWrapper, "Toon"));
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
    _universe.addTexture(texture2D);
    texture2D = AssetsFactory::instance().importTexture("../resources/images/Texture/Minion.png", "minion");
    _universe.addTexture(texture2D);
    texture2D = AssetsFactory::instance().importTexture("../resources/images/Texture/Mozart.png", "mozart");
    _universe.addTexture(texture2D);

    std::shared_ptr<CubeTexture> textureCube;
    textureCube = AssetsFactory::instance().importCubeMapTexture("../resources/images/Skybox/space_", "space");
    _universe.addCubeTexture(textureCube);
    textureCube = AssetsFactory::instance().importCubeMapTexture("../resources/images/Skybox/sky_", "sky");
    _universe.addCubeTexture(textureCube);

    _universe.addMesh(Mesh::createSquare("Square"));
    _universe.addMesh(Mesh::createCube(1, "Cube"));
    //_universe.addMesh(Mesh::createSphere(8, "Sphere"));
    //_universe.addMesh(Mesh::createCylinder(8, "Cylinder"));

    std::shared_ptr<Mesh> mesh;
    mesh = AssetsFactory::instance().importMeshs("../resources/meshes/minion.obj")[0];
    _universe.addMesh(mesh);
    mesh = AssetsFactory::instance().importMeshs("../resources/meshes/mozart.obj")[0];
    _universe.addMesh(mesh);
}

void App::initScene()
{
    _scene = std::make_shared<Scene>();
    _scene->build(_universe);

    _universe.addScene(_scene);

    _renderer = std::make_unique<Renderer>();

    std::function<void()> drawCall = [&](){
        if(_scene->isReady())
        {
            _scene->animate();
            _scene->update();
            _renderer->draw(*_scene);
        }
    };

    _canvasView->setDrawCall(drawCall);
}
