INC_DIR:= ./include
SRC_DIR:= ./src
SRCS:=$(wildcard $(SRC_DIR)/*.cc)
OBJS:= $(patsubst %.cc, %.o, $(SRCS))
LIBS:= -lpthread -ljson

CXX:=g++

CXXFLAGS:= -w -g -std=c++11 $(addprefix -I, $(INC_DIR)) $(LIBS) -Wno-deprecated -I ../cppjieba/include/ -I ../cppjieba/deps

EXE:=./server

$(EXE):$(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(CXXFLAGS)

clean:
	rm -rf $(EXE)
	rm -rf $(OBJS)
