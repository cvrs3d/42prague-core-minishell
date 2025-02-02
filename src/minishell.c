/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:21:42 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/02 12:37:46 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Ensuring that at least three file descriptors
	(stdin, stdout, stderr) are open prevents unexpected
	behavior in programs that assume these standard streams
	are available. This setup guarantees that your minishell
	can handle input and output operations reliably.
*/
static void	ft_check_system_fd(void)
{
	int fd;

	while ((fd = open("console", O_RDONLY)) >= 0)
	{
		if (fd >= 3)
		{
			close(fd);
			break;
		}
	}
	return ;
}

/*
	Ensures that Ctrl + C interrupt
	will be handled properly
	Ctrl + \ is ignored
*/
static void	ft_set_signal_handlers(void)
{
	signal(SIGINT, ft_sigquit_handler);
	signal(SIGQUIT, SIG_IGN);
	return ;
}

int	main(void)
{
	t_program *program;

    program = ft_calloc(1, sizeof(t_program));
    if (program == NULL)
		ft_panic(__FILE__, __LINE__, "calloc");
	ft_check_system_fd();
	ft_set_signal_handlers();
	ft_program_init(program);
	ft_repl(program);
	ft_cleanup(program);
	exit(0);
}
