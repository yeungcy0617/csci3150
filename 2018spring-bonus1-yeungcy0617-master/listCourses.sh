#!/bin/bash

#the database file name is stored in the variable "DATABASE"
# the original arguments are passed to functions, so you can parse the
# arguments on your own


function listCourses {
	file=$DATABASE
	while IFS= read line
	do
		IFS=',' read -ra ARRAY <<< "$line"
		if [[ ${ARRAY[0]} == "$2" ]] ; 
			then echo "${ARRAY[3]}";
		fi
	done < "$file"
}

listCourses "$@"