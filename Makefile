CC = clang-15
CFLAGS = -Wall -g -gdwarf-4

SRCS = stack.c token.c jc.c
OBJS = stack.o token.o jc.o

TARGET = jc

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

token.o: token.c token.h
	$(CC) $(CFLAGS) -c token.c

jc.o: jc.c token.h stack.h
	$(CC) $(CFLAGS) -c jc.c

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)
