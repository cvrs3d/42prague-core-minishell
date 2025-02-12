/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:48:09 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/12 13:00:54 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_env_size(t_env *env_list)
{
	t_env	*curr;
	int		size;

	size = 0;
	curr = env_list;
	while (curr)
	{
		size++;
		curr = curr->next;
	}
	return (size);
}

static char	*create_env_string(t_env *curr)
{
	char	*tmp;
	char	*env_str;

	tmp = ft_strjoin(curr->key, '=');
	if (!tmp)
		return (NULL);
	env_str = ft_strjoin(tmp, curr->value);
	free(tmp);
	return (env_str);
}

static int	fill_env_array(char **env_array, t_env *curr)
{
	int		i;
	char	*env_str;

	i = 0;
	while (curr)
	{
		env_str = create_env_string(curr);
		if (!env_str)
		{
			ft_free_split(env_array);
			return (-1);
		}
		env_array[i] = env_str;
		curr = curr->next;
		i++;
	}
	env_array[i] = NULL;
	return (0);
}

char	**convert_env_to_array(t_shell *shell)
{
	char	**env_array;
	int		size;

	size = get_env_size(shell->env_list);
	env_array = malloc(sizeof(char *) * (size + 1));
	if (!env_array)
		return (NULL);
	if (fill_env_array(env_array, shell->env_list) == -1)
		return (NULL);
	return (env_array);
}
