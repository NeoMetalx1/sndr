CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Isrc

SRC = src/main.c \
      src/setup/socket_options.c \
	  src/tx/transmit.c \
	  src/rx/receive.c \
	  src/file/file_options.c

OBJ = $(SRC:.c=.o)

TARGET = sndr

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
