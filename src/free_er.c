/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_er.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:15:14 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/19 17:33:48 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_non_fork_cd(char **argv)
{
	int	argc;

	if (!argv || !argv[0])
		return (false);
	argc = 0;
	while (argv[argc])
		argc++;
	return (argc <= 2);
}

static void	free_exec(t_execcmd *ecmd)
{
	if (!ecmd)
		return ;
	free(ecmd);
}

static void	free_redir(t_redircmd *rcmd)
{
	if (!rcmd)
		return ;
	free_tree(rcmd->cmd);
	free(rcmd->file);
	free(rcmd);
}

void	free_tree(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->type == EXEC)
		free_exec((t_execcmd *)cmd);
	else if (cmd->type == REDIR)
		free_redir((t_redircmd *)cmd);
	else if (cmd->type == PIPE)
		free_pipe((t_pipecmd *)cmd);
	else if (cmd->type == LIST)
		free_list((t_listcmd *)cmd);
	else if (cmd->type == AND)
		free_and((t_andcmd *)cmd);
	else if (cmd->type == OR)
		free_or((t_orcmd *)cmd);
	else if (cmd->type == BACK)
		free_back((t_backcmd *)cmd);
	else
		return ;
}
