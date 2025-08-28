NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
TFLAGS = -pthread
LIBFT = libft/ft_atoi.c\
		libft/ft_calloc.c\
		libft/ft_isdigit.c\
		libft/ft_itoa.c

THREADING = threding.c
TIME = time/print_time.c
FILES = main.c\
		even.c\
		actions/sleeptest.c\
		utils/message_print.c\
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

opti:
	cc -Wall -Wextra $(FILES) -g -O -o opti
.PHONY: re fclean clean all com star time test
