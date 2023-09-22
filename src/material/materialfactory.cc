#include "material/materialfactory.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>

#include "assimp/material.h"
#include "core/texture/cubetexture.h"
#include "core/texture/texture.h"
#include "material/shaderfactory.h"
#include "texture/texturefactory.h"

namespace orangutan {

const std::unordered_map<
    std::string, std::function<void(const aiMaterial& assimp_material,
                                    const aiMaterialProperty& assimp_property,
                                    Material& material)>>
    properties_map = {
        {"$mat.gltf.pbrMetallicRoughness.metallicFactor",
         [](const aiMaterial& assimp_material,
            const aiMaterialProperty& assimp_property, Material& material) {
           float metalness;
           assimp_material.Get(assimp_property.mKey.C_Str(), 0, 0, metalness);
           material.SetUniform("metalness", metalness);
         }},
        {"$mat.gltf.pbrMetallicRoughness.roughnessFactor",
         [](const aiMaterial& assimp_material,
            const aiMaterialProperty& assimp_property, Material& material) {
           float roughness;
           assimp_material.Get(assimp_property.mKey.C_Str(), 0, 0, roughness);
           material.SetUniform("roughness", roughness);
         }}};

std::unique_ptr<Material> MaterialFactory::CreatePbrMaterial(
    const std::string& name) {
  auto material = std::make_unique<Material>(name);

  material->CreateUniform("albedo", glm::vec3(1.0f, 1.0f, 1.0f),
                          glm::vec3(0.0f, 0.0f, 0.0f),
                          glm::vec3(1.0f, 1.0f, 1.0f));
  material->CreateUniform("roughness", 1.0f, 0.0f, 1.0f);
  material->CreateUniform("metalness", 0.0f, 0.0f, 1.0f);

  material->AddTexture("albedo_texture", NULL);
  material->AddTexture("pbr_texture", NULL);
  material->AddTexture("normal_texture", NULL);
  material->AddTexture("occlusion_texture", NULL);

  return material;
}

std::unique_ptr<Material> MaterialFactory::CreateSkyboxMaterial() {
  auto material = std::make_unique<Material>("skybox_material");
  return material;
}

std::unique_ptr<Material> MaterialFactory::ExtractMaterial(
    Universe& universe, aiMaterial& assimp_material) {
  auto material = CreatePbrMaterial(assimp_material.GetName().C_Str());

  // scalar & vector properties
  for (unsigned int i = 0; i < assimp_material.mNumProperties; i++) {
    auto assimp_property = assimp_material.mProperties[i];
    const std::string assimp_property_name = assimp_property->mKey.C_Str();

    if (properties_map.count(assimp_property_name)) {
      float value;
      assimp_material.Get(assimp_property->mKey.C_Str(), 0, 0, value);
      properties_map.at(assimp_property_name)(assimp_material, *assimp_property,
                                              *material.get());
    }
  }

  // textures
  std::vector<std::string> defines;

  // color
  unsigned int color_texture_count =
      assimp_material.GetTextureCount(aiTextureType_DIFFUSE);
  if (color_texture_count > 0) {  // Seems diffuse texture is being duplicated,
                                  // we'll take only the first one.
    aiString path;
    assimp_material.GetTexture(aiTextureType_DIFFUSE, 0, &path);
    std::string texture_name = material->getName() + "_color_texture";
    std::string texture_path =
        "../resources/meshes/" + std::string(path.C_Str());
    auto texture = universe.AddTexture(
        TextureFactory::ImportTexture(texture_name, texture_path));
    material->SetTexture("albedo_texture", texture);
    defines.push_back("ALBEDO_TEXTURE");
  }

  // normal
  unsigned int normal_texture_count =
      assimp_material.GetTextureCount(aiTextureType_NORMALS);
  if (normal_texture_count > 0) {
    aiString path;
    assimp_material.GetTexture(aiTextureType_NORMALS, 0, &path);
    std::string texture_name = material->getName() + "_normal_texture";
    std::string texture_path =
        "../resources/meshes/" + std::string(path.C_Str());
    auto texture = universe.AddTexture(
        TextureFactory::ImportTexture(texture_name, texture_path));
    // material->SetTexture("normal_texture", texture);
    // defines.push_back("NORMAL_TEXTURE");
  }

  // pbr
  unsigned int pbr_texture_count =
      assimp_material.GetTextureCount(aiTextureType_UNKNOWN);
  if (pbr_texture_count > 0) {
    aiString path;
    assimp_material.GetTexture(aiTextureType_UNKNOWN, 0, &path);
    std::string texture_name = material->getName() + "_pbr_texture";
    std::string texture_path =
        "../resources/meshes/" + std::string(path.C_Str());
    auto texture = universe.AddTexture(
        TextureFactory::ImportTexture(texture_name, texture_path));
    material->SetTexture("pbr_texture", texture);
    defines.push_back("PBR_TEXTURE");
  }

  // occlusion
  unsigned int occlusion_texture_count =
      assimp_material.GetTextureCount(aiTextureType_LIGHTMAP);
  if (occlusion_texture_count > 0) {
    aiString path;
    assimp_material.GetTexture(aiTextureType_LIGHTMAP, 0, &path);
    std::string texture_name = material->getName() + "_occlusion_texture";
    std::string texture_path =
        "../resources/meshes/" + std::string(path.C_Str());
    auto texture = universe.AddTexture(
        TextureFactory::ImportTexture(texture_name, texture_path));
    material->SetTexture("occlusion_texture", texture);
    defines.push_back("OCCLUSION_TEXTURE");
  }

  material->set_shader_wrapper(
      ShaderFactory::CreateOrGetShaderWrapperFromMaterial(
          universe, *material.get(), defines, "../resources/shaders/pbr.vert",
          "../resources/shaders/pbr.frag"));

  return material;
}

}  // namespace orangutan
