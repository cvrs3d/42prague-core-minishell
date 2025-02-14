/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:09:30 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/14 17:54:18 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_shell_fd(void)
{
	int	fd;

	fd = open("console", O_RDONLY);
	while (fd >= 0)
	{
		if (fd >= 3)
		{
			close(fd);
			break ;
		}
	}
}

static void	setup_signals(void)
{
	signal(SIGINT, ft_sigquit_handler);
	signal(SIGQUIT, SIG_IGN);
}

static void	execute_command(char *buffer, t_shell *sh)
{
	pid_t	pid;
	int		status;

	pid = fork1();
	if (pid == 0)
		runcmd(parsecmd(buffer), sh);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		sh->e_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		sh->e_code = 128 + WTERMSIG(status);
}

/**
 * @brief Entry point of the minishell program.
 *
 * This function initializes the minishell program, processes command-line
 * arguments, and sets up the environment for the shell.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of strings representing the command-line arguments.
 * @param envp An array of strings representing the environment variables.
 *
 * @return Returns an integer status code. Typically, 0 indicates success,
 *         while non-zero values indicate errors.
 */
int	main(int argc, char **argv, char **envp)
{
	static char	buffer[100];
	t_shell		shell;
	int			ret;

	(void)argc;
	(void)argv;
	init_env(&shell, envp);
	setup_signals();
	init_shell_fd();
	while (getcmd(buffer, sizeof(buffer)) >= 0)
	{
		if (evaluate_input(buffer, &shell) == -1)
			break ;
		ret = check_builtins_non_fork(buffer, &shell);
		if (ret == 127)
			exit_shell(&shell, shell.e_code);
		if (ret == NO_BUILTIN_FOUND)
			execute_command(buffer, &shell);
	}
	exit_shell(&shell, EXIT_SUCCESS);
}
