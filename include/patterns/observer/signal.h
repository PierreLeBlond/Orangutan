#ifndef ORANGUTAN_PATTERNS_OBSERVER_SIGNAL_H
#define ORANGUTAN_PATTERNS_OBSERVER_SIGNAL_H

#include <uuid/uuid.h>

#include <functional>
#include <unordered_map>
#include <utility>

namespace orangutan {

template <typename... Arguments>
class Signal {
  using Handler = std::function<void(Arguments...)>;

 public:
  void Emit(const std::string &source_handler_uuid, Arguments... arguments);
  std::string Connect(Handler handler);
  void Disconnect(const std::string &uuid_str);

 private:
  std::unordered_map<std::string, Handler> handlers_;
};

template <typename... Arguments>
void Signal<Arguments...>::Emit(const std::string &source_handler_uuid,
                                Arguments... arguments) {
  for (auto &handler : handlers_) {
    // An observer at the source of the call doesn't need to be notified
    if (handler.first != source_handler_uuid) {
      handler.second(arguments...);
    }
  }
}

template <typename... Arguments>
std::string Signal<Arguments...>::Connect(Handler handler) {
  uuid_t uuid;
  uuid_generate_time_safe(uuid);

  char uuid_str[37];
  uuid_unparse_lower(uuid, uuid_str);

  // handlers_.insert(std::pair<uuid_t, Handler>(uuid, handler));
  handlers_[uuid_str] = handler;

  return uuid_str;
}

template <typename... Arguments>
void Signal<Arguments...>::Disconnect(const std::string &uuid_str) {
  handlers_.erase(uuid_str);

  uuid_t uuid;
  uuid_parse(uuid_str.c_str(), uuid);
  uuid_clear(uuid);
}

}  // namespace orangutan

#endif  // ORANGUTAN_PATTERNS_OBSERVER_SIGNAL_H

