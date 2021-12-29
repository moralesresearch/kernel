CC = $(CROSS_COMPILE)gcc
<<<<<<< HEAD
CFLAGS = -g -Wall -O2 -D_FORTIFY_SOURCE=2
=======
CFLAGS = -g -Wall
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

all: resctrl_tests

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)

resctrl_tests: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean

clean:
	$(RM) $(OBJS) resctrl_tests
