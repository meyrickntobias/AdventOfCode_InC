CC = gcc
CFLAGS = -g -Wall 
TARGET = day6-part1

SRC = day6-part1.c input_processing.c helpers/grid.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
