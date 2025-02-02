/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 12:18:47 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/02 12:22:29 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// typedef struct s_program
// {
// 	t_backcmd	*backcmd;
// 	t_condcmd	*condcmd;
// 	t_pipecmd	*pipecmd;
// 	t_listcmd	*listcmd;
// 	t_redircmd	*redircmd;
// 	t_execcmd	*execcmd;
// 	char		*buffer;
// 	char		*prompt;
// }	t_program;

void ft_cleanup(t_program *program)
{
	if (program)
	{
		if (program->buffer)
			free(program->buffer);
		if (program->prompt)
			free(program->prompt);
		free(program);
	}
	rl_clear_history();
}
