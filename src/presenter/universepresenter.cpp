#include "presenter/universepresenter.h"

UniversePresenter::UniversePresenter(std::shared_ptr<Presenter> parent) :
    Presenter(parent)
{}

void UniversePresenter::init()
{
    _view->setFixedSize(Eigen::Vector2i(300, 600));
    _view->setPosition(Eigen::Vector2i(0, 0));

    _view->setLayout(new nanogui::GroupLayout());

    update();
}

void UniversePresenter::update()
{
    _view->clear();

    std::vector<std::string> renderableObjectNames;

    std::shared_ptr<Scene> scene = _universe->getSceneLibrary().getCurrentItem();

    const std::vector<std::shared_ptr<RenderableObject>>& renderableObjects =
        scene->getRenderableObjectLibrary().getItems();

    std::shared_ptr<RenderableObject> currentRenderableObject = scene->getRenderableObjectLibrary().getCurrentItem();

    int renderableObjectId = 0;

    for(unsigned int i = 0; i < renderableObjects.size(); ++i)
    {
        renderableObjectNames.push_back(renderableObjects[i]->getName());
        if(renderableObjects[i] == currentRenderableObject)
            renderableObjectId = i;
    }

    _view->addComboBox(_view.get(), nanogui::Popup::Right,
                          "Objects", renderableObjectNames, renderableObjectId,
                          [&, scene, renderableObjects](int id){
                          scene->setCurrentRenderableObject(renderableObjects.at(id));
                          scene->getCameraLibrary().getCurrentItem()->setFocusObject(renderableObjects.at(id));
                          scene->getCameraLibrary().getCurrentItem()->updateFocus();
                          scene->getCameraLibrary().getCurrentItem()->focus();
                          notifyChangeToModel();
                          });
}

void UniversePresenter::setView(nanogui::ref<View> view)
{
    _view = view;
}
