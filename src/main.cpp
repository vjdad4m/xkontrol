#include <iostream>
#include <thread>
#include <zmq.hpp>
#include <chrono>

#include "Controller.h"

#define STATE_BUFFER_SIZE 14

void printBitsBuffer(uint8_t* buffer) {
  for (uint8_t j = 0; j < STATE_BUFFER_SIZE; j++) {
    uint8_t element = buffer[j];
    for (int i = 7; i >= 0; --i) {
      std::cout << ((element >> i) & 1);
    }
    std::cout << " ";
  }
  std::cout << std::endl;
}

int main() {
  // Initialize controller
  #ifdef __linux__
    static char* device_path = "/dev/input/js1";
    Controller ctrl(device_path);
  #elif _WIN32
    Controller ctrl;
  #endif

  uint8_t buffer[STATE_BUFFER_SIZE]; // State byte array

  // Initialize ZeroMQ publisher
  zmq::context_t context(1);
  zmq::socket_t publisher(context, ZMQ_PUB);

  publisher.bind("tcp://*:5556");

  while (true) {
    ctrl.update();
    std::cout << "== Current state ==" << std::endl;
    ctrl.printState();
    ctrl.serialize(buffer);
    std::cout << "== Serialized state ==" << std::endl;
    printBitsBuffer(buffer);

    // Send serialized state
    zmq::message_t message(buffer, STATE_BUFFER_SIZE);
    publisher.send(message, zmq::send_flags::none);

    ctrl.loadState(buffer);
    std::cout << "== Deserialized state ==" << std::endl;
    ctrl.printState();
    std::cout << std::endl;

    // Sleep for 20ms
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
  }

  return 0;
}
