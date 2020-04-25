#! /bin/sh
#Reference: AESD Lecture 10.
#Script reused from:https://github.com/cu-ecen-5013/assignment-3-manual-kernel-and-root-filesystem-build-Sankalppund/blob/master/aesdsocket-start-stop.sh

case "$1" in
  start)
    echo "Starting humidity sesnor"
    start-stop-daemon -S -n humidity -a /usr/bin/humidity -- -d
    ;;
  stop)
    echo "Stoping humidity sesnor"
    start-stop-daemon -K -n humidity 
    ;; 
  *)
    echo "Usage : $0 {start|stop}"
  exit 
esac

exit 0
