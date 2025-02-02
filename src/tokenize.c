/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:34:47 by yustinov          #+#    #+#             */
/*   Updated: 2025/01/31 16:19:55 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_gettoken(char **ps, char *es, char **q, char **eq)
{
	char	*s;
	int		ret;

	s = *ps;
	while (s < es && ft_strchr(WHITESPACES, *s))
		s++;
	if (q)
		*q = s;
	ret = *s;
	if (*s != 0 && (ft_strchr(SYMBOLS, *s)))
	{
		if (*s == '>')
		{
			
		}
	}

}

// int gettoken(char **ps, char *es, char **q, char **eq)
// {
// 	char *s;
// 	int ret;

// 	s = *ps;
// 	while (s < es && strchr(whitespace, *s))
// 		s++;
// 	if (q)
// 		*q = s;
// 	ret = *s;
// 	switch (*s)
// 	{
// 	case 0:
// 		break;
// 	case '|':
// 	case '(':
// 	case ')':
// 	case ';':
// 	case '&':
// 	case '<':
// 		s++;
// 		break;
// 	case '>':
// 		s++;
// 		if (*s == '>')
// 		{
// 			ret = '+';
// 			s++;
// 		}
// 		break;
// 	default:
// 		ret = 'a';
// 		while (s < es && !strchr(whitespace, *s) && !strchr(symbols, *s))
// 			s++;
// 		break;
// 	}
// 	if (eq)
// 		*eq = s;
// 	while (s < es && strchr(whitespace, *s))
// 		s++;
// 	*ps = s;
// 	return ret;
// }
