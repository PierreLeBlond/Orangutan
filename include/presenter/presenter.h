#ifndef PRESENTER_H
#define PRESENTER_H

#include <memory>
#include <vector>

#include "model/universe.h"

class Presenter {
 public:
  Presenter(std::shared_ptr<Universe> universe, NVGcontext* context);

  virtual void Init() = 0;
  virtual void Update() = 0;

  [[nodiscard]] std::shared_ptr<Universe> get_universe() const;

  [[nodiscard]] NVGcontext* get_context() const;

  [[nodiscard]] const std::vector<std::shared_ptr<Presenter>>&
  get_child_presenters() const;
  void AddChildPresenter(std::shared_ptr<Presenter> child_presenter);

 private:
  std::shared_ptr<Universe> universe_;
  NVGcontext* context_;
  std::vector<std::shared_ptr<Presenter>> child_presenters_;
};

#endif  // PRESENTER_H
