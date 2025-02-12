/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_finder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:23:36 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/12 12:40:58 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_full_path(char *path, char *cmd)
{
	char	*full_path;
	size_t	len;

	len = strlen(path) + strlen(cmd) + 2;
	full_path = malloc(len);
	if (full_path == NULL)
		panic("malloc");
	snprintf(full_path, len, "%s/%s", path, cmd);
	return (full_path);
}

static int	check_executable(char *path, t_execcmd *ecmd)
{
	char	*full_path;

	full_path = create_full_path(path, ecmd->argv[0]);
	if (access(full_path, X_OK) == 0)
	{
		ecmd->argv[0] = full_path;
		return (0);
	}
	free(full_path);
	return (-1);
}

int	ft_try_find_cmd(t_execcmd *ecmd, t_shell *shell)
{
	char	*path_env;
	char	*path;

	if (access(ecmd->argv[0], X_OK) == 0)
		return (0);
	path_env = ft_getenv("PATH", shell);
	if (path_env == NULL)
		return (-1);
	path = strtok(path_env, ":");
	while (path != NULL)
	{
		if (check_executable(path, ecmd) == 0)
		{
			free(path_env);
			return (0);
		}
		path = strtok(NULL, ":");
	}
	free(path_env);
	return (-1);
}
