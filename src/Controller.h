#include <cstdint>

class Controller {
  public:
    void serialize();
    void loadState();
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
    int16_t joystick_left_x;
    int16_t joystick_left_y;
    int16_t joystick_right_x;
    int16_t joystick_right_y;
    uint8_t trigger_left;
    uint8_t trigger_right;
    uint8_t dpad_and_buttons;
    uint8_t padding;
    // Platform specific code
    #ifdef _WIN32
    // TODO: Implement windows platform
    #elif defined(__linux__)
    int joystick_device;
    #endif
};