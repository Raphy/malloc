##
## Makefile for malloc in /home/bade/Dev/tek2/Unix/malloc
## 
## Made by Barthelemy Delemotte
## Login   <bade@epitech.net>
## 
## Started on Thu Feb  6 12:02:38 2014 Barthelemy Delemotte
## Last update Sun Feb  9 20:28:35 2014 Barthelemy Delemotte
##

INCPATH = includes/
CC = gcc
CFLAGS = -I $(INCPATH) -Wall -Wextra -pedantic -fPIC -O3 -DNDEBUG
LDFLAGS = -shared
TARGET = libmy_malloc_$(HOSTTYPE).so
LINK_NAME = libmy_malloc.so
SRC =	src/malloc.c	\
	src/realloc.c	\
	src/free.c	\
	src/calloc.c	\
	src/heap.c	\
	src/show.c

OBJ = $(SRC:.c=.o)
RM = rm -vf
LN  = ln

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)
	$(LN) -s $(TARGET) $(LINK_NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(TARGET) $(LINK_NAME)

check-syntax:
	$(CC) $(CFLAGS) -o /dev/null $(SRC) $(CHK_SOURCES)
re: fclean all








