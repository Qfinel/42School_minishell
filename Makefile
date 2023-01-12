# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/24 16:07:27 by jtsizik           #+#    #+#              #
#    Updated: 2023/01/12 17:36:53 by jtsizik          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

HDRS =	minishell.h

OBJS =	obj/main.o \
		obj/utils.o \
		obj/free_utils.o \
		obj/ft_split_pipes.o \
		obj/signals.o \
		obj/ft_cd.o \
		obj/ft_cd_utils.o \
		obj/ft_echo.o \
		obj/ft_env.o \
		obj/ft_export.o \
		obj/ft_pwd.o \
		obj/ft_unset.o \
		obj/ft_unset_utils.o \
		obj/exec_cmd.o \
		obj/exec_pipes.o \
		obj/heredoc_utils.o \
		obj/parse_cmd.o \
		obj/parse_pipes.o \
		obj/parse_redirections.o \
		obj/parsing_utils.o \
		obj/handle_quotes.o \
		obj/handle_envvars.o \
		obj/envvars_utils.o \
		obj/quotes_utils.o \
		obj/envvars_utils2.o

RL_FLAGS = -L$$HOME/.brew/opt/readline/lib -lreadline -I$$HOME/.brew/opt/readline/include -lreadline

# BREW = /opt/homebrew/Cellar/readline/8.2.1

# RL_FLAGS = -L $(BREW)/lib -lreadline -I $(BREW)/include -lreadline

CFLAGS = -Wall -Wextra -Werror

obj/%.o: %.c
	cc -c $(CFLAGS) -I$$HOME/.brew/opt/readline/include $< -o $@

# obj/%.o: %.c
# 	cc -c $(CFLAGS) -I $(BREW)/include $< -o $@

obj/%.o: builtins/%.c
	cc -c $(CFLAGS)  $< -o $@

obj/%.o: executor/%.c
	cc -c $(CFLAGS)  $< -o $@

obj/%.o: parser/%.c
	cc -c $(CFLAGS)  $< -o $@

obj/%.o: lexer/%.c
	cc -c $(CFLAGS)  $< -o $@

obj/%.o: utils/%.c
	cc -c $(CFLAGS)  -I$$HOME/.brew/opt/readline/include $< -o $@

# obj/%.o: utils/%.c
# 	cc -c $(CFLAGS)  -I $(BREW)/include $< -o $@

$(NAME): obj $(OBJS)
	cd libft && make
	cd ..
	cc $(CFLAGS) $(RL_FLAGS) libft/libft.a $(OBJS) -o $(NAME)

all: $(NAME)

obj:
	mkdir obj

clean:
	rm -rf obj
	cd libft && make clean
	cd ..

fclean: clean
	rm -f $(NAME)
	cd libft && make fclean
	cd ..

re: fclean all

debug: obj $(OBJS)
	cd libft && make
	cd ..
	cc $(CFLAGS) $(RL_FLAGS) $(OBJS) libft/libft.a -g -Wno-gnu-include-next -I../LeakSanitizer/include -L../LeakSanitizer -llsan -lc++ -o $(NAME)

debug_only: CFLAGS += -g -fsanitize=address
debug_only: re

install:
	@which brew || curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install readline

.PHONY: all clean fclean re debug debug_only install
