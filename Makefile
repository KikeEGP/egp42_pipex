NAME = pipex
SOURCES =	main.c\

OBJECTS = $(SOURCES: .c=.o)

CFLAGS = -Wall -Wextra -Werror
CC = cc
RM = rm -f

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	@$(CC) $(CFLAGS) $(SOURCES) /here the path to libft/ -o $(NAME)
	$(info CREATED $(NAME))

clean:
	$(RM) $(OBJECTS)
	$(info REMOVED OBJECTS)

compclean: all clean

fclean: clean
	@$(RM) $(NAME)
	$(info REMOVED $(NAME))

re: fclean all

.PHONY: all clean fclean re compclean
