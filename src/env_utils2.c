/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:28:11 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/12 12:50:19 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
