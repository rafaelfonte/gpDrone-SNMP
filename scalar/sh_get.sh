IP=192.168.208.1
QUERY=$IP$1
FILTER=
OUTPUT_FL=output


if [ "$4" = "special" ]
then	#sudo wget -O - $QUERY > arch ; cat arch > $OUTPUT_FL # | grep $1/$2
	#echo $QUERY
	sudo wget -O - $QUERY > arch ; cat arch | grep $1/$2 | grep -o $3 | grep -o '[^(^)]*' > $OUTPUT_FL
elif [ "$4" = "bool" ]
then
	RES=$(sudo wget -O - $QUERY > arch ; cat arch | grep $1/$2 | grep -Eo $3)
	if [ "$RES" = "true" ]
		then echo 1 > $OUTPUT_FL
	else	echo 0 > $OUTPUT_FL
	fi
else
	sudo wget -O - $QUERY > arch ; cat arch | grep $1/$2 | grep -o $3 > $OUTPUT_FL
fi
