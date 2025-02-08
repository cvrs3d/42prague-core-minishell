/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:01:03 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/08 19:10:02 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parseblock(char **ps, char *es)
{
	t_cmd	*cmd;

	if (!peek(ps, es, "("))
		panic("parseblock");
	gettoken(ps, es, 0, 0);
	cmd = parseline(ps, es);
	if (!peek(ps, es, ")"))
		panic("syntax - missing )");
	gettoken(ps, es, 0, 0);
	cmd = parseredirs(cmd, ps, es);
	return (cmd);
}

t_cmd	*parseredirs(t_cmd *cmd, char **ps, char *es)
{
	int		tok;
	char	*q;
	char	*eq;

	while (peek(ps, es, "<>"))
	{
		tok = gettoken(ps, es, 0, 0);
		if (gettoken(ps, es, &q, &eq) != 'a')
			panic("Missing file for redirection");
		if (tok == '<')
			cmd = redircmd(cmd, q, eq, STDOUT);
		else if (tok == '>')
			cmd = redircmd(cmd, q, eq, STDIN);
		else if (tok == '+')
			cmd = redircmd(cmd, q, eq, APPEND);
		else if (tok == 'h')
			cmd = redircmd(cmd, q, eq, HEREDOC);
	}
	return (cmd);
}

t_cmd	*parsepipe(char **ps, char *es)
{
	t_cmd	*cmd;

	cmd = parseexec(ps, es);
	if (peek(ps, es, "|"))
	{
		gettoken(ps, es, 0, 0);
		cmd = pipecmd(cmd, parsepipe(ps, es));
	}
	return (cmd);
}

t_cmd	*parseline(char **ps, char *es)
{
	t_cmd	*cmd;

	cmd = parsepipe(ps, es);
	while (peek(ps, es, "&"))
	{
		gettoken(ps, es, 0, 0);
		cmd = backcmd(cmd);
	}
	if (peek(ps, es, ";"))
	{
		gettoken(ps, es, 0, 0);
		cmd = listcmd(cmd, parseline(ps, es));
	}
	return (cmd);
}
