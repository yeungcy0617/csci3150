#!/bin/bash

#the database file name is stored in the variable "DATABASE"
# the original arguments are passed to functions, so you can parse the
# arguments on your own
function delete {
	file=$DATABASE
	sed -i "/$2/{/$3/d}" $DATABASE
	echo -e "The total number of records is:\n$(wc -l < $DATABASE)"
}

delete "$@"
