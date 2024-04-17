#!/bin/bash

read -p "Enter the number to check :" num

limit=$(($num/2))
fact=2
check=true
while [[ $fact -le $limit ]];
do
	 if [[ $(($num % $fact )) == 0 ]]; then
	 	check=false
	 	break
	 fi
	 fact=$((fact+1))
done

if [[ $check == true ]]; then
	echo "The number is prime"
else
	echo "the number is not prime"
fi