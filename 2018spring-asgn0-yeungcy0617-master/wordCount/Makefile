######################################
# Makefile for the WordCount Program
# Already done for you : )
# 
######################################

CC = gcc
CFLAGS = -lcunit
TARGET = mywc

all: mywc.c util.c count.c
	$(CC) -o $(TARGET) $?
test: util.c count.c tester.c
	$(CC) -DTESTING -o tester $?  -lcunit
clean:
	rm -rf $(TARGET) tester
