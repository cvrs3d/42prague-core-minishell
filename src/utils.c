/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:13:07 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/09 15:18:41 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n--)
		*p++ = (unsigned char)c;
	return (s);
}

void	panic(char *s)
{
	fprintf(stderr, "%s\n", s);
	exit(1);
}

int	fork1(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		panic("fork");
	return (pid);
}

int	getcmd(char	*buf, int nbuf)
{
	char	*input;

	input = readline("minishell$ ");
	if (input == NULL)
	{
		if (input)
			free(input);
		rl_clear_history();
		fprintf(stderr, "exit\n");
		return (-1);
	}
	strncpy(buf, input, nbuf - 1);
	buf[nbuf - 1] = '\0';
	add_history(buf);
	free(input);
	return (0);
}

void	ft_putendl_fd(const char *s, int fd)
{
	if (!s)
	{
		write (fd, "(null)\n", 7);
		return ;
	}
	while (*s != '\0')
	{
		write (fd, s, 1);
		s++;
	}
	write (fd, "\n", 1);
}
