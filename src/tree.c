/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:37:20 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/08 18:37:41 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_spaces(int depth)
{
	while (depth-- > 0)
		printf("  ");
}

static void print_exec(t_execcmd *cmd, int depth)
{
	int i;

	print_spaces(depth);
	printf("EXEC: ");
	i = 0;
	while (cmd->argv[i])
	{
		printf("%s ", cmd->argv[i]);
		i++;
	}
	printf("\n");
}

static void print_redir(t_redircmd *cmd, int depth)
{
	print_spaces(depth);
	printf("REDIR: %s (fd: %d, mode: %d)\n", cmd->file, cmd->fd, cmd->mode);
	print_tree(cmd->cmd, depth + 1);
}

static void print_pipe(t_pipecmd *cmd, int depth)
{
	print_spaces(depth);
	printf("PIPE:\n");
	print_tree(cmd->left, depth + 1);
	print_tree(cmd->right, depth + 1);
}

static void print_list(t_listcmd *cmd, int depth)
{
	print_spaces(depth);
	printf("LIST:\n");
	print_tree(cmd->left, depth + 1);
	print_tree(cmd->right, depth + 1);
}

static void print_back(t_backcmd *cmd, int depth)
{
	print_spaces(depth);
	printf("BACKGROUND:\n");
	print_tree(cmd->cmd, depth + 1);
}

void print_tree(t_cmd *cmd, int depth)
{
	if (!cmd)
	{
		print_spaces(depth);
		printf("(null)\n");
		return;
	}
	if (cmd->type == EXEC)
		print_exec((t_execcmd *)cmd, depth);
	else if (cmd->type == REDIR)
		print_redir((t_redircmd *)cmd, depth);
	else if (cmd->type == PIPE)
		print_pipe((t_pipecmd *)cmd, depth);
	else if (cmd->type == LIST)
		print_list((t_listcmd *)cmd, depth);
	else if (cmd->type == BACK)
		print_back((t_backcmd *)cmd, depth);
	else
	{
		print_spaces(depth);
		printf("Unknown command type: %d\n", cmd->type);
	}
}
