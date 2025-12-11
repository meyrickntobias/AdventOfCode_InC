CC = gcc
CFLAGS = -g -Wall 
TARGET = day5-part2

SRC = day5-part2.c input_processing.c helpers/grid.c helpers/hashset.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
