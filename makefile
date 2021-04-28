COMPILER = g++
COMPILER_FLAGS = --std=c++11
SRC_DIR = src
INCLUDE_DIR = include
all : Network.out Switch.out System.out

Network.out : Network.o Utils.o
	${COMPILER} ${COMPILER_FLAGS} Network.o Utils.o -o Network.out
	
Network.o :  $(SRC_DIR)/Network.cpp $(INCLUDE_DIR)/Network.h $(INCLUDE_DIR)/Utils.h
	${COMPILER} ${COMPILER_FLAGS} -c $(SRC_DIR)/Network.cpp -o Network.o

Switch.out : Switch.o Utils.o
	${COMPILER} ${COMPILER_FLAGS} Switch.o Utils.o -o Switch.out

Switch.o :  $(SRC_DIR)/Switch.cpp $(INCLUDE_DIR)/Switch.h $(INCLUDE_DIR)/Utils.h
	${COMPILER} ${COMPILER_FLAGS} -c $(SRC_DIR)/Switch.cpp -o Switch.o

System.out : System.o Utils.o
	${COMPILER} ${COMPILER_FLAGS} System.o Utils.o -o System.out

System.o :  $(SRC_DIR)/System.cpp $(INCLUDE_DIR)/System.h $(INCLUDE_DIR)/Utils.h
	${COMPILER} ${COMPILER_FLAGS} -c $(SRC_DIR)/System.cpp -o System.o

Utils.o :  $(SRC_DIR)/Utils.cpp $(INCLUDE_DIR)/Utils.h
	${COMPILER} ${COMPILER_FLAGS} -c $(SRC_DIR)/Utils.cpp -o Utils.o

rm:
	rm -rf *.out 