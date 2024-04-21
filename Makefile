CC = gcc

SRC := src
OBJ := build

SRCS := $(wildcard $(SRC)/*.c)
OBJS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

all: dirs $(OBJS)
	$(CC) $(OBJS) -o build/riya

.PHONY: dirs
dirs:
	if [ ! -d ./build ]; then mkdir build; fi

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -c $< -o $@
	
.PHONY: clean
clean:
	rm build/*

