#!/bin/bash

read -p "Enter number of elements:" n
echo "Enter "$n" numbers :"
for ((i=0;i<$n;i++))
do
	read numbers[$i]
done

read -p "Enter 'asc' for ascending or 'desc' for descending:" order

if [ "$order" == "asc" ];
then
	sorted_num=($(printf '%s \n' "${numbers[@]}"|sort -n))
	echo "Sorted numbers in ascending order : "
	printf '%s ' "${sorted_num[@]}"
elif [ "$order" == "desc" ]; 
then
	sorted_num=($(printf '%s \n' "${numbers[@]}"|sort -nr))
	echo "Sorted numbers in descending order : "
	printf '%s ' "${sorted_num[@]}"
else
	echo "Invalid Input"

fi
