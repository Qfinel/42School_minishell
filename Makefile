# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/24 16:07:27 by jtsizik           #+#    #+#              #
#    Updated: 2022/12/17 11:03:20 by jtsizik          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	gcc *.c builtins/*.c libft/*.c -L$$HOME/.brew/opt/readline/lib -lreadline -I$$HOME/.brew/opt/readline/include -Wno-gnu-include-next -I../LeakSanitizer/include -L../LeakSanitizer -llsan -lc++ -lreadline -o minishell

# -Wno-gnu-include-next -I../LeakSanitizer/include -L../LeakSanitizer -llsan -lc++