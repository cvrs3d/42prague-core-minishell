/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:43:08 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/02 12:11:52 by yustinov         ###   ########.fr       */
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

void ft_repl(t_program *prog) {
    int     i;
    char    *es;
    char    *ps;

    while (ft_getcmd(prog) >= 0) {
        i = 0;
        es = prog->buffer + ft_strlen(prog->buffer);
        ps = prog->buffer;
        printf("Tokens: "); // Add this line for clarity
        while (ps < es) {
            int token = ft_gettoken(&ps, es, 0, 0);
            printf("%c ", token); // Print each token
        }
        printf("\n"); // Add a newline for better readability
    }
}
