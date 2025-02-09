/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:11:06 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/09 12:32:40 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char g_whitespace[] = " \t\r\n\v";
// static char g_symbols[] = "<|>&;()\"'";
int	get_token_append(char **ps, char *s)
{
	int	ret;

	ret = *s;
	s++;
	if (*s == '>')
	{
		ret = '+';
		s++;
	}
	else if (*s == '<')
	{
		ret = 'h';
		s++;
	}
	*ps = s;
	return (ret);
}

int	get_token_word(char **ps, char *es, char *s)
{
	while (s < es && !strchr(WHITESPACE, *s) && !strchr(SYMBOLS, *s))
		s++;
	*ps = s;
	return ('a');
}

int	gettoken(char **ps, char *es, char **q, char **eq)
{
	char	*s;
	int		ret;

	s = *ps;
	while (s < es && strchr(WHITESPACE, *s))
		s++;
	if (q)
		*q = s;
	ret = *s;
	if (*s == 0)
		return (0);
	else if (strchr("|();&", *s))
		*ps = s + 1;
	else if (*s == '>' || *s == '<')
		ret = get_token_append(ps, s);
	else
		ret = get_token_word(ps, es, s);
	if (eq)
		*eq = *ps;
	while (*ps < es && strchr(WHITESPACE, **ps))
		(*ps)++;
	// printf("token: %c\n", ret);
	return (ret);
}

int	peek(char **ps, char *es, char *toks)
{
	char	*s;

	s = *ps;
	while (s < es && strchr(WHITESPACE, *s))
		s++;
	*ps = s;
	return (*s && strchr(toks, *s));
}
