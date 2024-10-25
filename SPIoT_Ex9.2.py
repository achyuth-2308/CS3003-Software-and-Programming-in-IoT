# Implementing the Subscriber
# The subscriber listens for messages on a specific topic. Here's an example of a subscriber in Python:

import paho.mqtt.client as mqtt

# Define the MQTT broker and topic
broker = "mqtt.eclipse.org"
port = 1883
topic = "iot/lab/mqtt_test"

# Callback function for successful connection
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT Broker successfully")
        # Subscribe to the topic once connected
        client.subscribe(topic, qos=1)
        print(f"Subscribed to topic '{topic}' with QoS level 1")
    else:
        print(f"Failed to connect with error code {rc}")

# Callback function for incoming messages
def on_message(client, userdata, message):
    try:
        payload = message.payload.decode()
        print(f"Message received on topic '{message.topic}': {payload}")
    except UnicodeDecodeError:
        print("Received a message that couldn't be decoded.")

# Callback function for logging additional information (optional)
def on_log(client, userdata, level, buf):
    print(f"Log: {buf}")

# Create a new MQTT client instance
client = mqtt.Client()

# Attach the callback functions
client.on_connect = on_connect
client.on_message = on_message
client.on_log = on_log  # Optional: Attach for logging details

# Connect to the MQTT broker
client.connect(broker, port, keepalive=60)

# Start the loop to process incoming messages
try:
    client.loop_forever()
except KeyboardInterrupt:
    print("\nSubscriber disconnected from MQTT Broker.")
    client.disconnect()
