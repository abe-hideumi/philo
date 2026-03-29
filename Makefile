# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/08 17:22:20 by babe              #+#    #+#              #
#    Updated: 2026/03/29 14:22:53 by habe             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = main.c \
		src/philos_actions.c \
		src/philos_routine.c \
		src/monitor_routine.c \
		src/times.c \
		src/thread_create.c \
		src/init_src.c \
		src/cleanup.c \
		utils/error_exit.c \
		utils/error_msg.c \
		utils/ft_atoi.c \
		utils/param_check.c \
		utils/ft_strlen.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	@echo "\033[33m[Clean]\033[0m Remove object files..."
	@rm -f $(OBJS)

fclean:
	@echo "\033[31m[Fclean]\033[0m Remove all build artifacts..."
	@rm -f $(OBJS)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
