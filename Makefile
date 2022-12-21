# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/24 16:07:27 by jtsizik           #+#    #+#              #
#    Updated: 2022/12/19 16:09:51 by sdukic           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

HDRS =	minishell.h

OBJS =	obj/main.o \
		obj/redirections.o \
		obj/utils.o \
		obj/ft_cd.o \
		obj/ft_echo.o \
		obj/ft_env.o \
		obj/ft_export.o \
		obj/ft_pwd.o \
		obj/ft_unset.o \
		obj/handle_envvars.o \
		obj/handle_quotes.o

RL_FLAGS = -L$$HOME/.brew/opt/readline/lib -lreadline -I$$HOME/.brew/opt/readline/include -lreadline

FLAGS =

obj/%.o: %.c
	cc -c $(FLAGS) -I$$HOME/.brew/opt/readline/include $< -o $@

obj/%.o: builtins/%.c
	cc -c -Wall -Wextra -Werror $< -o $@

$(NAME): obj $(OBJS)
	cd libft && make
	cd ..
	cc $(FLAGS) $(RL_FLAGS) libft/libft.a $(OBJS) -o $(NAME)

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

debug_only: obj $(OBJS)
	cd libft && make
	cd ..
	cc -fsanitize=address *.c builtins/*.c libft/*.c -g -L$$HOME/.brew/opt/readline/lib -lreadline -I$$HOME/.brew/opt/readline/include -lreadline -o $(NAME)
	# cc -Wall -Wextra -Werror -f $(RL_FLAGS) libft/libft.a -g $(OBJS) -o $(NAME)
