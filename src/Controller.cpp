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
      /*
      std::cout << "Button " << (int)event.number
                << " is " << (event.value ? "pressed" : "released") << std::endl;
      */
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
        case 8:
          Controller::button_extra_c = event.value;
          break;
        case 9:
          Controller::button_stick_left = event.value;
          break;
        case 10:
          Controller::button_stick_right = event.value;
          break;
        default:
          // Ignore other events
          break;
      }
      break;
    case JS_EVENT_AXIS:
      /*
      std::cout << "Axis " << (int)event.number
                << " is at position " << event.value << std::endl;
      */
      switch (event.number) {
        case 0:
          Controller::joystick_left_x = event.value;
          break;
        case 1:
          Controller::joystick_left_y = -event.value;
          break;
        case 2:
          Controller::trigger_left = static_cast<uint16_t>(event.value + 32768);
          break;
        case 3:
          Controller::joystick_right_x = event.value;
          break;
        case 4:
          Controller::joystick_right_y = -event.value;
          break;
        case 5:
          Controller::trigger_right = static_cast<uint16_t>(event.value + 32768);
          break;
        // Handle dpad events
        case 6:
          event.value /= 32767;
          Controller::dpad_left = 0;
          Controller::dpad_right = 0;
          if (event.value == 1) {
            Controller::dpad_right = 1;
          } else if (event.value == -1) {
            Controller::dpad_left = 1;
          }
        case 7:
          event.value /= 32767;
          Controller::dpad_up = 0;
          Controller::dpad_down = 0;
          if (event.value == 1) {
            Controller::dpad_down = 1;
          } else if (event.value == -1) {
            Controller::dpad_up = 1;
          }
        default:
          // Ignore other events
          break;
      }

    default:
      // Ignore other events
      break;
  }
}
#endif

void Controller::printState() {
  std::cout << "Controller State" << std::endl;
  std::cout << "Left joystick: (x: " << Controller::joystick_left_x
            << ", y: " << Controller::joystick_left_y << ")" << std::endl;
  std::cout << "Right joystick: (x: " << Controller::joystick_right_x
            << ", y: " << Controller::joystick_right_y << ")" << std::endl;
  std::cout << "Left trigger: " << Controller::trigger_left << ", Right trigger: "
            << Controller::trigger_right << std::endl;
  std::cout << "Left bumper: " << (bool)Controller::bumper_left << ", Right bumper: "
            << (bool)Controller::bumper_right << std::endl;
  std::cout << "Dpad: (U: " << (bool)Controller::dpad_up << ", R: "
            << (bool) Controller::dpad_right << ", D: " << (bool)Controller::dpad_down
            << ", L: " << (bool)Controller::dpad_left << ")" << std::endl;
  std::cout << "Buttons: (Y: " << (bool)Controller::button_y << ", B: "
            << (bool) Controller::button_b << ", A: " << (bool)Controller::button_a
            << ", X: " << (bool)Controller::button_x << ")" << std::endl;
  std::cout << "Joystick buttons: " << (bool)Controller::button_stick_left
            << ", " << (bool)Controller::button_stick_right << std::endl;
  std::cout << "Extra buttons: " << (bool)Controller::button_extra_a << ", "
            << (bool)Controller::button_extra_b << ", " << (bool)Controller::button_extra_c
            << std::endl;
}