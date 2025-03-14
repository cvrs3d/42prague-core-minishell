/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:01:03 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/22 20:32:39 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Parses a block of commands from a string
 *
 * @param ps    Pointer to pointer to the current position in the input string
 * @param es    Pointer to the end of the input string
 * @return      Pointer to the parsed command structure (t_cmd)
 *

* This function parses a block of commands from the input string starting at *ps
 * until it reaches es. It handles command blocks enclosed in parentheses and
 * returns a parsed command structure.
 */
t_cmd	*parseblock(char **ps, char *es)
{
	t_cmd	*cmd;

	if (!peek(ps, es, "("))
	{
		ft_putendl_fd("Missing ')' ", 2);
		return (NULL);
	}
	gettoken(ps, es, 0, 0);
	cmd = parseline(ps, es);
	if (!cmd)
		return (NULL);
	if (!peek(ps, es, ")"))
	{
		ft_putendl_fd("Missing ')' ", 2);
		return (free_tree(cmd), NULL);
	}
	gettoken(ps, es, 0, 0);
	cmd = parseredirs(cmd, ps, es);
	return (cmd);
}

/**
 * Parses and processes redirection
 * operators and their corresponding files in the command
 *
 * @param cmd The command structure to store the redirection information
 * @param ps Pointer to the current position in the input string
 * @param es Pointer to the end of the input string
 *
 * @return Modified command structure with
 * redirection information, or NULL if parsing fails
 */
t_cmd	*parseredirs(t_cmd *cmd, char **ps, char *es)
{
	int		tok;
	char	*q;
	char	*eq;

	while (peek(ps, es, "<>"))
	{
		tok = gettoken(ps, es, 0, 0);
		if (gettoken(ps, es, &q, &eq) != 'a')
		{
			ft_putendl_fd("Missing redirection", 2);
			return (free_tree(cmd), NULL);
		}
		if (tok == '<')
			cmd = redircmd(cmd, q, eq, STDIN);
		else if (tok == '>')
			cmd = redircmd(cmd, q, eq, STDOUT);
		else if (tok == '+')
			cmd = redircmd(cmd, q, eq, APPEND);
		else if (tok == 'h')
			cmd = redircmd(cmd, q, eq, HEREDOC);
	}
	return (cmd);
}

/**
 * @brief Parses a pipe command from a command string
 *
 * @param ps Pointer to the current position in the command string
 * @param es Pointer to the end of the command string
 * @return t_cmd* Pointer to the parsed
 * command structure, or NULL if parsing fails
 *
 * This function parses a pipe command from the input string and creates
 * appropriate command structures. It handles the parsing of commands
 * separated by the pipe operator '|'.
 */
t_cmd	*parsepipe(char **ps, char *es)
{
	t_cmd	*cmd;
	int		tok;

	cmd = parseexec(ps, es);
	if (!cmd)
		return (NULL);
	if (peek(ps, es, "|&"))
	{
		tok = gettoken(ps, es, 0, 0);
		if (tok == '!' || tok == '?')
		{
			if (tok == '!')
				cmd = orcmd(cmd, parsepipe(ps, es));
			else
				cmd = andcmd(cmd, parsepipe(ps, es));
		}
		else
			cmd = pipecmd(cmd, parsepipe(ps, es));
	}
	return (cmd);
}

/**
 * Parses a command line.
 *
 * @param ps Pointer to the current position in the input string.
 * @param es Pointer to the end of the input string.
 * @return A pointer to the parsed command structure.
 */
t_cmd	*parseline(char **ps, char *es)
{
	t_cmd	*cmd;

	cmd = parsepipe(ps, es);
	if (!cmd)
		return (NULL);
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
