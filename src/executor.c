/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:18:05 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/13 16:22:01 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_exec_cmd(t_execcmd *ecmd, t_shell *sh)
{
	int	builtin;

	if (ecmd->argv[0] == 0)
		exit(0);
	builtin = check_builtins(ecmd->argv, sh);
	if (builtin != NO_BUILTIN_FOUND)
	{
		sh->e_code = builtin;
		return ;
	}
	if (ft_try_find_cmd(ecmd, sh) == -1)
	{
		fprintf(stderr, "command %s not found\n", ecmd->argv[0]);
		return ;
	}
	execve(ecmd->argv[0], ecmd->argv, sh->envp);
}

static void	handle_redir_cmd(t_redircmd *rcmd, t_shell *sh)
{
	int	fd;

	if (rcmd->mode == HEREDOC)
		handle_heredoc_cmd(rcmd->file);
	else
	{
		close(rcmd->fd);
		fd = open(rcmd->file, rcmd->mode, 0644);
		if (fd < 0)
		{
			fprintf(stderr, "open %s failed\n", rcmd->file);
			exit(1);
		}
	}
	runcmd(rcmd->cmd, sh);
}

// deleted exit() not sure if it will have effect
static void	handle_pipe_cmd(t_pipecmd *pcmd, t_shell *sh)
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
		runcmd(pcmd->left, sh);
	}
	if (fork1() == 0)
	{
		close(0);
		dup(p[0]);
		close(p[0]);
		close(p[1]);
		runcmd(pcmd->right, sh);
	}
	close(p[0]);
	close(p[1]);
	waitpid(0, NULL, 0);
	waitpid(0, NULL, 0);
}

static void	handle_list_cmd(t_listcmd *lcmd, t_shell *sh)
{
	if (fork1() == 0)
		runcmd(lcmd->left, sh);
	wait(0);
	runcmd(lcmd->right, sh);
}

void	runcmd(t_cmd *cmd, t_shell *sh)
{
	if (cmd == 0)
		exit(0);
	if (cmd->type == EXEC)
		handle_exec_cmd((t_execcmd *)cmd, sh);
	else if (cmd->type == REDIR)
		handle_redir_cmd((t_redircmd *)cmd, sh);
	else if (cmd->type == LIST)
		handle_list_cmd((t_listcmd *)cmd, sh);
	else if (cmd->type == PIPE)
		handle_pipe_cmd((t_pipecmd *)cmd, sh);
	else if (cmd->type == BACK)
	{
		if (fork1() == 0)
			runcmd(((t_backcmd *)cmd)->cmd, sh);
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
