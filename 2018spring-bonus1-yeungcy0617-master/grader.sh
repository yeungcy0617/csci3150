#!/bin/bash

##############################################################################
# Test cases

INPUT_DIR="./testcases/data"
TMP_INPUT_DIR="./testcases/tmp"
OUTPUT_DIR="./output"
ANS_DIR=./testcases/expected

function modify_database_file_path {
	# modify the DATABASE variable in run.sh file
	sed -i "s#\(DATABASE=\).*#\1\"$INPUT_DIR\/$1\"#g" run.sh
}

function use_default_database_file_path {
	# modify the DATABASE variable in run.sh file
	sed -i "s/\(DATABASE=\).*/\1\".\/testcases\/data\/registration.csv\"/g" run.sh
}

## basic test case: test the list course function using the example in specification
## use "a.csv" as the database file
function testcase1 {
	modify_database_file_path "a.csv"
	./run.sh 1 1155073100 > ${OUTPUT_DIR}/$1.txt
	use_default_database_file_path 
}

## basic test case: test the list number function using the example in specification
## use "a.csv" as the database file
function testcase2 {
	modify_database_file_path "a.csv"
	./run.sh 2 CSCI3150 CSCI4190 CSCI1100 > ${OUTPUT_DIR}/$1.txt
	use_default_database_file_path 
}

## basic test case: test the insert function using the example in specification
## use "a.csv" as the database file
function testcase3 {
	modify_database_file_path "a.csv"
	./run.sh 3 1155073104 Jim CSCI4190 "Introduction To Social Networks" > ${OUTPUT_DIR}/$1.txt
	use_default_database_file_path 
}

## basic test case: test the delete function using the example in specification
## in this example, we first input student id and then course id
## use "b.csv" as the database file
function testcase4 {
	modify_database_file_path "b.csv"
	./run.sh 4 1155073100 CSCI3150 > ${OUTPUT_DIR}/$1.txt
	use_default_database_file_path 
}

## basic test case: test the delete function using the example in specification
## in this example, we first input course id and then student id
## use "c.csv" as the database file
function testcase5 {
	modify_database_file_path "c.csv"
	./run.sh 4 CSCI3170 1155073102 > ${OUTPUT_DIR}/$1.txt
        use_default_database_file_path 
}


## advanced test case: test the list course function using a non-registration student id 
## use "a.csv" as the database file
function testcase6 {
	modify_database_file_path "a.csv"
	./run.sh 1 2255073100 > ${OUTPUT_DIR}/$1.txt
        use_default_database_file_path 
}


## advanced test case: test the list numbers function using an empty database file
## use "d.csv" as the database file
function testcase7 {
	modify_database_file_path "d.csv"
	./run.sh 2 CSCI3150 > ${OUTPUT_DIR}/$1.txt
        use_default_database_file_path 
}

## advanced test case: test the insert function using an empty database file
## use "d.csv" as the database file
function testcase8 {
	modify_database_file_path "d.csv"
	./run.sh 3 1155073104 Jim CSCI4190 "Introduction To Social Networks" > ${OUTPUT_DIR}/$1.txt
        use_default_database_file_path 
}

## advanced test case: test the delete function using a database file with only one record
## use "e.csv" as the database file
function testcase9 {
	modify_database_file_path "e.csv"
	./run.sh 4 1155073101 CSCI3150 > ${OUTPUT_DIR}/$1.txt
        use_default_database_file_path 
}

## advanced test case: test the list course function using an empty database file( threfore, the student is also a non-registration student id )
## use "a.csv" as the database file
function testcase10 {
	modify_database_file_path "d.csv"
	./run.sh 1 2255073100 > ${OUTPUT_DIR}/$1.txt
        use_default_database_file_path 
}

##############################################################################
# Reporting results

# have fun with colors and styles :) 
# ref: http://misc.flogisoft.com/bash/tip_colors_and_formatting

BD="\033[1m"
BDED="\033[21m"
RED="\033[31m"
GREEN="\033[92m"
ED="\e[0m"
diff_flags="-Z -b -B"

function main {
	if [ ! -d ${OUTPUT_DIR} ]; then
		mkdir -p ${OUTPUT_DIR} || { echo -e "${BD}${RED}Cannot create output directory \"${OUTPUT_DIR}\"${ED}"; exit -1; }
	fi

	# clean up the output files
	rm -rf ${OUTPUT_DIR}/*
		
	#since the script would change the content of the databsefile,
	#copy the test cases to a tmp file
	cp -r  ${INPUT_DIR} ${TMP_INPUT_DIR}
	

	tests=("1" "2" "3" "4" "5" "6" "7" "8" "9" "10")
	total=${#tests[@]}
	pass=0

	for i in ${tests[@]}; do		
		# run the test cases
		testcase${i} ${i}

		#restore the testcase file
                # this is a lazy solution, because we copy the whole test cases not the used one
		rm -rf ${INPUT_DIR}
		cp -r ${TMP_INPUT_DIR} ${INPUT_DIR}

		diff -q ${diff_flags} ${OUTPUT_DIR}/${i}.txt ${ANS_DIR}/${i}.txt \
		|| { echo -e "${BD}${RED}""Failed case ${i} \
		(left: your answer, right: correct answer)${ED}" \
		&& diff -y ${diff_flags} ${OUTPUT_DIR}/${i}.txt ${ANS_DIR}/${i}.txt; } && { \
		(( pass ++ )); }
		echo ""
	done

	echo -e "${GREEN}""[Result] ${pass}/${total} test cases passed${ED}"
	
	#remove the tmp test cases
	rm -rf ${TMP_INPUT_DIR}
}


main
