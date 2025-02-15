/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:15:17 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/15 14:16:12 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_or_null(t_orcmd *lcmd)
{
	nulterminate(lcmd->left);
	nulterminate(lcmd->right);
}

void	handle_and_null(t_andcmd *lcmd)
{
	nulterminate(lcmd->left);
	nulterminate(lcmd->right);
}
