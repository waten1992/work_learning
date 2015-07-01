CC:=g++
TOP:=../..
SRCS:=$(wildcard *.cpp)
OBJS:=$(patsubst %.cpp,%.o,${SRCS})
INCPATH:=-I$(TOP)/lib/include -I$(TOP)/lib/include/mfast
CFLAGS:=-O0 -g2 ${INCPATH} -std=c++11  
LIBPATH:=-L./ -L$(TOP)/lib/bin -L$(TOP)/src 
LDFLAGS:=${LIBPATH} -Wl,-rpath,$(TOP)/lib/bin -Wl,-rpath,$(TOP)/src -lrqb -lboost_system
OUT:= test_rqb
DEP:=.dep

all:$(OUT)_send $(OUT)_recv

$(OUT)_send:test_pub.cpp
	g++ $(CFLAGS) test_pub.cpp ${LDFLAGS} -o $(OUT)_send

$(OUT)_recv:test_sub.cpp
	g++ $(CFLAGS) test_sub.cpp ${LDFLAGS} -o $(OUT)_recv

# NOTE: manually update is needed when source/header
# dependency are changed.

vi:
	vi -p *.h *.cpp Makefile 

debug:

clean:
	-@rm -f *.o ||True
	-@rm -f $(OUT)* || True

distclean:
	-@rm -f *.o ||True
	-@rm -f $(OUT)* || True

