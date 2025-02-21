/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:15:32 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/19 18:09:15 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_tilde(char *path, t_shell *shell)
{
	char	*home;
	char	*result;

	if (!path || path[0] != '~')
		return (ft_strdup(path));
	home = ft_getenv("HOME", shell);
	if (!home)
		return (ft_strdup(path));
	if (path[1] == '\0')
		result = ft_strdup(home);
	else
		result = ft_strjoin(home, path + 1);
	free(home);
	return (result);
}

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
	char	*path;

	if (!argv || !shell)
		return (1);
	if (!argv[1])
	{
		home = ft_getenv("HOME", shell);
		if (!home)
		{
			shell->e_code = -1;
			ft_putendl_fd("cd: HOME not set\n", 2);
			return (1);
		}
		ret = chdir(home);
		return (free(home), ret == -1);
	}
	else
		path = expand_tilde(argv[1], shell);
	ret = chdir(path);
	if (ret == -1)
		return (ft_putendl_fd("cannot cd into:", 2), ft_putendl_fd(path, 2), 1);
	return (free(path), ret == -1);
}
