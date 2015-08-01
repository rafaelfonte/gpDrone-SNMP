#!/bin/bash
#$1 Contains the object being requested!

echo First parameter is $1 > file

#GET=$('pwd')/sh_get.sh
GET=./sh_get.sh

GROUP_GPS=/instrumentation/gps
GROUP_ALT=/instrumentation/altimeter
GROUP_TIME=/instrumentation/clock
GROUP_VEL_VERT=/instrumentation/inst-vertical-speed-indicator
GROUP_VEL_HORI=/instrumentation/airspeed-indicator
GROUP_ACC=/accelerations
GROUP_FUEL=/consumables/fuel
GROUP_SIM=/sim
GROUP_LGEAR=/controls/gear

#CREATE A TABLE WITH ALL OF THE LIGHTING RESOURCES AVAILABLE!
GROUP_CTRL_LIGHT=/controls/lighting

#FLOAT_EXP='[-]\{0,1\}[[:digit:]\.]\{3,\}'
INT_EXP='[-]\{0,1\}[[:digit:]]\{1,\}'
TIME_EXP='[[:digit:]]\{2\}:[[:digit:]]\{2\}'
DESC_EXP='(.*)'
BOOL_EXP='true|false'
FLOAT_EXP=$DESC_EXP

if   [ "$1" = "instPosGpsLongitude" ]
then	$($GET $GROUP_GPS indicated-longitude-deg $FLOAT_EXP special)

elif [ "$1" = "instPosGpsLatitude" ]
then	$($GET $GROUP_GPS indicated-latitude-deg $FLOAT_EXP special)

elif [ "$1" = "instPosAltitude" ]
then	$($GET $GROUP_ALT indicated-altitude-ft $FLOAT_EXP special)

elif [ "$1" = "instClTime" ]
then	$($GET $GROUP_TIME local-short-string $TIME_EXP normal)

elif [ "$1" = "sysTimeUp" ]
then	$($GET  $GROUP_TIME indicated-sec $INT_EXP normal) #$GROUP_TIME indicated-sec $INT_EXP

elif [ "$1" = "instSpeedGround" ]
then	$($GET $GROUP_VEL_HORI indicated-speed-kt $FLOAT_EXP special)

elif [ "$1" = "instSpeedVertical" ]
then	$($GET $GROUP_VEL_VERT indicated-speed-fps  $FLOAT_EXP special)

elif [ "$1" = "sysAircraftType" ]
then	$($GET $GROUP_SIM description  $DESC_EXP special)

elif [ "$1" = "lgSetPosition" ]
then	$($GET $GROUP_LGEAR gear-down $BOOL_EXP bool)

elif [ "$1" = "instTotalFuel" ]
then	$($GET $GROUP_FUEL total-fuel-kg $FLOAT_EXP special)

#TABLE CASES

elif [ "$1" = "beacon" ]
then	$($GET $GROUP_CTRL_LIGHT beacon $BOOL_EXP bool)

elif [ "$1" = "landing-light-left" ]
then	$($GET $GROUP_CTRL_LIGHT landing-light\" $BOOL_EXP bool)

elif [ "$1" = "landing-light-center" ]
then	$($GET $GROUP_CTRL_LIGHT landing-light%5B1%5D $BOOL_EXP bool)

elif [ "$1" = "landing-light-right" ]
then	$($GET $GROUP_CTRL_LIGHT landing-light%5B2%5D $BOOL_EXP bool)

elif [ "$1" = "logo-lights" ]
then	$($GET $GROUP_CTRL_LIGHT logo-lights $BOOL_EXP bool)

else
	echo "what was it?"

fi

#Freeing up the lock...
echo "0" > lock


