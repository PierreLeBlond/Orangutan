#ifndef RENDERABLE_OBJECT_PRESENTER_H
#define RENDERABLE_OBJECT_PRESENTER_H

#include "presenter/presenter.h"
#include "view/view.h"

class RenderableObjectPresenter : public Presenter {
 public:
  RenderableObjectPresenter(std::shared_ptr<Universe> universe,
                            NVGcontext* context, View* view);
  void Init() override;
  void Update() override;

  void UpdateMaterial(const Material& material,
                      const std::vector<std::string>& names);

 private:
  View* view_;
};

#endif  // RENDERABLE_OBJECT_PRESENTER_H
