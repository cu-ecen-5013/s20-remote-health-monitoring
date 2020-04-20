#Filename: Server-Subscriber.py
#Auther: Sankalp Pund
#Description: This python script works as mqtt server-subscriber
#Reference: https://github.com/eclipse/paho.mqtt.python

import context  # Ensures paho is in PYTHONPATH
import paho.mqtt.client as mqtt

# This is the Subscriber
print("I am Server")
def on_connect(client, userdata, flags, rc):
  print("Connected with result code "+str(rc))
  client.subscribe("topic/test")

def on_message(client, userdata, msg):
  a=msg.payload.decode()
  print("Received Message from Client is - - ->: '%s'" %a)	
  if a == "Sending test data to Server...":
    print("Success! Test data has been received at server from client side")
# client.disconnect()
    
client = mqtt.Client()
client.connect("localhost",1883,60)

client.on_connect = on_connect
client.on_message = on_message

client.loop_forever()
