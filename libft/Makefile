# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/12 18:37:01 by mdodevsk          #+#    #+#              #

#    Updated: 2025/06/17 11:00:35 by mdodevsk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#COMPILER AND FLAGS
CC = cc

CFLAGS = -Wall -Wextra -Werror -fPIC

AR = ar -rcs

#SOURCE FILES
SRC = ft_atoi.c ft_bzero.c ft_calloc.c \
      ft_isalnum.c ft_isalpha.c ft_isascii.c \
	  ft_isdigit.c ft_isprint.c ft_memchr.c \
	  ft_memcmp.c ft_memcpy.c ft_memmove.c \
	  ft_memset.c ft_strchr.c ft_strdup.c \
	  ft_strlcat.c ft_strlcpy.c ft_strlen.c \
	  ft_strncmp.c ft_strnstr.c ft_strrchr.c \
	  ft_tolower.c ft_toupper.c ft_substr.c \
	  ft_strjoin.c ft_split.c  \
	  ft_putchar_fd.c ft_putendl_fd.c ft_putstr_fd.c \
	  ft_putnbr_fd.c ft_itoa.c ft_strmapi.c ft_striteri.c \
	  ft_lstlast_bonus.c \
	  42-Gnl/get_next_line_utils.c 42-Gnl/get_next_line.c \
	  42-printf/ft_printf.c \
	  42-printf/ft_ptr.c 42-printf/ft_putlstr.c 42-printf/ft_putnbr_hex.c 42-printf/ft_putnbr_u.c 42-printf/ft_putnbr.c

#DEFINE DIRECTORIES
OBJ_DIR = obj

#DEFINE OBJECTS
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

#PROGRAM NAME
NAME = libft.a

#DEFAULT TARGET
all: $(NAME)

#CREATE STATIC LIBRARY
$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)

#CREATING OBJECT DIRECTORIES
$(OBJ_DIR):
	@mkdir -p $@

#COMPILING .c FILES INTO .o FILES (INSIDE OBJ DIR)
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

#BASIC RULES
clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY : all clean fclean re
