SRC:=$(wildcard *.c)
OBJ:=$(patsubst *.c,*.o,$(SRC))
TARGET:=quote_query
CFLAGS:= -o0 -g -pthread  -std=gnu11 -pg 
LDFLAGS:= -L ./ -lsche_task 
CC:=gcc

all:$(TARGET) 

$(TARGET):$(OBJ)
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -o $@

%.o:%.c
	$(CC) -c $< $(CFLAGS) -o $@

clean:
	rm $(TARGET)
