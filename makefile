CC = gcc
CFLAGS = -Wall -std=c99 -g
SRC = minesweeper.c board.c score.c game.c
OBJ = $(SRC:.c=.o)
TEST_SRC = tests.c
TEST_OBJ = tests.o
EXEC = saper
TEST_EXE = tests
#default target
all: $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

test: $(TEST_OBJ) board.o score.o game.o
	$(CC) $(CFLAGS) -o $(TEST_EXE) $(TEST_OBJ) board.o score.o game.o
	@echo "Testowanie..."
	./$(TEST_EXE)

%.o: %.c
	$(CC) $(CFLAGS) $(EXTRA_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TEST_OBJ) $(EXEC) $(TEST_EXE)

.PHONY: all clean test
