CC = gcc
LIBS = -ldl
CFLAGS = -Wall --ansi


OBJECTS = main.c
OBJECTS_LIB = calcAreas.c calcNewton.c

calc: $(OBJECTS) libcalc logconsole logfile
	$(CC) -o $@ $(OBJECTS) $(LIBS) 

libcalc: $(OBJECTS_LIB)
	$(CC) -o $@.so -shared -fpic calcAreas.c calcNewton.c

logconsole: logconsole.c
	$(CC) -o $@.so -shared -fpic logconsole.c

logfile: logfile.c
	$(CC) -o $@.so -shared -fpic logfile.c

