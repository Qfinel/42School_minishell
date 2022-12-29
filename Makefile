# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/24 16:07:27 by jtsizik           #+#    #+#              #
#    Updated: 2022/12/27 15:50:26 by jtsizik          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

HDRS =	minishell.h

OBJS =	obj/main.o \
		obj/utils.o \
		obj/free_utils.o \
		obj/ft_split_charset.o \
		obj/ft_cd.o \
		obj/ft_echo.o \
		obj/ft_env.o \
		obj/ft_export.o \
		obj/ft_pwd.o \
		obj/ft_unset.o \
		obj/exec_cmd.o \
		obj/exec_pipes.o \
		obj/parse_cmd.o \
		obj/parse_redirections.o \
		obj/handle_quotes.o \
		obj/handle_envvars.o

BREW = $(shell echo "$(brew --cellar readline)/$(brew list --versions readline | tr ' ' '\n' | tail -1)")

BREW = /opt/homebrew/Cellar/readline/8.2.1

RL_FLAGS = -L $(BREW)/lib -lreadline -I $(BREW)/include -lreadline

CFLAGS = -Wall -Wextra -Werror

obj/%.o: %.c
	cc -c $(CFLAGS) -I $(BREW)/include $< -o $@

obj/%.o: builtins/%.c
	cc -c $(CFLAGS)  $< -o $@

obj/%.o: executor/%.c
	cc -c $(CFLAGS)  $< -o $@

obj/%.o: parser/%.c
	cc -c $(CFLAGS)  $< -o $@

obj/%.o: lexer/%.c
	cc -c $(CFLAGS)  $< -o $@

obj/%.o: utils/%.c
	cc -c $(CFLAGS)  -I $(BREW)/include $< -o $@

$(NAME): obj $(OBJS)
	cd libft && make
	cd ..
	cc $(CFLAGS) $(RL_FLAGS) libft/libft.a $(OBJS) -o $(NAME)

all: $(NAME)

obj:
	mkdir obj

clean:
	rm -rf obj

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: obj $(OBJS)
	cd libft && make
	cd ..
	cc $(CFLAGS) $(RL_FLAGS) $(OBJS) libft/libft.a -g -Wno-gnu-include-next -I../LeakSanitizer/include -L../LeakSanitizer -llsan -lc++ -o $(NAME)

debug_only: CFLAGS += -g
debug_only: re

