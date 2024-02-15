#include "Controller.h"
#include <iostream>
#include <cstring>

// Platform specific constructor and update methods
#ifdef _WIN32
#include <Windows.h>
#include <Xinput.h>

Controller::Controller() {}

Controller::~Controller() {}

void Controller::update() {
  XINPUT_STATE state;
  ZeroMemory(&state, sizeof(XINPUT_STATE));
  if (XInputGetState(0, &state) == ERROR_SUCCESS) {
    Controller::joystick_left_x = state.Gamepad.sThumbLX;
    Controller::joystick_left_y = state.Gamepad.sThumbLY;
    Controller::joystick_right_x = state.Gamepad.sThumbRX;
    Controller::joystick_right_y = state.Gamepad.sThumbRY;
    // Convert trigger values from 0-255 to 0-65535
    Controller::trigger_left = static_cast<uint16_t>(state.Gamepad.bLeftTrigger * (65535.0 / 255.0));
    Controller::trigger_right =  static_cast<uint16_t>(state.Gamepad.bRightTrigger * (65535.0 / 255.0));
    Controller::dpad_up = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0;
    Controller::dpad_right = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0;
    Controller::dpad_down = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0;
    Controller::dpad_left = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0;
    Controller::button_y = (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0;
    Controller::button_b = (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0;
    Controller::button_a = (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0;
    Controller::button_x = (state.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0;
    Controller::button_stick_left = (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) != 0;
    Controller::button_stick_right = (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) != 0;
    Controller::bumper_left = (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0;
    Controller::bumper_right = (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0;
    Controller::button_extra_a = (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != 0;
    Controller::button_extra_b = (state.Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0;
  }
}

#elif defined(__linux__)
#include <linux/joystick.h>
#include <fcntl.h>
#include <unistd.h>

Controller::Controller(const char* device_path) {
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

// Platform independent implementations

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

void Controller::serialize(uint8_t* output_buffer) {
    int index = 0;

    // Store joystick positions
    memcpy(output_buffer + index, &joystick_left_x, sizeof(joystick_left_x));
    index += sizeof(joystick_left_x);
    memcpy(output_buffer + index, &joystick_left_y, sizeof(joystick_left_y));
    index += sizeof(joystick_left_y);
    memcpy(output_buffer + index, &joystick_right_x, sizeof(joystick_right_x));
    index += sizeof(joystick_right_x);
    memcpy(output_buffer + index, &joystick_right_y, sizeof(joystick_right_y));
    index += sizeof(joystick_right_y);

    // Store trigger positions
    memcpy(output_buffer + index, &trigger_left, sizeof(trigger_left));
    index += sizeof(trigger_left);
    memcpy(output_buffer + index, &trigger_right, sizeof(trigger_right));
    index += sizeof(trigger_right);

    // Store button states
    uint16_t buttons = dpad_up | (dpad_right << 1) | (dpad_down << 2) | (dpad_left << 3) |
                       (button_y << 4) | (button_b << 5) | (button_a << 6) | (button_x << 7) |
                       (button_stick_left << 8) | (button_stick_right << 9) |
                       (bumper_left << 10) | (bumper_right << 11) |
                       (button_extra_a << 12) | (button_extra_b << 13) | (button_extra_c << 14);

    memcpy(output_buffer + index, &buttons, sizeof(buttons));
}

void Controller::loadState(const uint8_t* in_buffer) {
    int index = 0;

    // Unpack joystick positions
    memcpy(&joystick_left_x, in_buffer + index, sizeof(joystick_left_x));
    index += sizeof(joystick_left_x);
    memcpy(&joystick_left_y, in_buffer + index, sizeof(joystick_left_y));
    index += sizeof(joystick_left_y);
    memcpy(&joystick_right_x, in_buffer + index, sizeof(joystick_right_x));
    index += sizeof(joystick_right_x);
    memcpy(&joystick_right_y, in_buffer + index, sizeof(joystick_right_y));
    index += sizeof(joystick_right_y);

    // Unpack trigger positions
    memcpy(&trigger_left, in_buffer + index, sizeof(trigger_left));
    index += sizeof(trigger_left);
    memcpy(&trigger_right, in_buffer + index, sizeof(trigger_right));
    index += sizeof(trigger_right);

    // Unpack button states
    uint16_t buttons;
    memcpy(&buttons, in_buffer + index, sizeof(buttons));

    dpad_up = buttons & 1;
    dpad_right = (buttons >> 1) & 1;
    dpad_down = (buttons >> 2) & 1;
    dpad_left = (buttons >> 3) & 1;
    button_y = (buttons >> 4) & 1;
    button_b = (buttons >> 5) & 1;
    button_a = (buttons >> 6) & 1;
    button_x = (buttons >> 7) & 1;
    button_stick_left = (buttons >> 8) & 1;
    button_stick_right = (buttons >> 9) & 1;
    bumper_left = (buttons >> 10) & 1;
    bumper_right = (buttons >> 11) & 1;
    button_extra_a = (buttons >> 12) & 1;
    button_extra_b = (buttons >> 13) & 1;
    button_extra_c = (buttons >> 14) & 1;
}
