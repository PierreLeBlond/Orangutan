#ifndef ORANGUTAN_PRESENTER_PRESENTER_H
#define ORANGUTAN_PRESENTER_PRESENTER_H

#include <memory>
#include <vector>

#include "model/universe.h"

namespace orangutan {

class Presenter {
 public:
  Presenter(Universe* universe, NVGcontext* context);

  virtual void Init() = 0;
  virtual void Update() = 0;
  virtual void Resize(unsigned int width, unsigned int height) = 0;

  [[nodiscard]] Universe& get_universe() const;

  [[nodiscard]] NVGcontext* get_context() const;

  [[nodiscard]] const std::vector<Presenter*>& get_child_presenters() const;
  void AddChildPresenter(Presenter& child_presenter);

 private:
  Universe* universe_;
  NVGcontext* context_;
  std::vector<Presenter*> child_presenters_;
};

}  // namespace orangutan

#endif  // ORANGUTAN_PRESENTER_PRESENTER_H
