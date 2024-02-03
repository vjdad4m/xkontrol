#include "Controller.h"
#include <iostream>

// Platform specific contruction
#ifdef _WIN32
// TODO: Implement windows platform
#elif defined(__linux__)
#include <linux/joystick.h>
#include <fcntl.h>
#include <unistd.h>
Controller::Controller(char* device_path) {
  Controller::joystick_device = open(device_path, 0, O_RDONLY);
  if (Controller::joystick_device < 0) {
      std::cerr << "Could not open joystick device." << std::endl;
  }
}

Controller::~Controller() {
  close(Controller::joystick_device);
}

void Controller::update() {
  struct js_event event;
  read(Controller::joystick_device, &event, sizeof(event));
  switch (event.type) {
    case JS_EVENT_BUTTON:
      std::cout << "Button " << (int)event.number
                << " is " << (event.value ? "pressed" : "released") << std::endl;
      break;
    case JS_EVENT_AXIS:
      std::cout << "Axis " << (int)event.number
                << " is at position " << event.value << std::endl;
      break;
    default:
      // Ignore other events
      break;
  }
}
#endif