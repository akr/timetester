all: localtime mktime info

localtime: localtime.o

localtime.o: localtime.c

mktime: mktime.o

mktime.o: mktime.c

info: info.o
info.o: info.c
