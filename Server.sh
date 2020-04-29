#! /bin/sh
#Reference: AESD Lecture 10.

case "$1" in
  start)
    echo "Starting Server Python script"
    python2.7 /bin/MQTT_Server/Server.py
    ;;
  *)
    echo "Usage : $0 {start|stop}"
  exit 
esac

exit 0
