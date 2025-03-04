/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:07:56 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/22 20:34:55 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sigquit_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_sig_child_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

int	split_free_wrapper(char **split, int i, t_shell *shell)
{
	ft_free_split(split);
	if (shell != NULL)
		shell->e_code = i;
	return (i);
}

void	exit_shell(t_shell *shell, int exit_code)
{
	if (shell)
	{
		if (shell->head)
		{
			free_tree(shell->head);
			shell->head = NULL;
		}
		cleanup_env(shell);
	}
	rl_clear_history();
	exit(exit_code);
}

// {
// 	cmd->argv[argc] = 0;
// 	cmd->eargv[argc] = 0;
// }
void	ft_norm1(char *p1, char *p2)
{
	p1 = 0;
	p2 = 0;
}
