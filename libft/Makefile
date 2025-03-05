# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 23:26:01 by ravazque          #+#    #+#              #
#    Updated: 2025/03/03 23:26:03 by ravazque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

LIBFT_OBJS_DIR = ../libftObjects

SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
      ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
      ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
      ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
      ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
      ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

OBJS = $(patsubst %.c, $(LIBFT_OBJS_DIR)/%.o, $(SRC))

GREEN = \033[1;32m
LIGHT_RED = \033[1;91m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "$(GREEN)[✔] libft compilada$(RESET)"

$(LIBFT_OBJS_DIR)/%.o: %.c | $(LIBFT_OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_OBJS_DIR):
	@mkdir -p $(LIBFT_OBJS_DIR)

clean:
	@if [ -d "$(LIBFT_OBJS_DIR)" ]; then \
		rm -rf $(LIBFT_OBJS_DIR); \
		echo "$(LIGHT_RED)[✘] Objetos de libft eliminados$(RESET)"; \
	fi

fclean:
	@if [ -d "$(LIBFT_OBJS_DIR)" ]; then \
		rm -rf $(LIBFT_OBJS_DIR); \
		echo "$(LIGHT_RED)[✘] Objetos de libft eliminados$(RESET)"; \
	fi
	@if [ -f "$(NAME)" ]; then \
		rm -f $(NAME); \
		echo "$(LIGHT_RED)[✘] Librería libft.a eliminada$(RESET)"; \
	fi

re: 
	@make -s fclean
	@make -s all 
