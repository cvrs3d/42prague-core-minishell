/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:43:08 by yustinov          #+#    #+#             */
/*   Updated: 2025/01/31 16:08:26 by yustinov         ###   ########.fr       */
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
static int	ft_getcmd(t_program *prog)
{
	prog->buffer = readline(prog->prompt);
	if (prog->buffer == NULL)
		return (-1);
	add_history(prog->buffer);
	return (0);
}

void	ft_repl(t_program *prog)
{
	int		i;
	char	*es;
	char	*ps;


	while (ft_getcmd(prog) >= 0)
	{
		i = 0;
		es = prog->buffer + ft_strlen(prog->buffer);
		ps = prog->buffer;
		while (ft_gettoken(&ps, es, 0, 0))
		{
			printf("%c", ft_gettoken(&ps, es, 0, 0))

		}
	}

}
