/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:10:06 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/08 18:37:54 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <stddef.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define EXEC 1
# define REDIR 2
# define PIPE 3
# define LIST 4
# define BACK 5
# define MAXARGS 10
# define WHITESPACE " \t\r\n\v"
# define SYMBOLS "<|>&;()\"'"
# define STDOUT 100
# define STDIN 101
# define APPEND 102
# define HEREDOC 103

typedef struct s_cmd
{
	int	type;
}	t_cmd;

typedef struct s_execcmd
{
	int		type;
	char	*argv[MAXARGS];
	char	*eargv[MAXARGS];
}	t_execcmd;

typedef struct s_redircmd
{
	int		type;
	t_cmd	*cmd;
	char	*file;
	char	*efile;
	int		mode;
	int		fd;
}	t_redircmd;

typedef struct s_listcmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_listcmd;

typedef struct s_backcmd
{
	int		type;
	t_cmd	*cmd;
}	t_backcmd;

typedef struct s_pipecmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipecmd;

// Function prototypes
void	ft_sigquit_handler(int sig);
int		fork1(void);
void	panic(char *s);
t_cmd	*parsecmd(char *s);
void	runcmd(t_cmd *cmd);
int		gettoken(char **ps, char *es, char **q, char **eq);
int		getcmd(char *buf, int nbuf);
int		peek(char **ps, char *es, char *toks);
void	*ft_memset(void *s, int c, size_t n);
t_cmd	*execcmd(void);
t_cmd	*redircmd(t_cmd *subcmd, char *file, char *efile, int mode);
t_cmd	*pipecmd(t_cmd *left, t_cmd *right);
t_cmd	*listcmd(t_cmd *left, t_cmd *right);
t_cmd	*backcmd(t_cmd *subcmd);
t_cmd	*parseline(char **ps, char *es);
t_cmd	*parsepipe(char **ps, char *es);
t_cmd	*parseredirs(t_cmd *cmd, char **ps, char *es);
t_cmd	*parseblock(char **ps, char *es);
t_cmd	*parseexec(char **ps, char *es);
void	ft_sigquit_handler(int sig);
// t_cmd	*nulterminate(t_cmd *cmd);
int		ft_try_find_cmd(t_execcmd *ecmd);
void	runcmd(t_cmd *cmd);
t_cmd	*nulterminate(t_cmd *cmd);
void	handle_exec_null(t_execcmd *ecmd);
void	handle_redir_null(t_redircmd *rcmd);
void	handle_pipe_null(t_pipecmd	*pcmd);
void	handle_list_null(t_listcmd	*lcmd);
void	handle_back_null(t_backcmd	*bcmd);
void	print_tree(t_cmd *cmd, int depth);

#endif
