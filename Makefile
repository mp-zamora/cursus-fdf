# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpenas-z <mpenas-z@student.42madrid.c      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/03 14:16:05 by mpenas-z          #+#    #+#              #
#    Updated: 2024/10/30 21:14:57 by mpenas-z         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = gcc
CFLAGS = -Wall -Wextra -Werror
DFLAGS = -g
CLIBS = -LMLX42/build -lmlx42 -lglfw -ldl -lm -lpthread

SRC_PATH = src/
OBJ_PATH = obj/
LIB_PATH = ./libft/
MLX_PATH = ./MLX42/

SRC =	main.c \
		parse.c \
		parse2.c \
		graphics.c \
		utils.c \
		utils2.c \
		color.c \
		bonus.c
SRCS = $(addprefix $(SRC_PATH), $(SRC))
OBJS = $(patsubst $(SRC_PATH)%.c,$(OBJ_PATH)%.o,$(SRCS))
INC = -I./MLX42/include -I ./includes/
LIB = $(addprefix $(LIB_PATH), libft.a)
MLX = $(addprefix $(MLX_PATH), build/libmlx42.a)

GREEN = \033[0;32m
BLUE = \033[0;34m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re call

all: $(NAME)

debug: CFLAGS += -g
debug: $(NAME)

$(LIB):
	@printf "$(YELLOW)Building libft...$(RESET) \n"
	@$(MAKE) -C $(LIB_PATH) > /dev/null 2>&1 && \
		printf "$(GREEN)✔ Build succesful!$(RESET) \n" || \
		printf "$(RED)✘ Build failed!$(RESET) \n"

$(MLX):
	@printf "$(YELLOW)Checking for MLX42...$(RESET) \n"
	@if [ ! -d "$(MLX_PATH)" ]; then \
		printf "$(BLUE)Cloning MLX42 repository...$(RESET) \n"; \
		git clone https://github.com/42-Fundacion-Telefonica/MLX42.git > /dev/null 2>&1; \
		printf "$(GREEN)✔ MLX42 repository cloned!$(RESET) \n"; \
	else \
		echo "$(GREEN)✔ MLX42 already cloned!$(RESET) \n"; \
	fi
	@if [ ! -f "$(MLX)" ]; then \
		printf "$(BLUE)Building MLX42...$(RESET) \n"; \
		cmake -S $(MLX_PATH) -B $(MLX_PATH)/build > /dev/null 2>&1; \
		cmake --build $(MLX_PATH)/build -j4 > /dev/null 2>&1; \
		printf "$(GREEN)✔ MLX42 build successful!$(RESET) \n"; \
	else \
		printf "$(GREEN)✔ MLX42 is already built!$(RESET) \n"; \
	fi

$(NAME): $(MLX) $(LIB) $(OBJS)
	@printf "$(YELLOW)Building $(NAME)...$(RESET) \n"
	@$(CC) $(CFLAGS) $(OBJS) $(INC) $(MLX) $(LIB) $(CLIBS) -o $(NAME) && \
		printf "$(GREEN)✔ Build succesful!$(RESET) \n" || \
		printf "$(RED)✘ Build failed!$(RESET) \n"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c | $(OBJ_PATH)
	@printf "$(BLUE)Compiling $<...$(RESET) \n"
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_PATH):
	@printf "$(BLUE)Creating object directory...$(RESET) \n"
	@mkdir -p $(OBJ_PATH)

clean:
	@printf "$(BLUE)Cleaning object files...$(RESET) \n"
	@$(MAKE) -C $(LIB_PATH) clean > /dev/null 2>&1
	@rm -f $(OBJS)
	@printf "$(GREEN)✔ Objects cleaned succesfully!$(RESET) \n"

fclean: clean
	@printf "$(BLUE)Removing binaries, dependencies and object files...$(RESET) \n"
	@$(MAKE) -C $(LIB_PATH) fclean > /dev/null 2>&1
	@rm -f $(NAME)
	@rm -rf $(MLX_PATH)
	@printf "$(GREEN)✔ Directory cleaned succesfully!$(RESET) \n"

re: fclean all

call: all clean
	@printf "$(YELLOW)Cleaning dependency builds...$(RESET) \n"
	@$(MAKE) -C $(LIB_PATH) fclean > /dev/null 2>&1
	@rm -rf $(MLX_PATH)
	@printf "$(GREEN)✔ Dependency builds cleaned succesfully!$(RESET) \n"
