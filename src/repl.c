/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:43:08 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/02 15:02:38 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	ft_getcmd
	Gets users prompt by using readline library
	exits if EOF is passed by Ctrl-D
	Invokes add_history to maintain prompt history
	On CTRL-D or Error returns -1 -> REPL exits -> main() -> cleanup
*/
static int ft_getcmd(t_program *prog)
{
	prog->buffer = readline(prog->prompt);
	if (prog->buffer == NULL)
		return (-1);
	add_history(prog->buffer);
	return (0);
}

/*
	Read
	Execute
	Parse
	Loop
*/
void ft_repl(t_program *prog)
{
	int 	i;
	t_cmd	*cmd;

	while (ft_getcmd(prog) >= 0)
	{
		i = 0;
		prog->es = prog->buffer + ft_strlen(prog->buffer);
		prog->ps = prog->buffer;
		cmd = ft_parse(prog);
		if (sys_fork() == 0)
			ft_runcmd(cmd);
		wait(0);
		ft_freecmd(cmd);
	}
}
