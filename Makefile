# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpenas-z <mpenas-z@student.42madrid.c      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/03 14:16:05 by mpenas-z          #+#    #+#              #
#    Updated: 2024/09/18 11:52:38 by mpenas-z         ###   ########.fr        #
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
		get_next_line.c \
		get_next_line_utils.c
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
debug: all

$(LIB):
	@echo -e "$(YELLOW)Building libft...$(RESET)"
	@$(MAKE) -C $(LIB_PATH) > /dev/null 2>&1 && \
		echo -e "$(GREEN)✔ Build succesful!$(RESET)" || \
		echo -e "$(RED)✘ Build failed!$(RESET)"

$(MLX):
	@echo -e "$(YELLOW)Checking for MLX42...$(RESET)"
	@if [ ! -d "$(MLX_PATH)" ]; then \
		echo -e "$(BLUE)Cloning MLX42 repository...$(RESET)"; \
		git clone https://github.com/42-Fundacion-Telefonica/MLX42.git > /dev/null 2>&1; \
		echo -e "$(GREEN)✔ MLX42 repository cloned!$(RESET)"; \
	else \
		echo "$(GREEN)✔ MLX42 already cloned!$(RESET)"; \
	fi
	@if [ ! -f "$(MLX)" ]; then \
		echo -e "$(BLUE)Building MLX42...$(RESET)"; \
		cmake -S $(MLX_PATH) -B $(MLX_PATH)/build > /dev/null 2>&1; \
		cmake --build $(MLX_PATH)/build -j4 > /dev/null 2>&1; \
		echo -e "$(GREEN)✔ MLX42 build successful!$(RESET)"; \
	else \
		echo -e "$(GREEN)✔ MLX42 is already built!$(RESET)"; \
	fi

$(NAME): $(MLX) $(LIB) $(OBJS)
	@echo -e "$(YELLOW)Building $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(INC) $(MLX) $(LIB) $(CLIBS) -o $(NAME) && \
		echo -e "$(GREEN)✔ Build succesful!$(RESET)" || \
		echo -e "$(RED)✘ Build failed!$(RESET)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c | $(OBJ_PATH)
	@echo -e "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_PATH):
	@echo -e "$(BLUE)Creating object directory...$(RESET)"
	@mkdir -p $(OBJ_PATH)

clean:
	@echo -e "$(BLUE)Cleaning object files...$(RESET)"
	@$(MAKE) -C $(LIB_PATH) clean > /dev/null 2>&1
	@rm -f $(OBJS)
	@echo -e "$(GREEN)✔ Objects cleaned succesfully!$(RESET)"

fclean: clean
	@echo -e "$(BLUE)Removing binaries, dependencies and object files...$(RESET)"
	@$(MAKE) -C $(LIB_PATH) fclean > /dev/null 2>&1
	@rm -f $(NAME)
	@rm -rf $(MLX_PATH)
	@echo -e "$(GREEN)✔ Directory cleaned succesfully!$(RESET)"

re: fclean all

call: all clean
	@echo -e "$(YELLOW)Cleaning dependency builds...$(RESET)"
	@$(MAKE) -C $(LIB_PATH) fclean > /dev/null 2>&1
	@rm -rf $(MLX_PATH)
	@echo -e "$(GREEN)✔ Dependency builds cleaned succesfully!$(RESET)"
