#include "Application.h"
#include <iostream>
#include <thread>
#include <chrono>

Application::Application(const std::string& zmq_bind_address, const std::string& devicePath) : context(1), publisher(context, ZMQ_PUB) {
  #ifdef __linux__
  // Initialize controller
  if (!devicePath.empty()) {
    ctrl = Controller(devicePath);
  }
  #endif
  publisher.bind(zmq_bind_address);
}

Application::~Application() {
  // Close the publisher and the context
  publisher.close();
  context.close();
}

void Application::run() {
  uint8_t buffer[STATE_BUFFER_SIZE]; // State byte array

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
}

void Application::printBitsBuffer(const uint8_t* buffer) const {
  for (uint8_t j = 0; j < STATE_BUFFER_SIZE; j++) {
    uint8_t element = buffer[j];
    for (int i = 7; i >= 0; --i) {
      std::cout << ((element >> i) & 1);
    }
    std::cout << " ";
  }
  std::cout << std::endl;
}