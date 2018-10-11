CC = clang
CFLAGS = -c -g -Wall -Wextra -pedantic -std=c11
LDFLAGS =
SRCS = deck.c
OBJS = $(SRCS:.c=.o)
BIN = blackjack

all: $(SRCS) $(BIN)

.PHONY: clean
clean:
	$(RM) *.o $(BIN)
