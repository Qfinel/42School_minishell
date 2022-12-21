# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/24 16:07:27 by jtsizik           #+#    #+#              #
#    Updated: 2022/12/21 15:59:55 by jtsizik          ###   ########.fr        #
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
		obj/parse_redirections.o

RL_FLAGS = -L$$HOME/.brew/opt/readline/lib -lreadline -I$$HOME/.brew/opt/readline/include -lreadline

obj/%.o: %.c
	cc -c -Wall -Wextra -Werror -I$$HOME/.brew/opt/readline/include $< -o $@

obj/%.o: builtins/%.c
	cc -c -Wall -Wextra -Werror $< -o $@

obj/%.o: executor/%.c
	cc -c -Wall -Wextra -Werror $< -o $@

obj/%.o: parser/%.c
	cc -c -Wall -Wextra -Werror $< -o $@

obj/%.o: utils/%.c
	cc -c -Wall -Wextra -Werror -I$$HOME/.brew/opt/readline/include $< -o $@

$(NAME): obj $(OBJS)
	cd libft && make
	cd ..
	cc -Wall -Wextra -Werror $(RL_FLAGS) libft/libft.a $(OBJS) -o $(NAME)

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