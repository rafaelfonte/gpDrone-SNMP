#!/bin/bash
IP=192.168.208.1
G_LIGHT=/controls/lighting
RETURN=

if [ "$2" = "1" ]
then	RETURN=true
else
	RETURN=false
fi

if [ "$1" = "lgSetPosition" ]
then
	wget -O - -t 1 $IP/controls/gear/gear-down?value=$RETURN"&submit=update"

elif [ "$1" = "beacon" ]
then
	wget -O - -t 1 $IP$G_LIGHT/beacon?value=$RETURN"&submit=update"
elif [ "$1" = "landing-light-left" ]
then
	wget -O - -t 1 $IP$G_LIGHT/landing-light?value=$RETURN"&submit=update"
elif [ "$1" = "landing-light-center" ]
then
	wget -O - -t 1 $IP$G_LIGHT/landing-light%5B1%5D?value=$RETURN"&submit=update"
elif [ "$1" = "landing-light-right" ]
then
	wget -O - -t 1 $IP$G_LIGHT/landing-light%5B2%5D?value=$RETURN"&submit=update"
elif [ "$1" = "logo-lights" ]
then
	wget -O - -t 1 $IP$G_LIGHT/logo-lights?value=$RETURN"&submit=update"
fi

#Freeing up the lock...
echo "0" > lock
