/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:39:29 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/18 16:44:56 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cleanup_heredoc(int fd)
{
	close(fd);
	unlink(HEREDOC_PATH);
}

static int	write_to_heredoc(int fd, char *limiter)
{
	char	*line;
	FILE	*original_stream;

	original_stream = rl_outstream;
	rl_outstream = stderr;
	while (1)
	{
		line = readline("heredocument> ");
		if (!line)
		{
			ft_putendl_fd("warning: here-document delimited by end-of-file", 2);
			break ;
		}
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	rl_outstream = original_stream;
	return (1);
}
// static int	write_to_heredoc(int fd, char *limiter)
// {
// 	char	*line;

// 	rl_outstream = stderr;
// 	while (1)
// 	{
// 		line = readline("heredocument> ");
// 		if (!line)
// 		{
// 			rl_outstream = stdout;
// 			ft_putendl_fd("warning: here-document delimited by end-of-file", 2);
// 			return (0);
// 		}
// 		if (ft_strcmp(line, limiter) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		ft_putendl_fd(line, fd);
// 		free(line);
// 	}
// 	rl_outstream = stdout;
// 	return (1);
// }

void	handle_heredoc_cmd(char *limiter)
{
	int		fd;
	FILE	*original_stream;

	original_stream = rl_outstream;
	fd = open(HEREDOC_PATH, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		panic("open", EXIT_MINISHEL_ERR, NULL);
	if (!write_to_heredoc(fd, limiter))
	{
		cleanup_heredoc(fd);
		rl_outstream = original_stream;
		return ;
	}
	close(fd);
	fd = open(HEREDOC_PATH, O_RDONLY);
	if (fd < 0)
	{
		cleanup_heredoc(fd);
		panic("open", EXIT_MINISHEL_ERR, NULL);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	rl_outstream = original_stream;
}
// void	handle_heredoc_cmd(char *limiter)
// {
// 	int	fd;

// 	fd = open(HEREDOC_PATH, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	if (fd < 0)
// 		panic("open", EXIT_MINISHEL_ERR);
// 	if (!write_to_heredoc(fd, limiter))
// 	{
// 		cleanup_heredoc(fd);
// 		return ;
// 	}
// 	close(fd);
// 	fd = open(HEREDOC_PATH, O_RDONLY);
// 	if (fd < 0)
// 	{
// 		cleanup_heredoc(fd);
// 		panic("open", EXIT_MINISHEL_ERR);
// 	}
// }
