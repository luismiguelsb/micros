TARGET=final
SRCS=$(TARGET).c
#gabriel stefaniak niemiec e nicolas eymael da silva
FLAGS=-Wall -g -MMD
INCLUDE=-I. -I../include
LIBDIR=-L../lib
LIBS=-lgalileo2

CC=$(CROSS_COMPILE)gcc
CFLAGS=$(FLAGS) $(INCLUDE)
LDFLAGS=$(LIBDIR) $(LIBS)

all: $(TARGET)
	echo Copy final and instal + eng scripts to Galileo and run instal

$(TARGET): $(SRCS:.c=.o) ../lib/libgalileo2.a
	$(CC) -o $@ $^ $(LDFLAGS) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< -lm

-include $(SRCS:.c=.d)

clean:
	rm -f *~ *.bak *.o *.d

distclean: clean
	rm -f $(TARGET)

