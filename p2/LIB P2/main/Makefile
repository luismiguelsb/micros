TARGET=main
SRCS=$(TARGET).c

FLAGS=-Wall -g -MMD
INCLUDE=-I. -I../include
LIBDIR=-L../lib
LIBS=

CC=$(CROSS_COMPILE)gcc
CFLAGS=$(FLAGS) $(INCLUDE)
LDFLAGS=$(LIBDIR) $(LIBS)

all: $(TARGET)

$(TARGET): $(SRCS:.c=.o) ../lib/libprova2.a
	$(CC) -o $@ $^ $(LDFLAGS) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

-include $(SRCS:.c=.d)

clean:
	rm main -f *~ *.bak *.o *.d

distclean: clean
	rm -f $(TARGET)
