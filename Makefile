# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpenas-z <mpenas-z@student.42madrid.c      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/03 14:16:05 by mpenas-z          #+#    #+#              #
#    Updated: 2024/09/04 12:00:44 by mpenas-z         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = gcc
CFLAGS = -Wall -Wextra -Werror -lm

SRC_PATH = src/
OBJ_PATH = obj/
LIB_PATH = ./libft/

SRC = 	main.c \
		parse.c \
		get_next_line.c \
		get_next_line_utils.c
SRCS = $(addprefix $(SRC_PATH), $(SRC))
OBJS = $(patsubst $(SRC_PATH)%.c,$(OBJ_PATH)%.o,$(SRCS))
INC = -I ./includes/
LIB = $(addprefix $(LIB_PATH), libft.a)

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIB_PATH)
	$(CC) $(CFLAGS) $(OBJS) $(INC) $(LIB) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

clean:
	make -C $(LIB_PATH) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIB_PATH) fclean
	rm -f $(NAME)

re: fclean all

call: all clean
	make -C $(LIB_PATH) fclean
