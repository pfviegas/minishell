# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/01 12:00:51 by pviegas           #+#    #+#              #
#    Updated: 2023/12/07 16:56:29 by pviegas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Color variables
RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
WHITE	= \033[1;37m
RESET 	= \033[0m

# Executable name
NAME = minishell

# Compiler options
CC 			= cc
CFLAGS		= -Wall -Werror -Wextra -g3 #-fsanitize=address
READFLAGS	= -lreadline

# Paths
SRC_DIR 			= src/
SRC_FILES			= 	minishell.c \
						signals.c \
						get_env.c \
						utils/init.c \
						utils/utils_1.c \
						utils/free.c \
						parsing/parsing.c \
						parsing/parsing_utils.c \
						parsing/parsing_utils_2.c \
						executor/here_doc.c
						built_in/cd.c \
						built_in/cd_utils.c \
						built_in/echo.c \
						built_in/env.c \
						built_in/pwd.c \
						built_in/unset.c \
						built_in/export.c \
						built_in/exit.c 
OBJ_DIR				= obj/

LIBFT 		= libft/libft.a
LIBFT_DIR 	= libft

# Source and object files
OBJS = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

${NAME}: $(OBJS)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)
	@echo "\n\n$(GREEN) [Success] Libft compilated.$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJS) $(READFLAGS) $(LIBFT) -o $(NAME)
	@echo "\n$(GREEN) [Success] ./MiniShell created.$(RESET)\n"

clean:
	@rm -rf $(OBJS)
	@echo "$(RED) [Deleting] .o files ... (deleted)$(RESET)"
	@cd $(LIBFT_DIR) && $(MAKE) --no-print-directory clean

fclean: clean
	@rm -rf $(NAME) $(OBJS)
	@echo "$(RED) [Deleting] .a files ... (deleted)$(RESET)"
	@cd $(LIBFT_DIR) && $(MAKE) --no-print-directory fclean

fclean_bonus: clean
	@rm -rf $(NAME_BONUS) $(OBJS_BONUS)
	@echo "$(RED) [Deleting] .a files ... (deleted)$(RESET)"
	@cd $(LIBFT_DIR) && $(MAKE) --no-print-directory fclean

re: fclean all

v:
	make re && valgrind --leak-check=full --show-leak-kinds=all --suppressions="supp.supp" ./minishell

.PHONY: all clean fclean re bonus fclean_bonus
