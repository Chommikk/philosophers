NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
TFLAGS = -pthread
LIBFT = libft/ft_atoi.c\
		libft/ft_calloc.c\
		libft/ft_isdigit.c\
		libft/ft_itoa.c\
		libft/puterror.c\
		libft/ft_strlen.c

FILES = main.c\
		even.c\
		odd.c\
		util.c\
		actions.c\
		$(LIBFT)
OBJ = $(FILES:.c=.o)


all : $(OBJ) $(NAME)
	

$(NAME): $(OBJ)
	$(CC) $(CFLAGS)  $(OBJ) -o $(NAME)


%.o : %.c libft.h
	$(CC) $(CFLAGS) -c -O  $< -o $@
	
clean :
	rm -f $(OBJ) $(BOBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all


thr:
	cc -Wall -Wextra $(TFLAGS) $(THREADING) $(LIBFT) -g -o ./hello

time:
	cc -Wall -Wextra $(TIME) $(LIBFT) -g -o tm

test:
	cc -Wall -Wextra $(FILES) -g -O -o test

.PHONY: test
