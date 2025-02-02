/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:22:14 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/02 13:50:29 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <stddef.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define MAXARGS	10
# define RESET "\033[0m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define WHITESPACES " \t\r\n\v"
# define SYMBOLS "<|>&;()\"'"

// ENUM for types handling
typedef enum e_type
{
	EXEC,
	REDIR,
	PIPE,
	LIST,
	BACK,
	COND
}	t_type;

// Generic
typedef struct s_cmd
{
	t_type	type;
}	t_cmd;

// Other stuff is considered a command
// And is executed
// Should evaluate in the following order
// Is it a builtin? -> Call a function()
// Is it in cwd? -> execve()
// Is it on PATH? -> change args and then execve
// exit (1);
typedef struct s_execcmd
{
	t_type	type;
	char	*argv[MAXARGS];
	char	*eargv[MAXARGS];
}	t_execcmd;

// Redirection
// fd -> 0 or 1 (input or output)
// file -> file to open
// mode -> O_MODE
// type -> REDIR
// symbols -> << < > >>
typedef struct s_redircmd
{
	t_type	type;
	t_cmd	*cmd;
	char	*file;
	char	*efile;
	int		mode;
	int		fd;
}	t_redircmd;

// Listcmd
// symbol to parse -> ;
// type -> LIST
typedef struct s_listcmd
{
	t_type	type;
	t_cmd	*left;
	t_cmd	*right;
}	t_listcmd;

// Backcmd is used for
// supporting calling a daemon
// process - process with no parent
// running on the background
// type -> BACK
// symbol to parse -> &
typedef struct s_backcmd
{
	t_type	type;
	t_cmd	*cmd;
}	t_backcmd;

// Pipe operator
// type -> PIPE
// symbol to parse -> |
typedef struct s_pipecmd
{
	t_type	type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipecmd;

// Conditionals like && and ||
// Flag is needed to differ between
// && and ||
// 0 for && -> executes next cmd if
// previous was succsesfull
// 1 for || -> executes next cmd if
// previous was failed
// type -> COND
typedef struct s_condcmd
{
	t_type	type;
	t_cmd	*left;
	t_cmd	*rigth;
	int		flag;
}	t_condcmd;

// Whole program's config
typedef struct s_program
{
	t_backcmd	*backcmd;
	t_condcmd	*condcmd;
	t_pipecmd	*pipecmd;
	t_listcmd	*listcmd;
	t_redircmd	*redircmd;
	t_execcmd	*execcmd;
	char		*buffer;
	char		*prompt;
	char		*es;
	char		*ps;
}	t_program;

// signals.c
void	ft_sigquit_handler(int signal);
// init.c
void	ft_program_init(t_program *prog);
void	ft_init_prompt(t_program *prog);
// alloc.c
void	*ft_calloc(size_t nmemb, size_t size);
// memory.c
void	*ft_memset(void *s, int c, size_t n);
// panic.c
void	ft_panic(const char *file, int line, const char *message);
// strings.c
size_t	ft_strlen(const char *str);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strcat(char *dest, const char *src);
// syscall.c
char	*sys_getcwd(char *buf, size_t size);
char	*sys_getenv(const char *name);
// repl.c
void	ft_repl(t_program *prog);
// tokenize.c
int		ft_gettoken(char **ps, char *es, char **q, char **eq);
// cleanup.c
void	ft_cleanup(t_program *program);

#endif
