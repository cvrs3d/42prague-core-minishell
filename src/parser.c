/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:11:47 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/22 20:34:26 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd			*parseexec(char **ps, char *es);
t_cmd			*nulterminate(t_cmd *cmd);

static void	process_token(t_execcmd *cmd, int *argc, char *q, char *eq)
{
	if (!cmd)
		return ;
	cmd->argv[*argc] = q;
	cmd->eargv[*argc] = eq;
	(*argc)++;
	if (*argc > MAXARGS)
		panic("too many args", EXIT_MINISHEL_ERR, NULL);
}

/**
 * Parses command arguments from the input string.
 *
 * @param ret Pointer to the command structure to be populated
 * @param ps  Pointer to the current position in the input string
 * @param es  Pointer to the end of the input string
 *
 * @return Pointer to the populated command structure after parsing arguments
 */
static t_cmd	*parse_arguments(t_cmd *ret, char **ps, char *es)
{
	t_execcmd	*cmd;
	char		*q;
	char		*eq;
	int			argc;
	int			tok;

	cmd = (t_execcmd *)ret;
	if (!cmd)
		return (NULL);
	argc = 0;
	while (!peek(ps, es, "|)&;"))
	{
		tok = gettoken(ps, es, &q, &eq);
		if (tok == 0)
			break ;
		if (tok != 'a')
			return (NULL);
		process_token(cmd, &argc, q, eq);
		ret = parseredirs(ret, ps, es);
	}
	if (cmd->argv[argc] == NULL && cmd->eargv[argc] == NULL)
		ft_norm1(cmd->argv[argc], cmd->eargv[argc]);
	return (ret);
}

t_cmd	*parseexec(char **ps, char *es)
{
	t_cmd	*ret;

	if (peek(ps, es, "("))
		return (parseblock(ps, es));
	ret = execcmd();
	ret = parseredirs(ret, ps, es);
	if (!ret)
		return (NULL);
	ret = parse_arguments(ret, ps, es);
	if (!ret)
		return (NULL);
	return (ret);
}

/**
 * Parses a command string and creates a command structure
 *
 * @param s The command string to parse
 * @return Returns a pointer to the parsed command structure (t_cmd)
 *         or NULL if parsing fails
 *
 * This function takes a command string as input and converts it into
 * a structured command representation that can be executed by the shell.
 * The resulting structure contains all necessary information about the
 * command including its type, arguments, and any redirections.
 */
t_cmd	*parsecmd(char *s)
{
	char	*es;
	t_cmd	*cmd;

	es = s + ft_strlen(s);
	cmd = parseline(&s, es);
	peek(&s, es, "");
	if (s != es)
	{
		ft_putendl_fd("leftovers: ", 2);
		ft_putendl_fd(s, 2);
		free_tree(cmd);
		return (NULL);
	}
	nulterminate(cmd);
	return (cmd);
}

/**
 * @brief Null terminates a command structure
 *
 * This function adds null termination to the
 * command structure and its components.
 * It's used to ensure proper termination of command strings and arguments.
 *
 * @param cmd Pointer to the command structure to be null terminated
 * @return Pointer to the null terminated command structure
 */
t_cmd	*nulterminate(t_cmd *cmd)
{
	if (cmd == 0)
		return (0);
	if (cmd->type == EXEC)
		handle_exec_null((t_execcmd *)cmd);
	else if (cmd->type == REDIR)
		handle_redir_null((t_redircmd *)cmd);
	else if (cmd->type == PIPE)
		handle_pipe_null((t_pipecmd *)cmd);
	else if (cmd->type == LIST)
		handle_list_null((t_listcmd *)cmd);
	else if (cmd->type == BACK)
		handle_back_null((t_backcmd *)cmd);
	else if (cmd->type == OR)
		handle_or_null((t_orcmd *)cmd);
	else if (cmd->type == AND)
		handle_and_null((t_andcmd *)cmd);
	return (cmd);
}
