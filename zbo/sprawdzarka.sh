#!/bin/bash
let COUNTER=0
if [ -z $5 ]
then
COUNTER=0
else
COUNTER=$5
fi

let limit=$4+$COUNTER

while [ $COUNTER -lt $limit ]
do
	printf "Test $COUNTER: ";
	$1 > input.txt $COUNTER;
	/usr/bin/time -o time_elapsed.txt --format "%e %M" $2 < input.txt > output1.txt;
	time_elapsed=$(cat time_elapsed.txt);
	$3 < input.txt > output2.txt;
	DIFF=$(diff -q -w output1.txt output2.txt);
	diff -w output1.txt output2.txt >/dev/null;REPLY=$?
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
