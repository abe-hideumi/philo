# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: babe <habe@student.42tokyo.jp>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/08 17:22:20 by babe              #+#    #+#              #
#    Updated: 2025/12/13 15:58:18 by babe             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = src/main.c \
		src/ft_atoi.c \
		src/error.c \
		src/init.c\
		src/thread_create.c\
		src/param_check.c\
		src/cleanup.c
		
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