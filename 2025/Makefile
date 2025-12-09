CC = gcc
CFLAGS = -g -Wall 
TARGET = day5-part1

SRC = day5-part1.c input_processing.c helpers/grid.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
