# **************************************************************** #
#                                                                  #
#        :::        ::::::::::: :::::::::  :::::::::: :::::::::::  #
#       :+:            :+:     :+:    :+: :+:            :+:       #
#      +:+            +:+     +:+    +:+ +:+            +:+        #
#     +#+            +#+     +#++:++#+  :#::+::#       +#+         #
#    +#+            +#+     +#+    +#+ +#+            +#+          #
#   #+#            #+#     #+#    #+# #+#            #+#           #
#  ########## ########### #########  ###            ###            #
#                                                                  #
# **************************************************************** #

NAME = libft.a

FILES = ft_strchr.c    \
		ft_strlen.c    \
		ft_calloc.c    \
		ft_strcat.c    \
		ft_isspace.c   \
		ft_strndup.c   \
		ft_strcmp.c    \
		ft_strdup.c    \
		ft_strncpy.c   \
		ft_strjoin.c   \
		ft_isalpha.c   \
		ft_charjoin.c  \
		ft_strlcpy.c   \
		ft_putstr_fd.c \
		ft_memzero.c   \
		ft_strncmp.c   \
		ft_split.c

OBJS = $(FILES:.c=.o)

CC = cc
INCLUDE = -I ../include
CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "· compiling libft/$<"

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all fclean clean re