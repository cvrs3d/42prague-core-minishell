/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:09:30 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/09 15:38:13 by yustinov         ###   ########.fr       */
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

static void	handle_cd_command(char *buffer)
{
	if (chdir(buffer + 3) < 0)
		fprintf(stderr, "cannot cd %s\n", buffer + 3);
}

static void	setup_signals(void)
{
	signal(SIGINT, ft_sigquit_handler);
	signal(SIGQUIT, SIG_IGN);
}

static void	execute_command(char *buffer, t_shell *sh)
{
	if (fork1() == 0)
		runcmd(parsecmd(buffer), sh);
	wait(0);
}

int	main(int argc, char **argv, char **envp)
{
	static char	buffer[100];
	t_shell		shell;

	(void)argc;
	(void)argv;
	init_env(&shell, envp);
	setup_signals();
	init_shell_fd();
	while (getcmd(buffer, sizeof(buffer)) >= 0)
	{
		if (buffer[0] == 'c' && buffer[1] == 'd' && buffer[2] == ' ')
		{
			handle_cd_command(buffer);
			continue ;
		}
		execute_command(buffer, &shell);
	}
	cleanup_env(&shell);
	exit(0);
}
