#include <cstdint>

class Controller {
  public:
    void printState();
    void serialize(uint8_t* output_buffer);
    void loadState(const uint8_t* in_buffer);
    void update();
    // Platform specific code
    #ifdef _WIN32 // TODO: Implement windows platform
    Controller();
    ~Controller();
    #elif defined(__linux__)
    Controller(char* device_path);
    ~Controller();
    #endif
  private:
    int16_t joystick_left_x = 0;
    int16_t joystick_left_y = 0;
    int16_t joystick_right_x = 0;
    int16_t joystick_right_y = 0;
    uint16_t trigger_left = 1;
    uint16_t trigger_right = 1;
    uint8_t dpad_up : 1 = 0;
    uint8_t dpad_right : 1 = 0;
    uint8_t dpad_down : 1 = 0;
    uint8_t dpad_left : 1 = 0;
    uint8_t button_y : 1 = 0;
    uint8_t button_b : 1 = 0;
    uint8_t button_a : 1 = 0;
    uint8_t button_x : 1 = 0;
    uint8_t button_stick_left : 1 = 0;
    uint8_t button_stick_right : 1 = 0;
    uint8_t bumper_left : 1 = 0;
    uint8_t bumper_right : 1 = 0;
    uint8_t button_extra_a : 1 = 0;
    uint8_t button_extra_b : 1 = 0;
    uint8_t button_extra_c : 1 = 0;
    // Platform specific code
    #ifdef _WIN32
    // TODO: Implement windows platform
    #elif defined(__linux__)
    int joystick_device;
    #endif
};