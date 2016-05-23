#pragma once

namespace app {
  typedef void(*StartHandler)();
  typedef void(*ShutdownHandler)();

  int run(StartHandler);
  void push_shutdown_handler(ShutdownHandler);
}
