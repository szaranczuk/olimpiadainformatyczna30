#!/bin/bash
let COUNTER=0
if [ -z $3 ]
then
COUNTER=0
else
COUNTER=$3
fi

let limit=$2+$COUNTER

while [ $COUNTER -lt $limit ]
do
	printf "Test $COUNTER: ";
	/usr/bin/time -o time_elapsed.txt --format "%e %M" $1 < $COUNTER.in > output1.txt;
	time_elapsed=$(cat time_elapsed.txt);
	diff -w output1.txt $COUNTER.out >/dev/null;REPLY=$?
	if [ ${REPLY} -eq 0 ]
	then
		printf "\u001b[32mOK\u001b[0m (";
		#printf "($time_elapsed";
		awk '{printf $1}' time_elapsed.txt
		printf "s "
		awk '{printf $2}' time_elapsed.txt
		printf "KB)\n";
	else
		printf "\u001b[31mZLE\u001b[0m (";
		awk '{printf $1}' time_elapsed.txt
		printf "s "
		awk '{printf $2}' time_elapsed.txt
		printf "KB)\n";
		exit 0;
	fi
	let COUNTER=COUNTER+1
done;
printf "\u001b[32mProgram passed all tests!\u001b[0m\n"
