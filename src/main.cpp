#include <iostream>
#include <thread>
#include "Controller.h"

int main() {
  char* device_path = "/dev/input/js1";
  Controller ctrl(device_path);
  while (true) {
    ctrl.update();
    ctrl.printState();
    std::cout << std::endl;
  }
  
  return 0;
}