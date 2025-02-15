/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:13:07 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/15 16:46:48 by yustinov         ###   ########.fr       */
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

void	panic(char *s, int exit_code)
{
	ft_putendl_fd(s, 2);
	exit(exit_code);
}

int	fork1(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		panic("fork", EXIT_FAILURE);
	return (pid);
}

/**
 * @brief Reads a command from the standard input into the provided buffer.
 *
 * This function reads up to `nbuf` characters from the standard input and stores
 * them in the buffer `buf`. It ensures that the buffer is null-terminated.
 *
 * @param buf A pointer to the buffer where the command will be stored.
 * @param nbuf The maximum number of characters to read into the buffer.
 * @return The number of characters read, or -1 if an error occurs.
 */
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
