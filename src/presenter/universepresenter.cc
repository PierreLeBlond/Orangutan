#include "presenter/universepresenter.h"

UniversePresenter::UniversePresenter(std::shared_ptr<Universe> universe,
                                     NVGcontext* context, View* view)
    : Presenter(std::move(universe), context), view_(view) {}

void UniversePresenter::Init() {
  view_->set_layout(new nanogui::GroupLayout());

  Update();
}

void UniversePresenter::Update() {
  view_->clear();

  std::vector<std::string> renderableObjectNames;

  const std::vector<std::shared_ptr<RenderableObject>>& renderableObjects =
      get_universe()->get_renderable_object_library().get_items();

  std::shared_ptr<RenderableObject> currentRenderableObject =
      get_universe()->get_renderable_object_library().get_current_item();

  unsigned int renderableObjectId = 0;

  for (unsigned int i = 0; i < renderableObjects.size(); ++i) {
    renderableObjectNames.push_back(renderableObjects[i]->getName());
    if (renderableObjects[i] == currentRenderableObject) renderableObjectId = i;
  }

  view_->addComboBox(view_, nanogui::Popup::Right, "Objects",
                     renderableObjectNames, renderableObjectId,
                     [&, renderableObjects](int id) {
                       // scene->setCurrentRenderableObject(renderableObjects.at(id));
                       // scene->getCameraLibrary().getCurrentItem()->set_focus_object(
                       // renderableObjects.at(id));
                       // scene->getCameraLibrary().getCurrentItem()->UpdateFocus();
                       // scene->getCameraLibrary().getCurrentItem()->Focus();
                       // notifyChangeToModel();
                     });
}
