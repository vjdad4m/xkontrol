import threading
import struct
import random
import time
import zmq


# Button mappings
BUTTON_DPAD_UP = 0
BUTTON_DPAD_DOWN = 1
BUTTON_DPAD_LEFT = 2
BUTTON_DPAD_RIGHT = 3
BUTTON_Y = 4
BUTTON_B = 5
BUTTON_A = 6
BUTTON_X = 7
BUTTON_STICK_LEFT = 8
BUTTON_STICK_RIGHT = 9
BUTTON_BUMPER_LEFT = 10
BUTTON_BUMPER_RIGHT = 11
BUTTON_EXTRA_A = 12
BUTTON_EXTRA_B = 13
BUTTON_EXTRA_C = 14

class ControllerState:
  def __init__(self, state = None):
    if state is not None:
      self.deserialize(state)
    else:
      self.reset()
  
  def reset(self):
    self.joystick_left_x = 0
    self.joystick_left_y = 0
    self.joystick_right_x = 0
    self.joystick_right_y = 0
    self.trigger_left = 0
    self.trigger_right = 0
    self.buttons = 0 # Use a single integer to represent all buttons
    
  # Serialize controller state
  def serialize(self):
    packed_data = struct.pack('hhhhHH', self.joystick_left_x, self.joystick_left_y,
                                  self.joystick_right_x, self.joystick_right_y,
                                  self.trigger_left, self.trigger_right)
    # Add button states
    packed_data += struct.pack('H', self.buttons)
    
    return packed_data
  
  # Deserialize controller state
  def deserialize(self, data):
    unpacked_data = struct.unpack('hhhhHHH', data)
    self.joystick_left_x, self.joystick_left_y, \
    self.joystick_right_x, self.joystick_right_y, \
    self.trigger_left, self.trigger_right, self.buttons = unpacked_data
  
  def set_button_state(self, button, state):
    if state:
      self.buttons |= (1 << button)
    else:
      self.buttons &= ~(1 << button)

  def get_button_state(self, button):
    return (self.buttons >> button) & 1
  
  def __str__(self):
    return f"Joystick left: ({self.joystick_left_x}, {self.joystick_left_y}), " + \
           f"Joystick right: ({self.joystick_right_x}, {self.joystick_right_y}), " + \
           f"Triggers: ({self.trigger_left}, {self.trigger_right}), " + \
           f"Buttons: {self.buttons}"
  
  def __repr__(self):
    return self.__str__()


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
  
  # Return latest state
  def get(self):
    current_state = ControllerState(self.latest_serialized_state)
    return current_state

def test_serialization():
  original_state = ControllerState()
  # Set some values
  original_state.joystick_left_x = random.randint(-32768, 32767)
  original_state.joystick_left_y = random.randint(-32768, 32767)
  original_state.joystick_right_x = random.randint(-32768, 32767)
  original_state.joystick_right_y = random.randint(-32768, 32767)
  original_state.trigger_left = random.randint(0, 65535)
  original_state.trigger_right = random.randint(0, 65535)
  # Set button states
  for i in range(15):
    original_state.set_button_state(i, random.choice([True, False]))

  # Serialize then deserialize
  serialized_state = original_state.serialize()
  new_state = ControllerState(serialized_state)

  # Serialize again to compare
  serialized_state_again = new_state.serialize()

  assert serialized_state == serialized_state_again, "Serialized states do not match."

  return True

def main():
  # Run serialization test
  for idx in range(10):
    result = test_serialization()
    if result:
      print(f"Serialization test [{idx+1}] passed.")
    else:
      print(f"Serialization test [{idx+1}] failed.")

  # Create controller instance
  controller = Controller()
  controller.start()

  while True:
    latest_state = controller.get()
    print(latest_state)

    time.sleep(0.01)

if __name__ == "__main__":
  main()