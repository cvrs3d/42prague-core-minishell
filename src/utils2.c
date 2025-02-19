/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:25:37 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/19 17:25:59 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipe(t_pipecmd *pcmd)
{
	if (!pcmd)
		return ;
	free_tree(pcmd->left);
	free_tree(pcmd->right);
	free(pcmd);
}

void	free_list(t_listcmd *lcmd)
{
	if (!lcmd)
		return ;
	free_tree(lcmd->left);
	free_tree(lcmd->right);
	free(lcmd);
}

void	free_and(t_andcmd *acmd)
{
	if (!acmd)
		return ;
	free_tree(acmd->left);
	free_tree(acmd->right);
	free(acmd);
}

void	free_or(t_orcmd *acmd)
{
	if (!acmd)
		return ;
	free_tree(acmd->left);
	free_tree(acmd->right);
	free(acmd);
}

void	free_back(t_backcmd *bcmd)
{
	if (!bcmd)
		return ;
	free_tree(bcmd->cmd);
	free(bcmd);
}
