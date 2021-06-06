#!/bin/bash
for i in 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21
do
touch cicle.in
cp $i cicle.in
./Lab2
s1=`cat cicle.out`
s2=`cat $i.a`
if [[ `cat cicle.out` == `cat $i.a` ]]
then
echo "$i: OK" >> result.txt
else echo "$i: NOT OK" >> result.txt
fi
rm cicle.in
rm cicle.out
done
