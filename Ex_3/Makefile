CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS =

SRCS = main.c
OBJS = $(SRCS:.c=.o)
EXECUTABLE = rave

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXECUTABLE) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
