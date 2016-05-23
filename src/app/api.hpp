#pragma once

namespace app {
  typedef void(*ShutdownHandler)();

  int run();
  void push_shutdown_handler(ShutdownHandler);
}
