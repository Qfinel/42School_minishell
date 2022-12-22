# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/24 16:07:27 by jtsizik           #+#    #+#              #
#    Updated: 2022/12/22 16:17:33 by sdukic           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

HDRS =	minishell.h

OBJS =	obj/main.o \
		obj/parse_redirections.o \
		obj/utils.o \
		obj/ft_cd.o \
		obj/ft_echo.o \
		obj/ft_env.o \
		obj/ft_export.o \
		obj/ft_pwd.o \
		obj/ft_unset.o \
		obj/handle_envvars.o \
		obj/handle_quotes.o \
		obj/exec_cmd.o \
		obj/exec_pipes.o \
		obj/parse_cmd.o

RL_FLAGS = -L$$HOME/.brew/opt/readline/lib -lreadline -I$$HOME/.brew/opt/readline/include -lreadline

CFLAGS =

obj/%.o: %.c
	cc $(CFLAGS) -c $(FLAGS) -I$$HOME/.brew/opt/readline/include $< -o $@

obj/%.o: builtins/%.c
	cc $(CFLAGS) -c -Wall -Wextra -Werror $< -o $@

obj/%.o: executor/%.c
	cc $(CFLAGS) -c -Wall -Wextra -Werror $< -o $@

obj/%.o: parser/%.c
	cc $(CFLAGS) -c -Wall -Wextra -Werror $< -o $@

obj/%.o: utils/%.c
	cc $(CFLAGS) -c -I$$HOME/.brew/opt/readline/include $< -o $@

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
	cc -Wall -Wextra -Werror $(RL_FLAGS) $(OBJS) libft/libft.a -g -Wno-gnu-include-next -I../LeakSanitizer/include -L../LeakSanitizer -llsan -lc++ -o $(NAME)

debug_only: CFLAGS += -g
debug_only: $(NAME)
