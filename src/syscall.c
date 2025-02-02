/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:30:35 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/02 14:56:53 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Safer version of
	getenv syscall
	Can be upgraded
*/
char	*sys_getenv(const char *name)
{
	char *value;

	value = getenv(name);
	if (value == NULL)
		return ("unknown");
	return value;
}

/*
	Gets cwd
	Panics if there is no cwd
	???
*/
char	*sys_getcwd(char *buf, size_t size)
{
	if (getcwd(buf, size) == NULL)
	{
		ft_panic(__FILE__, __LINE__, "getcwd failed");
	}
	return buf;
}

/*
	fork sys call
	wrapper
	panics if fork() -> -1
*/
pid_t	sys_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		panic("fork");
	return pid;
}
