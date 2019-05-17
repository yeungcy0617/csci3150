#!/bin/bash

#the database file name is stored in the variable "DATABASE"

# this file only is used to automatically grade your program. You do not need to 
# modify it.
function listDatabase {
    # start processing $
    #remove the empty line
    sed -i '/^$/d' $DATABASE
    cat $DATABASE
}

listDatabase
