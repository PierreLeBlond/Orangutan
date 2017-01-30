#ifndef MATERIAL_FACTORY
#define MATERIAL_FACTORY

#include "object/material.h"

class MaterialFactory
{
  public:
    static Material createPhongMaterial();
    static Material createRefractionMaterial();
    static Material createSkyboxMaterial();
    static Material createToonMaterial();
    static Material createDefaultMaterial();

  private:
    MaterialFactory();
};

#endif //MATERIAL_FACTORY
