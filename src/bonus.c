/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 13:50:02 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/15 14:55:35 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_token_bonus(char **ps, char *s)
{
	int	ret;

	ret = *s;
	s++;
	if (*s == '&' && ret == '&')
	{
		ret = '?';
		s++;
	}
	else if (*s == '|' && ret == '|')
	{
		ret = '!';
		s++;
	}
	*ps = s;
	return (ret);
}

t_cmd	*andcmd(t_cmd *left, t_cmd *right)
{
	t_andcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = AND;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

t_cmd	*orcmd(t_cmd *left, t_cmd *right)
{
	t_orcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = OR;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

void	handle_or_cmd(t_orcmd *lcmd, t_shell *sh)
{
	pid_t	pid;
	int		code_exit;
	int		run_next;

	run_next = 0;
	pid = fork1();
	if (pid == 0)
		runcmd(lcmd->left, sh);
	waitpid(pid, &code_exit, 0);
	if (WIFEXITED(code_exit))
		run_next = WEXITSTATUS(code_exit);
	else if (WIFSIGNALED(code_exit))
		run_next = 128 + WTERMSIG(code_exit);
	if (run_next != 0)
		runcmd(lcmd->right, sh);
	exit(run_next);
}

void	handle_and_cmd(t_andcmd *lcmd, t_shell *sh)
{
	pid_t	pid;
	int		code_exit;
	int		run_next;

	run_next = 0;
	pid = fork1();
	if (pid == 0)
		runcmd(lcmd->left, sh);
	waitpid(pid, &code_exit, 0);
	if (WIFEXITED(code_exit))
		run_next = WEXITSTATUS(code_exit);
	else if (WIFSIGNALED(code_exit))
		run_next = 128 + WTERMSIG(code_exit);
	if (run_next == 0)
		runcmd(lcmd->right, sh);
	exit(run_next);
}
