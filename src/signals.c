/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:48:02 by yustinov          #+#    #+#             */
/*   Updated: 2025/01/30 15:52:26 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Handles Ctrl + C
	casts the signal to avoid linter
	writes a newline after ^C
	sets redline reader on a new line
	clears redline reader's input buffer
	redisplays the prompt
	minishell$: ^C
	minishell$:
*/
void	ft_sigquit_handler(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}
