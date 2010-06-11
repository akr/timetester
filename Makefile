all: localtime mktime

localtime: localtime.o

localtime.o: localtime.c

mktime: mktime.o

mktime.o: mktime.c
