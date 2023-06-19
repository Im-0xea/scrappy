CC = gcc
LD = gcc

CFLAGS  = -Oz -std=c11 -Wall
LDFLAGS = -flto -static

OBJ = main.o \
      sql.o \
      logging.o \

all: $(OBJ)


.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm $(OBJ)
