#include "app/app.hpp"

#include <cstdlib>
#include "di/output.hpp"

using namespace app;

Instance::~Instance() {
  for (auto handler : shutdown_handlers) {
    handler();
  }

  is_running = false;
}

int Instance::Run(StartHandler handler) {
  is_running = true;

  di::set_files(
    fopen("./module.txt", "w"),
    fopen("./runtime.txt", "w")
  );

  handler();

  return EXIT_SUCCESS;
}

bool Instance::IsRunning() const noexcept {
  return is_running;
}

void Instance::PushShutdownHandler(ShutdownHandler handler) {
  shutdown_handlers.push_back(handler);
}
