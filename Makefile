SRC_DIR=src
OBJ_DIR=obj
INCLUDE_DIR=include
BUILD_DIR=build

CC=g++
CFLAGS=-c -std=c++11 -Wall -I$(INCLUDE_DIR)
LDFLAGS=-lm


all: $(BUILD_DIR)/run

$(BUILD_DIR)/run: $(OBJ_DIR)/main.o $(OBJ_DIR)/graph_utils.o $(OBJ_DIR)/line_segment.o $(OBJ_DIR)/point3.o
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/graph_utils.h $(INCLUDE_DIR)/line_segment.h $(INCLUDE_DIR)/point3.h
	$(CC) $(CFLAGS) $(SRC_DIR)/main.cpp -o $@


$(OBJ_DIR)/graph_utils.o: $(SRC_DIR)/graph_utils.cpp $(INCLUDE_DIR)/graph_utils.h $(INCLUDE_DIR)/line_segment.h
	$(CC) $(CFLAGS) $(SRC_DIR)/graph_utils.cpp -o $@

$(OBJ_DIR)/line_segment.o: $(SRC_DIR)/line_segment.cpp $(INCLUDE_DIR)/line_segment.h $(INCLUDE_DIR)/point3.h
	$(CC) $(CFLAGS) $(SRC_DIR)/line_segment.cpp -o $@

$(OBJ_DIR)/point3.o: $(SRC_DIR)/point3.cpp $(INCLUDE_DIR)/point3.h
	$(CC) $(CFLAGS) $(SRC_DIR)/point3.cpp -o $@

clean:
	-rm $(OBJ_DIR)/*.o $(BUILD_DIR)/run
