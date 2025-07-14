CC=gcc
CFLAGS=-Wall -Wextra -Ilib -m64
LDFLAGS=-lws2_32

SRC=server.c lib/file_helper.c lib/http_helper.c utils.c
OBJ=$(SRC:.c=.o)
EXEC=server.exe

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	cmd /c del *.o lib\*.o server.exe


