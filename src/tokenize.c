/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:34:47 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/02 13:45:09 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// # define WHITESPACES " \t\r\n\v"
// # define SYMBOLS "<|>&;()\"'"
/*
	check_double_chars
	functions checks for here_doc
	symbols or append sybols being passed
*/
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

/*
	ft_gettoken
	tokeinzes first symbol it finds in the user_input
	it returns one char(ascii code) for every word
	separated by spaces.
*/
int	ft_gettoken(char **ps, char *es, char **q, char **eq)
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
