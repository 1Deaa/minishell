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
		token.c token_utils.c token_re.c token_filter.c \
		syntax.c syntax_utils.c \
		expand.c expand_utils.c expand_utils2.c \
		parse.c parse_redir.c parse_utils.c parse_print.c heredoc.c heredoc_utils.c \
		exec.c exec_utils.c exec_utils2.c \
		find_path.c \
		bn_echo.c bn_env.c bn_export.c bn_pwd.c bn_cd.c bn_exit.c bn_unset.c \
		error.c 

CC = cc
RM = rm -rf
CFLAGS = -Wall -Werror -Wextra -g

LIBFT_A = libft/libft.a
FT_PRINTF_A = ft_printf/libftprintf.a
ENVTOOLS_A = env_tools/libenvtools.a

LINK = -lreadline -lncurses $(LIBFT_A) $(FT_PRINTF_A) $(ENVTOOLS_A)
INCLUDE = -I include
MAKEFLAGS += --no-print-directory

SRC_DIR = src
OBJ_DIR = obj

SRC = $(addprefix $(SRC_DIR)/, $(FILES))
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

all: libft printf envtools $(NAME)

libft:
	@make -C libft

printf:
	@make -C ft_printf

envtools:
	@make -C env_tools

$(NAME): $(LIBFT_A) $(FT_PRINTF_A) $(ENVTOOLS_A) $(OBJS)
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
	@make -C env_tools clean
	@echo "deleted all object files."
	@$(RM) $(OBJ_DIR)

fclean: clean
	@make -C libft fclean
	@make -C ft_printf fclean
	@make -C env_tools fclean
	@$(RM) $(NAME)
	@echo "./$(NAME) was deleted."

re: fclean all

.PHONY: all fclean clean re libft printf envtools
