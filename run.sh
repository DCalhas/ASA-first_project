#!/bin/bash
# Script to compile and execute a c program in one step.
make

./project <tests/test01.in> test01.myout
DIFF=$(diff tests/test01.out test01.myout)
if ["$DIFF" == ""]
then
	echo "PASSED TEST01"
else 
	echo "FAILED TEST01"
	echo "$DIFF"
fi


./project <tests/test02.in> test02.myout
DIFF=$(diff tests/test02.out test02.myout)
if ["$DIFF" == ""]
then
	echo "PASSED TEST02"
else
	echo "FAILED TEST02" 
	echo "$DIFF"
fi


./project <tests/test03.in> test03.myout
DIFF=$(diff tests/test03.out test03.myout)
if ["$DIFF" == ""]
then
	echo "PASSED TEST03"
else 
	echo "FAILED TEST03"
	echo "$DIFF"
fi



rm -f *.myout


make clean