/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:52:38 by yustinov          #+#    #+#             */
/*   Updated: 2025/01/30 17:42:30 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	ft_init_prompt
	Allocates memory for shell prompt
	Cause panic if there is no memory
	Constructs the string
*/
void	ft_init_prompt(t_program *prog)
{
	char	*user;
	char	cwd[1024];

	user = sys_getenv("USER");
	sys_getcwd(cwd, 1024);
	prog->prompt = (char *)ft_calloc(1, ft_strlen(user)
		+ ft_strlen(cwd) + 4);
	if (!prog->prompt)
		ft_panic(__FILE__, __LINE__, "calloc");
	ft_strcpy(prog->prompt, "$");
	ft_strcat(prog->prompt, user);
	ft_strcat(prog->prompt, ":");
	ft_strcat(prog->prompt, cwd);
	ft_strcat(prog->prompt, "$ ");
}

/*
	ft_program_init
	should safelly allocate memory for
	the config structure or panic if there
	is some malloc problems
	then it passes the flow to ft_init_prompt
*/
void	ft_program_init(t_program *prog)
{
	prog = (t_program *)ft_calloc(1, sizeof(t_program) * 1);
	if (prog == NULL)
		ft_panic(__FILE__, __LINE__, "calloc");
	ft_init_promt(prog);
}
