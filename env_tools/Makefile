NAME = libenvtools.a

FILES = env_dup.c \
		env_free_i.c \
		env_free.c \
		env_app.c \
		env_count.c \
		env_print.c \
		env_grab.c \
		env_grabentry.c \
		env_newentry.c \
		env_index.c \
		env_del.c \
		env_entry_name.c \
		env_entry_value.c \
		env_entry_grab.c \
		env_print_export.c

OBJS = $(FILES:.c=.o)

CC = cc
INCLUDE = -I ../include
CFLAGS = -Wall -Werror -Wextra

# COLORS

DEF_COLOR = \e[1;39m
RESET = \e[0m
GRAY = \e[1;90m
RED = \e[1;91m
YELLOW = \e[1;93m
GREEN = \e[1;92m
BLUE = \e[1;94m
MAGENTA = \e[1;95m
CYAN = \e[1;96m
WHITE = \e[1;97m
BLINK = \e[5m

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "$(GREEN)✔ $(MAGENTA)created $(GREEN)$(NAME)$(MAGENTA)!$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "· compiling env_tools/$<"

clean: 
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all fclean clean re