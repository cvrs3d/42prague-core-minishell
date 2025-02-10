/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:28:11 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/10 15:44:41 by yustinov         ###   ########.fr       */
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

static char	**convert_env_to_array(t_shell *shell)
{
	t_env	*curr;
	char	**env_array;
	char	*tmp;
	int		i;
	int		size;

	size = get_env_size(shell->env_list);
	env_array = malloc(sizeof(char *) * (size + 1));
	if (!env_array)
		return (NULL);
	curr = shell->env_list;
	i = 0;
	while (curr)
	{
		tmp = ft_strjoin(curr->key, "=");
		env_array[i] = ft_strjoin(tmp, curr->value);
		free(tmp);
		if (!env_array[i])
		{
			ft_free_split(env_array);
			return (NULL);
		}
		curr = curr->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

void	update_env_array(t_shell *shell)
{
	if (shell->envp)
		ft_free_split(shell->envp);
	shell->envp = convert_env_to_array(shell);
}

char	*ft_getenv(const char *key, t_shell *shell)
{
	t_env	*current;

	if (!key || !shell || !shell->env_list)
		return (NULL);
	current = shell->env_list;
	while (current)
	{
		if (strcmp(key, current->key) == 0)
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (NULL);
}
