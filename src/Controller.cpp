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
  std::cout << (bool)Controller::button_a << std::endl;
  struct js_event event;
  read(Controller::joystick_device, &event, sizeof(event));
  switch (event.type) {
    case JS_EVENT_BUTTON:
      std::cout << "Button " << (int)event.number
                << " is " << (event.value ? "pressed" : "released") << std::endl;
      switch (event.number) {
        case 0:
          Controller::button_a = event.value;
          break;
        case 1:
          Controller::button_b = event.value;
          break;
        case 2:
          Controller::button_x = event.value;
          break;
        case 3:
          Controller::button_y = event.value;
          break;
        case 4:
          Controller::bumper_left = event.value;
          break;
        case 5:
          Controller::bumper_right = event.value;
          break;
        case 6:
          Controller::button_extra_a = event.value;
          break;
        case 7:
          Controller::button_extra_b = event.value;
          break;
        case 9:
          Controller::button_extra_c = event.value;
          break;
        case 10:
          Controller::button_stick_left = event.value;
          break;
        case 11:
          Controller::button_stick_right = event.value;
          break;
      }
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