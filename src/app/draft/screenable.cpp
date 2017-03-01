#include "app/screenable.h"
#include "core/debug.h"

Screenable::Screenable()
{
}

Screenable::~Screenable()
{
    //Let the smart pointer delete all assets before the OpenGL context is destroyed
    _scene = NULL;
    _assetsFactory = NULL;
    _assetsStorage = NULL;
}

void Screenable::init()
{
    _assetsStorage = std::make_shared<AssetsStorage>();
    _assetsFactory = std::make_shared<AssetsFactory>(_assetsStorage);

    std::cout << "Shader phong" << std::endl;
    _assetsFactory->importShader("../resources/shaders/phong.vert",
                                 "../resources/shaders/phong.frag");
    _assetsFactory->createNewShaderStrategy(0, "phong");

    std::cout << "Shader skybox" << std::endl;
    _assetsFactory->importShader("../resources/shaders/skybox.vert",
                                 "../resources/shaders/skybox.frag");
    _assetsFactory->createNewShaderStrategy(1, "skybox");

    std::cout << "Shader environment" << std::endl;
    _assetsFactory->importShader("../resources/shaders/environmentmap.vert",
                                 "../resources/shaders/environmentmap.frag");
    _assetsFactory->createNewShaderStrategy(2, "environmentmap");

    std::cout << "Shader shader" << std::endl;
    _assetsFactory->importShader("../resources/shaders/shader.vert",
                                 "../resources/shaders/shader.frag");
    _assetsFactory->createNewShaderStrategy(3, "gouraud");

    std::cout << "Shader toon" << std::endl;
    _assetsFactory->importShader("../resources/shaders/toon.vert",
                                 "../resources/shaders/toon.frag");
    _assetsFactory->createNewShaderStrategy(4, "toon");

    std::cout << "Shader edge" << std::endl;
    _assetsFactory->importShader("../resources/shaders/edgefilter.vert",
                                 "../resources/shaders/edgefilter.frag");
    _assetsFactory->createNewScreenSpaceShaderStrategy(EDGEFILTER, 5, "edgeFilter");

    std::cout << "Shader gaussian" << std::endl;
    _assetsFactory->importShader("../resources/shaders/edgefilter.vert",
                                 "../resources/shaders/verticalgaussianblurfilter.frag");
    _assetsFactory->createNewScreenSpaceShaderStrategy(GAUSSIANBLURFILTER, 6,
                                                       "verticalGaussianBlur");

    std::cout << "Shader gaussian" << std::endl;
    _assetsFactory->importShader("../resources/shaders/edgefilter.vert",
                                 "../resources/shaders/horizontalgaussianblurfilter.frag");
    _assetsFactory->createNewScreenSpaceShaderStrategy(GAUSSIANBLURFILTER, 7,
                                                       "horizontalGaussianBlur");

    _assetsFactory->importTexture("../resources/images/Texture/dice.jpg", "dice");
    _assetsFactory->importTexture("../resources/images/Texture/Minion.png", "minion");
    _assetsFactory->importTexture("../resources/images/Texture/Mozart.png", "mozart");
    _assetsFactory->importCubeMapTexture("../resources/images/Skybox/space_", "space");
    _assetsFactory->importCubeMapTexture("../resources/images/Skybox/sky_", "sky");

    _assetsFactory->importMeshs("../resources/meshes/minion.obj");
    _assetsFactory->importMeshs("../resources/meshes/mozart.obj");

    _scene = std::make_shared<Scene>(_assetsStorage);
    _scene->setIsReady(true);

    _renderer = std::make_shared<Renderer>();
}

