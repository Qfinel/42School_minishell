/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:56:13 by sdukic            #+#    #+#             */
/*   Updated: 2023/01/02 15:08:02 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

char	get_opening_quote(char quote, char c)
{
	if (quote == 0 && is_quote(c))
	{
		quote = c;
	}
	else if (quote == c)
	{
		quote = 0;
	}
	return (quote);
}
