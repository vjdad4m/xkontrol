#include <iostream>
#include "Controller.h"

int main() {
  char* device_path = "/dev/input/js1";
  Controller ctrl(device_path);
  while (true) {
    ctrl.update(); // Note: Update is in blocking mode
  }
  
  return 0;
}