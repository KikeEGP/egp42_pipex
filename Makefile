# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/22 13:08:10 by enrgil-p          #+#    #+#              #
#    Updated: 2025/06/24 19:38:09 by enrgil-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
SOURCES =	main.c utils_and_error.c childs.c manage_path.c\

LIBFT_DIR = ./libft
LIBFT  = $(LIBFT_DIR)/libft.a

OBJECTS = $(SOURCES:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g
SANIT_FLAG = -fsanitize=address
LIBFT_FLAG = -L $(LIBFT_DIR) -l ft
CC = cc
RM = rm -f

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)
	$(info CREATED $(LIBFT))

$(NAME): $(LIBFT) $(OBJECTS)
	$(CC) $(CFLAGS) $(SOURCES) $(LIBFT_FLAG) -o $(NAME)
	$(info CREATED $(NAME))

fsanitize: $(NAME)
	
	$(CC) $(CFLAGS) $(SANIT_FLAG) $(SOURCES) $(LIBFT_FLAG) -o $(NAME)
	$(info CREATED $(NAME) with fsanitize)

clean:
	$(RM) $(OBJECTS)
	@make -C $(LIBFT_DIR)
	$(info REMOVED OBJECTS AND LIBFT/OBJECTS)

compclean: all clean

fclean: clean
	$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean
	$(info REMOVED $(NAME) AND -IN CASE THESE EXISTED YET- OBJECTS)

re: fclean all

.PHONY: all clean fclean re fsanitize compclean
