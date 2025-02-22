/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:41:54 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/22 17:50:11 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

bool	ft_isstralnum(char *str)
{
	int		i;
	bool	has_digit;

	if (!str)
		return (false);
	i = 0;
	has_digit = false;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			has_digit = true;
		i++;
	}
	return (has_digit);
}

void	ft_close_descriptors(int *p)
{
	close(p[0]);
	close(p[1]);
	close(0);
	close(1);
	close(2);
}

bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

bool	is_empty_or_spaces(const char *str)
{
	if (!str)
		return (true);
	while (*str)
	{
		if (!ft_isspace(*str))
			return (false);
		str++;
	}
	return (true);
}
