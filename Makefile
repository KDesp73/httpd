CC=gcc
CFLAGS=-Wall -Wextra -ansi -pedantic -O2
LDFLAGS=

TARGET = example

.PHONY: all index clean

all : $(TARGET)

$(TARGET) : $(TARGET).o
	$(CC) -o $@ $^ $(LDFLAGS)

stripped : $(TARGET)
	strip -s httpd

index :
	ctags $(TARGET).c

clean :
	rm -f *.o *.exe *.stackdump
	rm -f $(TARGET)
	rm -f tags

%.o : %.c
	$(CC) -o $@ -c $< $(CFLAGS)

