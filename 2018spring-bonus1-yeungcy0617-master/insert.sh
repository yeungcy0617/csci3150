#!/bin/bash

#the database file name is stored in the variable "DATABASE"
# the original arguments are passed to functions, so you can parse the
# arguments on your own

function insert {
	file=$DATABASE
	while IFS= read line
	do
		IFS=',' read -ra ARRAY <<< "$line"
		if [[ ${ARRAY[2]} -eq $4 && ${ARRAY[0]} -eq $2 ]]; then
			exit 
		fi
	done < "$file"
	echo "$2,$3,$4,$5" >> $DATABASE
	echo -e "The total number of records is:\n$(wc -l < $DATABASE)"
}
insert "$@"
