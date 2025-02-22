/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_null.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:55:17 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/22 17:31:56 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_exec_null(t_execcmd *ecmd)
{
	int	i;

	i = -1;
	while (ecmd->argv[++i])
		*ecmd->eargv[i] = 0;
}

void	handle_redir_null(t_redircmd *rcmd)
{
	nulterminate(rcmd->cmd);
	*rcmd->efile = 0;
}

void	handle_pipe_null(t_pipecmd	*pcmd)
{
	nulterminate(pcmd->left);
	nulterminate(pcmd->right);
}

void	handle_list_null(t_listcmd	*lcmd)
{
	nulterminate(lcmd->left);
	nulterminate(lcmd->right);
}

void	handle_back_null(t_backcmd	*bcmd)
{
	nulterminate(bcmd->cmd);
}
