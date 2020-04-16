#! /bin/sh

case "$1" in 
  start)
    echo "Starting echo socket server"
    start-stop-daemon -S -n tmp102  -a /usr/bin/tmp102 -- -d 
    ;; 
  stop)
    echo "Stopping simple server"
    start-stop-daemon -K -n tmp102
    ;;
   *)
  echo "Usage : $0 {start|stop}"
 exit 1 
esac 

exit 0
