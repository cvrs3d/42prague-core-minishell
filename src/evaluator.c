/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:13:41 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/12 14:52:33 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_quotes(char *str)
{
	int		i;
	char	quote;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				i++;
			if (!str[i])
				return (0);
		}
		i++;
	}
	return (1);
}

static char	*expand_exit_status(char *str, int *i, t_shell *shell)
{
	char	*before;
	char	*after;
	char	*exit_status;
	char	*result;

	before = ft_substr(str, 0, *i);
	after = ft_strdup(str + *i + 2);
	exit_status = ft_itoa(shell->e_code);
	result = ft_strjoin(before, exit_status);
	free(before);
	before = result;
	result = ft_strjoin(before, after);
	free(before);
	free(after);
	*i += ft_strlen(exit_status) - 1;
	free(str);
	free(exit_status);
	return (result);
}

int	evaluate_input(char *buffer, t_shell *shell)
{
	int		i;
	int		in_quotes;
	char	*result;

	if (!check_quotes(buffer))
		return (1, printf("unclosed quotes: %s\n", buffer));
	result = ft_strdup(buffer);
	i = 0;
	in_quotes = 0;
	while (result[i])
	{
		if (result[i] == '\'')
			in_quotes = !in_quotes;
		if (!in_quotes && result[i] == '$')
		{
			if (result[i + 1] == '?')
				result = expand_exit_status(result, &i, shell);
			else if (ft_isalpha(result[i + 1]) || result[i + 1] == '_')
				result = expand_variable(result, &i, shell);
		}
		i++;
	}
	ft_strlcpy(buffer, result, ft_strlen(result) + 1);
	free(result);
	return (0);
}
