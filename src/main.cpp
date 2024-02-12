#include "Application.h"

int main() {
  std::string zmq_bind_address = "tcp://*:5556";

  #ifdef __linux__
  // Set the device path
  std::string devicePath = "/dev/input/js1";
  Application app(zmq_bind_address, devicePath);
  #else
  Application app(zmq_bind_address);
  #endif

  app.run();

  return 0;
}
