################################################################################
# NAME:		    Makefile
#
# AUTHOR:	    Ethan D. Twardy
#
# DESCRIPTION:	    The makefile for the project.
#
# CREATED:	    11/06/2017
#
# LAST EDITED:	    11/06/2017
###

CC=gcc
CFLAGS=-g -Wall -O0 # TODO: Change these values

SRCS += calc.c

OBJS=$(patsubst %.c,%.o,$(SRCS))

.PHONY: force clean

all: force calc clean

calc: force $(OBJS)
	$(CC) $(CFLAGS) -o calc $(OBJS)

$(OBJS): force

force:

clean:
	@rm -f $(TOP)/*.o
	@rm -f $(TOP)/*.c~
	@rm -f $(TOP)/*.h~

################################################################################
