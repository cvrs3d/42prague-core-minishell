/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:32:05 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/14 16:55:36 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_pwd_command(t_shell *shell)
{
	char	*cwd;
	char	buf[PATH_MAX];

	(void)shell;
	cwd = getcwd(buf, PATH_MAX);
	if (NULL == cwd)
		return (1);
	printf("%s\n", cwd);
	return (0);
}

/*
	ADD SUPPORT FOR EXITTING WITH PROVIDED ERROR CODE
	IF NOTHING PROVIDED EXIT WITH 0
	IF CANNOT ATOI THAN EXIT WITH -1
	REWRITE ATOI SO IT RETURNS -1 ON ERROR
*/
int	handle_exit_command(char **argv, t_shell *shell)
{
	int		e_code;

	if (!argv)
	{
		shell->e_code = EXIT_FAILURE;
		return (1);
	}
	if (argv[1])
	{
		e_code = atoi(argv[1]);
		if (e_code == 0)
		{
			printf("integer required %s\n", argv[1]);
			shell->e_code = EXIT_CMD_NOT_FOUND;
		}
		else
			shell->e_code = e_code;
	}
	printf("exit\n");
	return (127);
}

int	handle_echo_command(char **argv, t_shell *shell)
{
	int		new_line_flag;
	int		i;

	shell->e_code = 0;
	new_line_flag = 1;
	if (NULL == argv)
		return (1);
	if (argv[1])
		new_line_flag = strcmp(argv[1], "-n");
	i = 1;
	if (new_line_flag == 0)
		i = 2;
	while (argv[i])
	{
		printf("%s ", argv[i]);
		i++;
	}
	if (new_line_flag != 0)
		printf("\n");
	return (0);
}

int	check_builtins_non_fork(char *buffer, t_shell *shell)
{
	char	**argv;

	if (!buffer || !*buffer)
		return (-1);
	argv = ft_split(buffer, ' ');
	if (!argv)
		return (-1);
	if (!argv[0])
		return (ft_free_split(argv), -1);
	if (strncmp(argv[0], "cd", 2) == 0)
		return (split_free_wrapper(argv,
				handle_cd_command(argv, shell), shell));
	else if (strncmp(argv[0], "unset", 5) == 0)
		return (split_free_wrapper(argv,
				handle_unset_command(argv, shell), shell));
	else if (strncmp(argv[0], "export", 6) == 0)
		return (split_free_wrapper(argv,
				handle_export_command(argv, shell), shell));
	else if (strncmp(argv[0], "exit", 4) == 0)
		return (split_free_wrapper(argv,
				handle_exit_command(argv, shell), shell));
	return (ft_free_split(argv), NO_BUILTIN_FOUND);
}
