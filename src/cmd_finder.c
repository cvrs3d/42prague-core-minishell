/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_finder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:23:36 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/14 18:31:12 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_full_path(char *path, char *cmd)
{
	char	*full_path;
	size_t	len;

	len = ft_strlen(path) + ft_strlen(cmd) + 2;
	full_path = malloc(len);
	if (full_path == NULL)
		panic("malloc", EXIT_MINISHEL_ERR);
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

/*
	TODO:
	Change strtok to ft_split
*/
int	ft_try_find_cmd(t_execcmd *ecmd, t_shell *shell)
{
	char	*path_env;
	char	**path_args;
	int		i;

	if (access(ecmd->argv[0], X_OK) == 0)
		return (0);
	path_env = ft_getenv("PATH", shell);
	if (path_env == NULL)
		return (-1);
	path_args = ft_split(path_env, ':');
	i = 0;
	while (path_args && path_args[i])
	{
		if (check_executable(path_args[i], ecmd) == 0)
		{
			free(path_env);
			ft_free_split(path_args);
			return (0);
		}
		i++;
	}
	if (path_args)
		ft_free_split(path_args);
	free(path_env);
	return (-1);
}
