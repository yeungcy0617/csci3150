#!/bin/bash

#the database file name is stored in the variable "DATABASE"
# the original arguments are passed to functions, so you can parse the
# arguments on your own

function listNumbers {
	file=$DATABASE
	shift
	for arguments; do
		let total=0	
		while IFS= read line
		do
			IFS=',' read -ra ARRAY <<< "$line"
			if [[ ${ARRAY[2]} == $arguments ]] ; 
				then ((total++));
			fi
		done < "$file"
		echo $total
	done
}

listNumbers "$@"
