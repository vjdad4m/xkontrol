import threading
import time
import zmq

# TODO: Implement controller state
class ControllerState:
  pass

class Controller:
  def __init__(self, zmq_stream_address="tcp://localhost:5556"):
    self.latest_serialized_state = None

    self.context = zmq.Context()
    self.subscriber = self.context.socket(zmq.SUB)
    self.subscriber.connect("tcp://localhost:5556")
    self.subscriber.setsockopt_string(zmq.SUBSCRIBE, '')

    # Non-blocking receive
    self.subscriber.setsockopt(zmq.RCVTIMEO, 1000)

  def start(self):
    t_receive = threading.Thread(target=self._receive_thread, daemon=True)
    t_receive.start()

  def _receive_thread(self):
    while True:
      try:
        message = self.subscriber.recv()
        self.latest_serialized_state = message
      # Timeout exception
      except zmq.error.Again:
        continue

  # TODO: Create a ControllerState object from latest serialized state 
  def get(self):
    pass

def main():
  controller = Controller()
  controller.start()

  while True:
    print(controller.latest_serialized_state)
    time.sleep(0.01)

if __name__ == "__main__":
  main()