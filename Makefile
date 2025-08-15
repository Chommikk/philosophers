NAME = change
CC = cc
CFLAGS = -Wall -Wextra -Werror
TFLAGS = -pthread
LIBFT = libft/*.c
THREADING = threding.c
TIME = time/print_time.c
FILES = $(EXECFILES)
OBJ = $(FILES:.c=.o)


all : $(OBJ) $(NAME)
	

$(NAME): $(OBJ)
	$(CC) $(CFLAGS)  $(OBJ) -o $(NAME)


%.o : %.c libft.h
	$(CC) $(CFLAGS) -c   $< -o $@
	
clean :
	rm -f $(OBJ) $(BOBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all


thr:
	cc -Wall -Wextra $(TFLAGS) $(THREADING) $(LIBFT) -g -o ./hello

time:
	cc -Wall -Wextra $(TIME) $(LIBFT) -g -o tm

.PHONY: re fclean clean all com star time
