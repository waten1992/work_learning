SRC:=$(wildcard *.c)
OBJ:=$(patsubst *.c,*.o,$(SRC))
TARGET:=a
CFLAGS:=-o0 -g3 -lpthread -std=gnu11
CC:=gcc

all:$(TARGET)

$(TARGET):$(OBJ)
	$(CC) $^ $(CFLAGS) -o $@
%.o:%.c
	$(CC) -c $< $(CFLAGS) -o $@


clean:
	@rm $(TARGET)
 
