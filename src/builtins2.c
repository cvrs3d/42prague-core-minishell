/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:32:05 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/11 19:32:13 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_pwd_command(char *buffer, t_shell *shell)
{
	char	*cwd;
	char	buf[PATH_MAX];

	(void)buffer;
	(void)shell;
	cwd = getcwd(buf, PATH_MAX);
	if (NULL == cwd)
		return (-1);
	printf("%s\n", cwd);
	return (1);
}

/*
	ADD SUPPORT FOR EXITTING WITH PROVIDED ERROR CODE
	IF NOTHING PROVIDED EXIT WITH 0
	IF CANNOT ATOI THAN EXIT WITH -1
	REWRITE ATOI SO IT RETURNS -1 ON ERROR
*/
int	handle_exit_command(char *buffer, t_shell *shell)
{
	char	**args;
	int		e_code;

	(void)buffer;
	args = ft_split(buffer, ' ');
	if (!args)
	{
		shell->e_code = EXIT_FAILURE;
		return (-1);
	}
	if (args[1])
	{
		e_code = atoi(args[1]);
		if (e_code == 0)
			printf("integer required %s\n", args[1]);
		shell->e_code = e_code;
	}
	ft_free_split(args);
	printf("exit\n");
	return(-1);
}

int	handle_echo_command(char *buffer, t_shell *shell)
{
	char	**args;
	int		new_line_flag;
	int		i;

	new_line_flag = 1;
	args = ft_split(buffer, ' ');
	if (NULL == args)
		return (-1);
	if (args[1])
		new_line_flag = strcmp(args[1], "-n");
	i = 1;
	if (new_line_flag == 0)
		i = 2;
	while (args[i])
	{
		printf("%s ", args[i]);
		i++;
	}
	if (new_line_flag != 0)
		printf("\n");
	ft_free_split(args);
	return (1);
}
