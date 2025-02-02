/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:58:56 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/02 15:12:14 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_cmd	*ft_parse(t_program *prog)
{
	t_cmd	*cmd;

	cmd = ft_parseline(&prog->ps, prog->es);
	ft_peek(&prog->ps, prog->es, "");
	if (prog->ps != prog->es)
		ft_exit_on_err()
}
