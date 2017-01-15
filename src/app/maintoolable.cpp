#include "app/maintoolable.h"

MainToolable::MainToolable()
{
}

MainToolable::~MainToolable()
{
    _scene = NULL;
}

void MainToolable::setCurrentObject(std::shared_ptr<RenderableObject> object)
{
    _object = object;
}

void MainToolable::setScene(std::shared_ptr<Scene> scene){
    _scene = scene;
}

void MainToolable::setAssetsStorage(std::shared_ptr<AssetsStorage> assetsStorage){
    _assetsStorage = assetsStorage;
}

void MainToolable::setSkybox(int id){
}

