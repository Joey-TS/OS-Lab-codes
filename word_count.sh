#!/bin/bash

read -p "Enter the text file name : " file_name
read -p "Enter the word to count : " word

word_count=$(grep -o -w $word $file_name | uniq -c)
echo "word count :" $word_count
