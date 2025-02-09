/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:41:45 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/09 15:31:52 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_node(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

void	init_env(t_shell *shell, char **envp)
{
	t_env	*new;
	char	**split;
	int		i;

	shell->env_list = NULL;
	i = 0;
	while (envp[i])
	{
		split = ft_split(envp[i], '=');
		if (split[0] && split[1])
		{
			new = create_env_node(split[0], split[1]);
			new->next = shell->env_list;
			shell->env_list = new;
		}
		ft_free_split(split);
		i++;
	}
}

void	export_var(t_shell *shell, char *key, char *value)
{
	t_env	*env;

	env = shell->env_list;
	while (env)
	{
		if (strcmp(env->key, key) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
	env = create_env_node(key, value);
	env->next = shell->env_list;
	shell->env_list = env;
}

void	unset_var(t_shell *shell, char *key)
{
	t_env	*env;
	t_env	*prev;

	env = shell->env_list;
	prev = NULL;
	while (env)
	{
		if (strcmp(env->key, key) == 0)
		{
			if (prev)
				prev->next = env->next;
			else
				shell->env_list = env->next;
			free(env->key);
			free(env->value);
			free(env);
			return ;
		}
		prev = env;
		env = env->next;
	}
}

void	cleanup_env(t_shell *shell)
{
	t_env	*env;
	t_env	*next;

	env = shell->env_list;
	while (env)
	{
		next = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = next;
	}
}
