/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:10:29 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/14 16:47:10 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handles the 'cd' command in the minishell.
 *
 * This function processes the 'cd' (change directory) command by updating
 * the current working directory based on the provided buffer.
 *
 * @param buffer A string containing the target directory path.
 * @return An integer indicating the success or failure of the operation.
 *         Typically, 0 indicates success, while a non-zero value indicates
 *         an error.
 */
int	handle_cd_command(char **argv, t_shell *shell)
{
	char	*home;
	int		ret;

	if (!argv || !shell)
		return (1);
	if (!argv[1])
	{
		home = ft_getenv("HOME", shell);
		if (!home)
		{
			shell->e_code = -1;
			printf("cd: HOME not set\n");
			return (1);
		}
		ret = chdir(home);
		free(home);
	}
	else
		ret = chdir(argv[1]);
	if (ret == -1)
		return (printf("cannot cd into: %s\n", argv[1]), 1);
	return (0);
}

/**
 * @brief Handles the 'env' command in the shell.
 *
 * This function processes the 'env' command, which typically prints out
 * the current environment variables. It takes a pointer to the shell
 * structure as an argument to access the necessary context and data.
 *
 * @param shell A pointer to
 * the t_shell structure containing the shell's state and data.
 * @return An integer
 * representing the success or failure of the command execution.
 */
int	handle_env_command(t_shell *shell)
{
	t_env	*curr;

	curr = shell->env_list;
	while (curr)
	{
		printf("%s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
	return (0);
}

/**
 * @brief Handles the 'unset' command in the shell.
 *
 * This function processes the 'unset' command, which is used to remove
 * environment variables from the shell's environment.
 *
 * @param buffer A string containing the command and its arguments.
 * @param shell A pointer to the shell structure containing the shell's state.
 *
 * @return An integer status code
 * indicating the success or failure of the operation.
 */
int	handle_unset_command(char **argv, t_shell *shell)
{
	int		i;

	if (!argv)
		return (1);
	i = 1;
	while (argv[i])
	{
		unset_var(shell, argv[i]);
		i++;
	}
	return (0);
}

/**
 * @brief Handles the export command in the shell.
 *
 * This function processes the export command, which is used to set environment
 * variables in the shell. It parses the input buffer and updates the shell's
 * environment accordingly.
 *
 * @param buffer The input buffer
 * containing the export command and its arguments.
 * @param shell A pointer to the
 * shell structure containing the current state of the shell.
 * @return An integer status code
 * indicating the success or failure of the command.
 */
int	handle_export_command(char **argv, t_shell *shell)
{
	char	**key_value;
	int		i;

	if (!argv)
		return (1);
	i = 1;
	while (argv[i])
	{
		key_value = ft_split(argv[i], '=');
		if (key_value && key_value[0] && key_value[1])
		{
			export_var(shell, key_value[0], key_value[1]);
			ft_free_split(key_value);
		}
		else if (key_value)
			ft_free_split(key_value);
		i++;
	}
	return (0);
}

/**
 * check_builtins - Checks if the given command is a built-in shell command.
 * @buffer: The command string to check.
 * @shell: A pointer to the shell structure containing shell state and context.
 *
 * Return: An integer indicating the result of the check. Typically, this
 *         would be a boolean-like value where 0 means the command is not
 *         a built-in and 1 means it is a built-in.
 * ON SUCCESS ALL HANDLERS RETURN 1 EXEPT EXIT
 */
int	check_builtins(char **argv, t_shell *shell)
{
	if (strncmp(argv[0], "cd", 2) == 0)
		return (handle_cd_command(argv, shell));
	else if (strncmp(argv[0], "env", 3) == 0)
		return (handle_env_command(shell));
	else if (strncmp(argv[0], "unset", 5) == 0)
		return (handle_unset_command(argv, shell));
	else if (strncmp(argv[0], "export", 6) == 0)
		return (handle_export_command(argv, shell));
	else if (strncmp(argv[0], "pwd", 3) == 0)
		return (handle_pwd_command(shell));
	else if (strncmp(argv[0], "echo", 4) == 0)
		return (handle_echo_command(argv, shell));
	else if (strncmp(argv[0], "exit", 4) == 0)
		return (handle_exit_command(argv, shell));
	return (NO_BUILTIN_FOUND);
}
