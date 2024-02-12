#include <zmq.hpp>
#include <string>

#include "Controller.h"

class Application {
  public:
    Application(const std::string& zmq_bind_address, const std::string& devicePath = "");
    ~Application();
    void run();
  private:
    Controller ctrl;
    zmq::context_t context;
    zmq::socket_t publisher;
    static constexpr size_t STATE_BUFFER_SIZE = 14;

    void printBitsBuffer(const uint8_t* buffer) const;
};