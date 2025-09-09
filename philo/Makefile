NAME = philo

SRCS = main.c \
	   input_parser.c \
	   helper1.c \
	   helper2.c \
	   helper3.c \
	   routine_thread.c \
	   monitor_routine.c \
	   routine_actions.c \
	   routine_forks.c \
	   one_philo_case.c \
	   threads_ready_check.c

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