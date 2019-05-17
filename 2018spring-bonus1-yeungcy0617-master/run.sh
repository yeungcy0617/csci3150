#!/bin/bash

# variables for storing database file, we modify it via "grader.sh" across
# test cases
export DATABASE="./testcases/data/registration.csv"
# determine the operations to run
function run_op {
	case $1 in
	1)
		bash ./listCourses.sh "$@";;
	2)
		bash ./listNumbers.sh "$@";;
	3)
		bash ./insert.sh "$@"
		bash ./listDatabase.sh ;;
	4) 
		bash ./delete.sh "$@"
		bash ./listDatabase.sh ;;
        *) 
                echo "Unknown operation type";;
	esac
}

function main {
    # check the database file if exists.
    if [ ! -f $DATABASE ]; then
  	touch $DATABASE
    fi

    # the original arguments are passed to functions, so you can parse the
    # arguments on your own
    run_op "$@"
}

main "$@"
