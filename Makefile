# ******************************************************************************************************* #
#                                                                                                         #
#        :::::::: ::::::::::: :::     :::::::::          ::::::::  :::    ::: :::::::::: :::        :::   #
#      :+:    :+:    :+:   :+: :+:   :+:    :+:        :+:    :+: :+:    :+: :+:        :+:        :+:    #
#     +:+           +:+  +:+   +:+  +:+    +:+        +:+        +:+    +:+ +:+        +:+        +:+     #
#    +#++:++#++    +#+ +#++:++#++: +#++:++#:         +#++:++#++ +#++:++#++ +#++:++#   +#+        +#+      #
#          +#+    +#+ +#+     +#+ +#+    +#+               +#+ +#+    +#+ +#+        +#+        +#+       #
#  #+#    #+#    #+# #+#     #+# #+#    #+#        #+#    #+# #+#    #+# #+#        #+#        #+#        #
#  ########     ### ###     ### ###    ###         ########  ###    ### ########## ########## ##########  #
#                                                                                                         #
# ******************************************************************************************************* #

NAME = minishell

FILES = main.c		\
		signals.c	\
		echo.c		\
		shell.c shell_utils.c	\
		token.c token_utils.c	\
		syntax.c syntax_utils.c \
		expand.c expand_utils.c \
		parse.c	parse_utils.c parse_print.c parse_clean.c \
		envp.c \
		exec.c


CC = cc
RM = rm -rf
CFLAGS = -Wall -Werror -Wextra
LINK = -lreadline -lncurses libft/libft.a
INCLUDE = -I include
MAKEFLAGS += --no-print-directory

SRC_DIR = src
OBJ_DIR = obj

SRC = $(addprefix $(SRC_DIR)/, $(FILES))
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LINK)
	@echo "./$(NAME) was created!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "· compiling $<"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@make -C libft clean
	@echo "deleted all object files."
	@$(RM) $(OBJ_DIR)

fclean: clean
	@make -C libft fclean
	@$(RM) $(NAME)
	@echo "./$(NAME) was deleted."

re: fclean all

.PHONY: all fclean clean re
