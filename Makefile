NAME_PS = push_swap
NAME_CH = checker
SRC_COMMON = $(wildcard *.c)
SRC_CHECKER = $(wildcard checker_f/*.c)
SRC_PUSHSWAP = $(wildcard push_swap_f/*.c)
OBJ_COMMON=$(SRC_COMMON:.c=.o)
OBJ_CHECKER=$(SRC_CHECKER:.c=.o)
OBJ_PUSHSWAP=$(SRC_PUSHSWAP:.c=.o)
CC = clang
CFLAGS = -Wall -Wextra -Werror
LIB := ./libft/lib/libft.a
LIBDIR = libft/
LIBSPATH = -I libft/includes/ -I /usr/local/include/ -I ./
HDR := ./push_swap.h
VIZ =
LINK = -lmlx -framework OpenGL -framework AppKit -L /usr/local/lib/

viz: VIZ = -D VIZUALIZER
viz: re

%.o: %.c $(HDR) $(LIB)
	$(CC) $(CFLAGS) $(VIZ) $(LIBSPATH) -c $< -o $@

all: lib $(NAME_CH) $(NAME_PS)

$(NAME_PS): $(OBJ_COMMON) $(OBJ_PUSHSWAP)
	$(CC) $(CFLAGS) $(LIBSPATH) -o $(NAME_PS) $(LINK) $(LIB) $(OBJ_COMMON) $(OBJ_PUSHSWAP)

$(NAME_CH): $(OBJ_COMMON) $(OBJ_CHECKER)
	$(CC) $(CFLAGS) $(LIBSPATH) $(VIZ) -o $(NAME_CH) $(LINK) $(LIB) $(OBJ_COMMON) $(OBJ_CHECKER)

lib:
	make -C $(LIBDIR)

fclean: clean cleanlib
	/bin/rm -f $(NAME)

clean:
	@/bin/rm -f $(OBJ_COMMON) $(OBJ_PUSHSWAP) $(OBJ_CHECKER)

cleanlib:
	make -C $(LIBDIR) clean

re: fclean all

clean_all: cleanlib clean

fclean_all: clean_all
	/bin/rm -f $(NAME)
	make -C $(LIBDIR) fclean

re_all: fclean_all all

