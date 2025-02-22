/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:44:26 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/22 13:59:55 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_var_name(char *str, int *i, int *j)
{
	*j = *i + 1;
	while (str[*j] && (ft_isalnum(str[*j]) || str[*j] == '_'))
		(*j)++;
	return (ft_substr(str, *i + 1, *j - *i - 1));
}

static char	*join_parts(char *before, char *v_val, char *after)
{
	char	*temp;
	char	*result;

	result = ft_strjoin(before, v_val);
	free(before);
	temp = result;
	result = ft_strjoin(temp, after);
	free(temp);
	free(after);
	return (result);
}

char	*expand_variable(char *str, int *i, t_shell *shell)
{
	int		j;
	char	*v_name;
	char	*v_val;
	char	*result;

	v_name = get_var_name(str, i, &j);
	v_val = ft_getenv(v_name, shell);
	if (!v_val)
		v_val = ft_strdup("");
	result = join_parts(ft_substr(str, 0, *i), v_val,
			ft_strdup(str + j));
	free(v_name);
	*i += ft_strlen(v_val) - 1;
	free(v_val);
	free(str);
	return (result);
}
