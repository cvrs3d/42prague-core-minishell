/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:49:59 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/08 14:51:34 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// t_cmd	*parse_arguments(t_cmd *ret, char **ps, char *es)
// {
// 	t_execcmd	*cmd;
// 	char		*q;
// 	char		*eq;
// 	int			argc;
// 	int			tok;

// 	cmd = (t_execcmd *)ret;
// 	argc = 0;
// 	while (!peek(ps, es, "|)&;"))
// 	{
// 		tok = gettoken(ps, es, &q, &eq);
// 		if (tok == 0)
// 			break ;
// 		if (tok != 'a')
// 			panic("syntax");
// 		process_token(cmd, &argc, q, eq);
// 		ret = parseredirs(ret, ps, es);
// 	}
// 	cmd->argv[argc] = 0;
// 	cmd->eargv[argc] = 0;
// 	return (ret);
// }
