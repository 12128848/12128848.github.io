CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lm
OBJS = main.o tilewm.o anchor.o
TARGET = wm

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)
clean:
	rm -f $(OBJS) $(TARGET)