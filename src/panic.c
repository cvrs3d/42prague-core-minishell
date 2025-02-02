/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:41:39 by yustinov          #+#    #+#             */
/*   Updated: 2025/01/30 16:55:59 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_putnbr(int n)
{
	char	c;

	if (n >= 10)
		ft_putnbr(n / 10);
	c = '0' + (n % 10);
	write(STDERR_FILENO, &c, 1);
}

/*
	panic
	Should be used when some serious errors occur
	like:
	malloc
	I/O
	BUSERROR
	etc.
*/
void	ft_panic(const char *file, int line, const char *message)
{
	write(STDERR_FILENO, "Panic: ", 7);
	write(STDERR_FILENO, message, strlen(message));
	write(STDERR_FILENO, " in file ", 9);
	write(STDERR_FILENO, file, strlen(file));
	write(STDERR_FILENO, " at line ", 9);
	ft_putnbr(line);
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}
