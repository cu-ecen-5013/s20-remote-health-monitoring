# FileName: Client-Publisher.py
# Auther: Sankalp Pund
# Description: This python script runs as mqtt client
# Reference: https://github.com/eclipse/paho.mqtt.python

import context  # Ensures paho is in PYTHONPATH
import paho.mqtt.client as mqtt
print("I am Client")
client = mqtt.Client()
client.connect("10.0.0.185",1883,60)
client.publish("topic/test","Sending test data to Server...");
print("Sending test data to Server...")
client.disconnect();

