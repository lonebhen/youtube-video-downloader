CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11
LDFLAGS = -ljansson

SRCS = main.c command_execution.c video_info.c format_parsing.c user_interaction.c directory_management.c download_helpers.c argument_parsing.c help_display.c

OBJS = $(SRCS: .c=.o)
TARGET = ytdl

.PHONY: all clean

all: $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)


%.o: %.c
	$(CC) $(CFLAGS) -c $<


clean:
	rm -f $(OBJS) $(TARGET)

