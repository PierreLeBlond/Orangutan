#ifndef ORANGUTAN_PATTERNS_OBSERVER_SIGNAL_H
#define ORANGUTAN_PATTERNS_OBSERVER_SIGNAL_H

#include <functional>
#include <list>

template <typename... Arguments>
class Signal {
  using Handler = std::function<void(Arguments...)>;

 public:
  void Emit(Arguments... arguments);
  void Connect(Handler handler);

 private:
  std::list<Handler> handlers_;
};

template <typename... Arguments>
void Signal<Arguments...>::Emit(Arguments... arguments) {
  for (auto &handler : handlers_) {
    handler(arguments...);
  }
}

template <typename... Arguments>
void Signal<Arguments...>::Connect(Handler handler) {
  handlers_.push_back(handler);
}

#endif  // ORANGUTAN_PATTERNS_OBSERVER_SIGNAL_H

