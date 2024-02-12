import zmq

# Setup context and subscriber socket
context = zmq.Context()
subscriber = context.socket(zmq.SUB)
subscriber.connect("tcp://localhost:5556")
subscriber.setsockopt_string(zmq.SUBSCRIBE, '')

# Non-blocking receive
subscriber.setsockopt(zmq.RCVTIMEO, 1000)

try:
    while True:
        message = subscriber.recv()

        print("Received serialized state: ", message)
        
        for byte in message:
            print(bin(byte)[2:].zfill(8), end=' ')
        print()
    
except KeyboardInterrupt:
    print("Exiting...")

finally:
    subscriber.close()
    context.term()
