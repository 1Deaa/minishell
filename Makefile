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

FILES = main.c \
		signals.c signals_utils.c \
		shell.c shell_utils.c \
		token.c token_utils.c \
		syntax.c syntax_utils.c \
		expand.c expand_utils.c \
		parse.c parse_redir.c parse_utils.c parse_print.c heredoc.c \
		exec.c exec_utils.c \
		find_path.c \
		bn_echo.c bn_env.c bn_export.c bn_pwd.c bn_cd.c bn_exit.c \
		error.c \
		envp.c 

CC = cc
RM = rm -rf
CFLAGS = -Wall -Werror -Wextra -g
LINK = -lreadline -lncurses libft/libft.a ft_printf/libftprintf.a
INCLUDE = -I include
MAKEFLAGS += --no-print-directory

SRC_DIR = src
OBJ_DIR = obj

SRC = $(addprefix $(SRC_DIR)/, $(FILES))
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	@make -C ft_printf
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LINK)
	@echo "./$(NAME) was created!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "· compiling $<"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@make -C libft clean
	@make -C ft_printf clean
	@echo "deleted all object files."
	@$(RM) $(OBJ_DIR)

fclean: clean
	@make -C libft fclean
	@make -C ft_printf fclean
	@$(RM) $(NAME)
	@echo "./$(NAME) was deleted."

re: fclean all

.PHONY: all fclean clean re
