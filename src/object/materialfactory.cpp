#include "object/materialfactory.h"

Material MaterialFactory::createPhongMaterial()
{
    Material m("Phong");

    m.createUniform("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
                    glm::vec4(0.0f, 0.0f, 0.0f, 0.0f),
                    glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    m.createUniform("Ka", glm::vec3(1.0f, 1.0f, 1.0f),
                    glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(1.0f, 1.0f, 1.0f));
    m.createUniform("Kd", glm::vec3(1.0f, 1.0f, 1.0f),
                    glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(1.0f, 1.0f, 1.0f));
    m.createUniform("Ks", glm::vec3(1.0f, 1.0f, 1.0f),
                    glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(1.0f, 1.0f, 1.0f));
    m.createUniform("Ns", 3.0f, 0.5f, 20.0f);

    m.addTexture("colorMap", std::make_shared<Texture>());

    return m;
}

Material MaterialFactory::createRefractionMaterial()
{
    Material m("Refraction");

    m.createUniform("refractionRatio", 0.3f, 0.0f, 1.0f);
    m.createUniform("reflexionRatio", 0.6f, 0.0f, 1.0f);

    m.addTexture("cubeMap", std::make_shared<Texture>());

    return m;
}

Material MaterialFactory::createToonMaterial()
{
    Material m("Toon");

    m.createUniform("levels", 3, 0, 10);

    return m;
}

Material MaterialFactory::createSkyboxMaterial()
{
    Material m("Skybox");

    m.createUniform("Ka", glm::vec3(1.0f, 1.0f, 1.0f),
                    glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(1.0f, 1.0f, 1.0f));

    m.addTexture("cubeMap", std::make_shared<Texture>());

    return m;
}

Material MaterialFactory::createDefaultMaterial()
{
    Material m("Default");

    Material phong = createPhongMaterial();

    m.addMaterial(phong);//It won't work, right ? well it does, but we need to avoid useless copy
    m.addMaterial(createRefractionMaterial());
    m.addMaterial(createToonMaterial());

    return m;
}
