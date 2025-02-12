/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:40:04 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/12 12:40:06 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_redir_mode(t_redircmd *cmd, int mode)
{
	if (mode == STDIN)
	{
		cmd->mode = O_WRONLY;
		cmd->fd = 0;
	}
	else if (mode == HEREDOC)
	{
		cmd->mode = HEREDOC;
		cmd->fd = 0;
	}
	else if (mode == STDOUT)
	{
		cmd->mode = O_WRONLY | O_CREAT | O_TRUNC;
		cmd->fd = 1;
	}
	else if (mode == APPEND)
	{
		cmd->mode = O_WRONLY | O_CREAT | O_APPEND;
		cmd->fd = 1;
	}
}

t_cmd	*redircmd(t_cmd *subcmd, char *file, char *efile, int mode)
{
	t_redircmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = REDIR;
	cmd->cmd = subcmd;
	cmd->file = file;
	cmd->efile = efile;
	set_redir_mode(cmd, mode);
	return ((t_cmd *)cmd);
}
