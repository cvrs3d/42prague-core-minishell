/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:18:05 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/08 17:46:05 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_exec_cmd(t_execcmd *ecmd)
{
	if (ecmd->argv[0] == 0)
		exit(0);
	if (ft_try_find_cmd(ecmd) == -1)
	{
		fprintf(stderr, "command %s not found\n", ecmd->argv[0]);
		return ;
	}
	execve(ecmd->argv[0], ecmd->argv, NULL);
	fprintf(stderr, "exec %s failed\n", ecmd->argv[0]);
}

static void	handle_redir_cmd(t_redircmd *rcmd)
{
	close(rcmd->fd);
	if (open(rcmd->file, rcmd->mode, 0644) < 0)
	{
		fprintf(stderr, "open %s failed\n", rcmd->file);
		exit(1);
	}
	runcmd(rcmd->cmd);
}

static void	handle_pipe_cmd(t_pipecmd *pcmd)
{
	int	p[2];

	if (pipe(p) < 0)
		panic("pipe");
	if (fork1() == 0)
	{
		close(1);
		dup(p[1]);
		close(p[0]);
		close(p[1]);
		runcmd(pcmd->left);
	}
	if (fork1() == 0)
	{
		close(0);
		dup(p[0]);
		close(p[0]);
		close(p[1]);
		runcmd(pcmd->right);
	}
	close(p[0]);
	close(p[1]);
	wait(0);
	wait(0);
}

static void	handle_list_cmd(t_listcmd *lcmd)
{
	if (fork1() == 0)
		runcmd(lcmd->left);
	wait(0);
	runcmd(lcmd->right);
}

void	runcmd(t_cmd *cmd)
{
	if (cmd == 0)
		exit(0);
	if (cmd->type == EXEC)
		handle_exec_cmd((t_execcmd *)cmd);
	else if (cmd->type == REDIR)
		handle_redir_cmd((t_redircmd *)cmd);
	else if (cmd->type == LIST)
		handle_list_cmd((t_listcmd *)cmd);
	else if (cmd->type == PIPE)
		handle_pipe_cmd((t_pipecmd *)cmd);
	else if (cmd->type == BACK)
	{
		if (fork1() == 0)
			runcmd(((t_backcmd *)cmd)->cmd);
	}
	else
		panic("runcmd");
	exit(0);
}
// void runcmd(t_cmd *cmd)
// {
// 	t_backcmd *bcmd;
// 	t_execcmd *ecmd;
// 	t_listcmd *lcmd;
// 	t_pipecmd *pcmd;
// 	t_redircmd *rcmd;

// 	if (cmd == 0)
// 		exit(0);
// 	switch (cmd->type)
// 	{
// 	case EXEC:
// 		ecmd = (t_execcmd *)cmd;
// 		handle_exec_cmd(ecmd);
// 		break;
// 	case REDIR:
// 		rcmd = (t_redircmd *)cmd;
// 		handle_redir_cmd(rcmd);
// 		break;
// 	case LIST:
// 		lcmd = (t_listcmd *)cmd;
// 		handle_list_cmd(lcmd);
// 		break;
// 	case PIPE:
// 		pcmd = (t_pipecmd *)cmd;
// 		handle_pipe_cmd(pcmd);
// 		break;
// 	case BACK:
// 		bcmd = (t_backcmd *)cmd;
// 		if (fork1() == 0)
// 			runcmd(bcmd->cmd);
// 		break;
// 	default:
// 		panic("runcmd");
// 	}
// 	exit(0);
// }
