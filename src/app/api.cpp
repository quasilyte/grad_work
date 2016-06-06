#include <app/api.hpp>

#include <app/app.hpp>
#include <dev_assert.hpp>

using namespace app;

Instance instance;

int app::run(StartHandler handler) {
  dev_assert(!instance.IsRunning());

  return instance.Run(handler);
}

void app::push_shutdown_handler(ShutdownHandler handler) {
  instance.PushShutdownHandler(handler);
}
