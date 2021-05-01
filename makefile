CC = g++
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
CFLAGS = -std=c++11 -Wall -Werror -I$(INCLUDE_DIR)

OBJECTS = \
	$(BUILD_DIR)/Utils.o \
	$(BUILD_DIR)/EthernetFrame.o \

NetworkSensitivityList = \
	$(SRC_DIR)/Network.cpp \
	$(INCLUDE_DIR)/Network.h \

SwitchSensitivityList = \
	$(SRC_DIR)/Switch.cpp \
	$(INCLUDE_DIR)/Switch.h \

SystemSensitivityList = \
	$(SRC_DIR)/System.cpp \
	$(INCLUDE_DIR)/System.h \

UtilsSensitivityList = \
	$(SRC_DIR)/Utils.cpp \
	$(INCLUDE_DIR)/Utils.h \

EthernetFrameSensitivityList = \
	$(SRC_DIR)/EthernetFrame.cpp \
	$(INCLUDE_DIR)/EthernetFrame.h \

all: $(BUILD_DIR) Network.out Switch.out System.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

Network.out: $(BUILD_DIR)/Network.o $(OBJECTS)
	$(CC) $(CFLAGS) -o Network.out $(BUILD_DIR)/Network.o $(OBJECTS)

Switch.out: $(BUILD_DIR)/Switch.o $(OBJECTS)
	$(CC) $(CFLAGS) -o Switch.out $(BUILD_DIR)/Switch.o $(OBJECTS)

System.out: $(BUILD_DIR)/System.o $(OBJECTS)
	$(CC) $(CFLAGS) -o System.out $(BUILD_DIR)/System.o $(OBJECTS)

$(BUILD_DIR)/Network.o: $(NetworkSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Network.cpp -o $(BUILD_DIR)/Network.o

$(BUILD_DIR)/Switch.o: $(SwitchSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Switch.cpp -o $(BUILD_DIR)/Switch.o

$(BUILD_DIR)/System.o: $(SystemSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/System.cpp -o $(BUILD_DIR)/System.o

$(BUILD_DIR)/Utils.o: $(UtilsSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Utils.cpp -o $(BUILD_DIR)/Utils.o

$(BUILD_DIR)/EthernetFrame.o: $(EthernetFrameSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/EthernetFrame.cpp -o $(BUILD_DIR)/EthernetFrame.o

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out
