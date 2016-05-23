#pragma once

#include <vector>

namespace app {
  class Instance;
}

class app::Instance {
public:
  typedef void(*ShutdownHandler)();

  ~Instance();

  int Run();
  bool IsRunning() const noexcept;

  void PushShutdownHandler(ShutdownHandler handler);

private:
  std::vector<ShutdownHandler> shutdown_handlers;
  bool is_running = false;
};
