# Implementing the MQTT communication protocol to enable lightweight, reliable messaging
# between devices in IoT applications, focusing on efficient data exchange over constrained networks

import paho.mqtt.client as mqtt
import time

# Define the MQTT broker and port
broker = "mqtt.eclipse.org"
port = 1883
topic = "iot/lab/mqtt_test"

# Define the message payload and Quality of Service level
message = "Hello from the Advanced MQTT Publisher!"
qos = 1  # QoS level (0 = at most once, 1 = at least once, 2 = exactly once)

# Callback function to handle connection events
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT Broker successfully")
    else:
        print(f"Failed to connect with error code {rc}")

# Callback function to handle message publishing events
def on_publish(client, userdata, mid):
    print(f"Message '{message}' published to topic '{topic}' with QoS {qos}")

# Create a new MQTT client instance
client = mqtt.Client()
client.on_connect = on_connect
client.on_publish = on_publish

# Connect to the MQTT broker
client.connect(broker, port, keepalive=60)

# Start the network loop
client.loop_start()

# Publish the message to the specified topic with QoS
try:
    result = client.publish(topic, message, qos=qos)
    status = result.rc
    if status == 0:
        print(f"Message sent successfully to topic '{topic}'")
    else:
        print(f"Failed to send message to topic '{topic}', return code: {status}")

    time.sleep(1)  # Optional delay to ensure message delivery

finally:
    # Disconnect and stop the loop after publishing
    client.loop_stop()
    client.disconnect()
    print("Disconnected from the MQTT Broker")
