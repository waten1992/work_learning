SRC:=$(wildcard *.c)
OBJ:=$(patsubst *.c,*.o,$(SRC))
TARGET:=cun_test 
CFLAGS:= -o0 -g -pthread -lcunit -std=gnu11 -pg
LDFLAGS:=  -pthread -lcunit -std=gnu11
CC:=gcc

all:$(TARGET) 

$(TARGET):$(OBJ)
	$(CC) $^  $(LDFLAGS) -o $@

%.o:%.c
	$(CC) -c $< $(CFLAGS) -o $@

clean:
	rm $(TARGET)
