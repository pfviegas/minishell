# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/05 12:14:41 by pviegas           #+#    #+#              #
#    Updated: 2023/07/24 15:24:16 by pviegas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= libft.a

CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

OBJ_PATH 		= ../obj/

SRCS			=	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
					ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
					ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
					ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
					ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
					ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
					ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
					ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
					ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
					ft_printf.c ft_putchar_ct.c ft_putnbr_ct.c \
					ft_putptr_ct.c ft_putstr_ct.c ft_puthexh_ct.c \
					ft_puthexl_ct.c ft_putuint_ct.c ft_base_conv.c \
					ft_get_next_line.c ft_lstnew.c ft_lstadd_front.c \
					ft_lstsize.c ft_lstadd_back.c ft_lstdelone.c \
					ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS			= $(addprefix $(OBJ_PATH), $(SRCS:.c=.o))

NOC		:= \033[0m
RED		:= \033[1;31m
GREEN	:= \033[1;32m
YELLOW	:= \033[1;33m
BLUE	:= \033[1;34m
WHITE	:= \033[1;37m
					
all:			$(NAME)

$(NAME):		$(OBJS)
				@ar rcs $(NAME) $(OBJS)

$(OBJ_PATH)%.o:	%.c
				@mkdir -p $(OBJ_PATH)
				@echo "  Compiling $(GREEN) $(notdir $@)  $(NOC)"
				@$(CC) $(CFLAGS) -c $< -o $@

clean:
				@echo " "
				@echo "  Deleting $(RED) $(OBJS)  $(NOC)"
				@$(RM) $(OBJS)
				@echo " "

fclean:			clean
				@echo "  Deleting $(YELLOW) $(NAME)  $(NOC)"
				@echo " "
				@$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
