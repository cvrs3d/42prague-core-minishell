/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:11:06 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/10 17:22:39 by yustinov         ###   ########.fr       */
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

/*
	For no skip anything in quotes no matter " or '
*/
int	get_token_quoted(char **ps, char *es, char *s, char **q, char **eq)
{
	char	quote;
	char	*start;

	quote = *s;
	start = s;
	s++;
	if (q)
		*q = s;
	while (s < es && *s != quote)
		s++;
	if (s >= es)
	{
		*ps = start + 1;
		return ('a');
	}
	if (eq)
		*eq = s;
	s++;
	*ps = s;
	return ('a');
}

/**
 * Gets the next token from the input string.
 *
 * @param ps Pointer to the current position in the input string
 * @param es Pointer to the end of the input string
 * @param q  Pointer to store the start of the token
 * @param eq Pointer to store the end of the token
 *
 * @return Token type identifier
 */
int	gettoken(char **ps, char *es, char **q, char **eq)
{
	char	*s;
	int		ret;
	int		qt;

	s = *ps;
	qt = 0;
	while (s < es && strchr(WHITESPACE, *s))
		s++;
	if (q)
		*q = s;
	ret = *s;
	if (*s == 0)
		return (0);
	else if (strchr("\"\'", *s))
		return (get_token_quoted(ps, es, s, q, eq));
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
