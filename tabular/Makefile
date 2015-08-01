#
# Warning: you may need more libraries than are included here on the
# build line.  The agent frequently needs various libraries in order
# to compile pieces of it, but is OS dependent and we can't list all
# the combinations here.  Instead, look at the libraries that were
# used when linking the snmpd master agent and copy those to this
# file.
#

CC=gcc

OBJS1=snmpdrone.o
OBJS2=snmpdrone.so
TARGETS=gpDroneMIB asyncapp

CFLAGS=-I. `net-snmp-config --cflags`
BUILDLIBS=`net-snmp-config --libs`
BUILDAGENTLIBS=`net-snmp-config --agent-libs`

# shared library flags (assumes gcc)
DLFLAGS=-fPIC -shared

all: $(TARGETS)

snmpdrone: $(OBJS1)
	$(CC) -o gpDroneMIB $(OBJS1) $(BUILDLIBS)

snmpdrone_t.so: gpDroneMIB.c Makefile
	$(CC) $(CFLAGS) $(DLFLAGS) -c -o gpDroneMIB.o gpDroneMIB.c
	$(CC) $(CFLAGS) $(DLFLAGS) -o gpDroneMIB.so gpDroneMIB.o
