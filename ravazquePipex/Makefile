# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 21:02:14 by ravazque          #+#    #+#              #
#    Updated: 2025/03/04 18:50:50 by ravazque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
# CFLAGS = -Wall -Wextra -Werror -g3 -Ilibft

CFLAGS = -g3 -Ilibft

PIPEX_OBJS_DIR = pipexObjects
LIBFT_OBJS_DIR = libftObjects

SRC = pipex.c pipex_utils.c
PIPEX_OBJS = $(patsubst %.c, $(PIPEX_OBJS_DIR)/%.o, $(SRC))

LIBFT_SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
            ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
            ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
            ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
            ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
            ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

LIBFT_OBJS = $(patsubst %.c, $(LIBFT_OBJS_DIR)/%.o, $(LIBFT_SRC))

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

GREEN = \033[1;32m
LIGHT_RED = \033[1;91m
RESET = \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(PIPEX_OBJS)
	@if [ ! -f $(PIPEX_OBJS_DIR)/%.o ]; then \
		$(CC) $(CFLAGS) $(PIPEX_OBJS) $(LIBFT) -o $(NAME) > /dev/null 2>&1; \
		echo "$(GREEN)[✔] pipex compilado$(RESET)"; \
	fi
	@if [ ! -f $(NAME) ]; then \
		$(CC) $(CFLAGS) $(PIPEX_OBJS) $(LIBFT) -o $(NAME) > /dev/null 2>&1; \
		echo "$(GREEN)[✔] pipex compilado$(RESET)"; \
	fi

$(LIBFT): $(LIBFT_OBJS)
	@echo "$(GREEN)[✔] libft completada$(RESET)"
	@ar rcs $(LIBFT) $(LIBFT_OBJS) > /dev/null 2>&1

$(PIPEX_OBJS_DIR)/%.o: %.c | $(PIPEX_OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ > /dev/null 2>&1

$(LIBFT_OBJS_DIR)/%.o: $(LIBFT_DIR)/%.c | $(LIBFT_OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ > /dev/null 2>&1

$(PIPEX_OBJS_DIR):
	@mkdir -p $(PIPEX_OBJS_DIR) > /dev/null 2>&1

$(LIBFT_OBJS_DIR):
	@mkdir -p $(LIBFT_OBJS_DIR) > /dev/null 2>&1

clean:
	@if [ -d "$(PIPEX_OBJS_DIR)" ]; then \
		rm -rf $(PIPEX_OBJS_DIR) > /dev/null 2>&1; \
		echo "$(LIGHT_RED)[✘] Objetos de pipex eliminados$(RESET)"; \
	fi
	@if [ -d "$(LIBFT_OBJS_DIR)" ]; then \
		rm -rf $(LIBFT_OBJS_DIR) > /dev/null 2>&1; \
		echo "$(LIGHT_RED)[✘] Objetos de libft eliminados$(RESET)"; \
	fi
	@if [ -f "$(LIBFT_DIR)/libft.a" ]; then \
		rm -f $(LIBFT_DIR)/libft.a > /dev/null 2>&1; \
		echo "$(LIGHT_RED)[✘] Librería libft.a eliminada$(RESET)"; \
	fi

fclean:
	@if [ -f $(NAME) ]; then \
		rm -f $(NAME) > /dev/null 2>&1; \
		echo "$(LIGHT_RED)[✘] Archivos de ejecución existentes eliminados$(RESET)"; \
	fi
	@make clean > /dev/null 2>&1
	@make -C $(LIBFT_DIR) fclean -s > /dev/null 2>&1

re: fclean all
