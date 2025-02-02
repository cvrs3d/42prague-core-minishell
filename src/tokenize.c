/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:34:47 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/02 12:08:20 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// # define WHITESPACES " \t\r\n\v"
// # define SYMBOLS "<|>&;()\"'"

static void	check_double_chars(char **s, int *ret)
{
	(*s)++;
	if (**s == '<')
	{
		*ret = 'h';
		(*s)++;
	}
	else if (**s == '>')
	{
		*ret = '+';
		(*s)++;
	}
	return ;
}

int	gettoken(char **ps, char *es, char **q, char **eq)
{
	char *s;
	int ret;

	s = *ps;
	while (s < es && strchr(WHITESPACES, *s))
		s++;
	if (q)
		*q = s;
	ret = *s;
	if (*s == 0)
	{
		// End of input
	}
	else if (strchr("|();&\"'$", *s))
		s++;
	else if (strchr("><", *s))
		check_double_chars(&s, &ret);
	else
	{
		ret = 'a';
		while (s < es && !strchr(WHITESPACES, *s) && !strchr(SYMBOLS, *s))
			s++;
	}
	if (eq)
		*eq = s;
	while (s < es && strchr(WHITESPACES, *s))
		s++;
	*ps = s;
	return ret;
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
