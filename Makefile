NAME = philo

SRCS = main.c \
	   helper1.c \
	   helper2.c \
	   routines.c \

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	cc -o $(NAME) $(OBJS) -pthread

%.o: %.c
	cc -c  -Wall -Werror -Wextra $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re