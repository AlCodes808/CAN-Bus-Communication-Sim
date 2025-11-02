CC=gcc
CFLAGS=-Iinclude -Wall
SRC=src/can_frame.c src/can_bus.c src/ecu_node.c src/dtc_manager.c src/json_logger.c src/main.c
OBJ=$(SRC:.c=.o)
EXEC=can_simulator.exe

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

clean:
	rm -f $(OBJ) $(EXEC) can_data.json