#include "app/nanogui/app.h"

void App::init()
{
    _screenView = new ScreenView();

    _screenView->drawAll();
    _screenView->setVisible(true);
}

void App::initAssets()
{
    _assets = std::make_shared<Assets>();

    std::cout << "Shader phong" << std::endl;
    std::shared_ptr<ShaderWrapper> shaderWrapper;
    shaderWrapper = AssetsFactory::instance().importShader("../resources/shaders/phong.vert",
                                 "../resources/shaders/phong.frag");
    _assets->addShaderWrapper(shaderWrapper);
    _assets->addShaderStrategy(AssetsFactory::instance().createShaderStrategy(shaderWrapper, "Phong"));

    std::cout << "Shader skybox" << std::endl;
    shaderWrapper = AssetsFactory::instance().importShader("../resources/shaders/skybox.vert",
                                 "../resources/shaders/skybox.frag");
    _assets->addShaderWrapper(shaderWrapper);
    _assets->addShaderStrategy(AssetsFactory::instance().createShaderStrategy(shaderWrapper, "Skybox"));

    std::cout << "Shader environment" << std::endl;
    shaderWrapper = AssetsFactory::instance().importShader("../resources/shaders/environmentmap.vert",
                                 "../resources/shaders/environmentmap.frag");
    _assets->addShaderWrapper(shaderWrapper);
    _assets->addShaderStrategy(AssetsFactory::instance().createShaderStrategy(shaderWrapper, "Environment"));

    std::cout << "Shader gouraud" << std::endl;
    shaderWrapper = AssetsFactory::instance().importShader("../resources/shaders/shader.vert",
                                 "../resources/shaders/shader.frag");
    _assets->addShaderWrapper(shaderWrapper);
    _assets->addShaderStrategy(AssetsFactory::instance().createShaderStrategy(shaderWrapper, "Gouraud"));

    std::cout << "Shader toon" << std::endl;
    shaderWrapper = AssetsFactory::instance().importShader("../resources/shaders/toon.vert",
                                 "../resources/shaders/toon.frag");
    _assets->addShaderWrapper(shaderWrapper);
    _assets->addShaderStrategy(AssetsFactory::instance().createShaderStrategy(shaderWrapper, "Toon"));
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
    _assets->addTexture(texture2D);
    texture2D = AssetsFactory::instance().importTexture("../resources/images/Texture/Minion.png", "minion");
    _assets->addTexture(texture2D);
    texture2D = AssetsFactory::instance().importTexture("../resources/images/Texture/Mozart.png", "mozart");
    _assets->addTexture(texture2D);
    texture2D = AssetsFactory::instance().importCubeMapTexture("../resources/images/Skybox/space_", "space");
    _assets->addTexture(texture2D);
    texture2D = AssetsFactory::instance().importCubeMapTexture("../resources/images/Skybox/sky_", "sky");
    _assets->addTexture(texture2D);

    _assets->addMesh(Mesh::createSquare("Square"));
    _assets->addMesh(Mesh::createCube(1, "Cube"));
    _assets->addMesh(Mesh::createSphere(8, "Sphere"));
    _assets->addMesh(Mesh::createCylinder(8, "Cylinder"));

    std::shared_ptr<Mesh> mesh;
    mesh = AssetsFactory::instance().importMeshs("../resources/meshes/minion.obj");
    _assets->addMesh(mesh);
    mesh = AssetsFactory::instance().importMeshs("../resources/meshes/mozart.obj");
    _assets->addMesh(mesh);
}

