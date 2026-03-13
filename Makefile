# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: babe <habe@student.42tokyo.jp>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/08 17:22:20 by babe              #+#    #+#              #
#    Updated: 2026/03/13 12:25:47 by babe             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c \
		routine/philos_routine.c\
		routine/times.c
		utils/ft_atoi.c \
		utils/error.c \
		utils/thread_create.c\
		utils/param_check.c\
		utils/cleanup.c\
		utils/init.c\

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
