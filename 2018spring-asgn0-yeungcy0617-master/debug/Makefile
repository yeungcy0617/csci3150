#############################################
# Makefile for the buggy program.
# Please modify and fill up the space for
# compliation. : )
#############################################

CC = gcc
CFLAGS = -lm
TARGET = mycode

all: mycode.c doMath.c doStr.c
	$(CC) -o $(TARGET) $? $(CFLAGS)
test: doMath.c doStr.c tester.c
	$(CC) -o tester $? $(CFLAGS) -lcunit
clean:
	rm -rf $(TARGET) tester
