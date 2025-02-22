/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:10:06 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/22 20:35:04 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stddef.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <linux/limits.h>
# include <stdbool.h>
# include <termios.h>
# include <term.h>

# define EXEC 1
# define REDIR 2
# define PIPE 3
# define LIST 4
# define BACK 5
# define OR 6
# define AND 7
# define MAXARGS 15
# define WHITESPACE " \t\r\n\v"
# define SYMBOLS "<|>&;()\"'"
# define STDOUT 100
# define STDIN 101
# define APPEND 102
# define HEREDOC 103
# define HEREDOC_PATH "/tmp/hrdc_tpm"
# define EXIT_CMD_NOT_FOUND 127
# define NO_BUILTIN_FOUND 404
# define EXIT_MINISHEL_ERR 2

typedef struct s_cmd
{
	int	type;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_env	*env_list;
	char	**envp;
	int		e_code;
	t_cmd	*head;
}	t_shell;

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

//	&&
typedef struct s_andcmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_andcmd;

//	||
typedef struct s_orcmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_orcmd;

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

/*
	CONSTRUCTOR FUNTIONS
	***************************
*/
t_cmd	*execcmd(void);
t_cmd	*redircmd(t_cmd *subcmd, char *file, char *efile, int mode);
t_cmd	*pipecmd(t_cmd *left, t_cmd *right);
t_cmd	*listcmd(t_cmd *left, t_cmd *right);
t_cmd	*andcmd(t_cmd *left, t_cmd *right);
t_cmd	*orcmd(t_cmd *left, t_cmd *right);
t_cmd	*backcmd(t_cmd *subcmd);
/*
	***************************
*/
/*
	PARSING FUNCTIONS
	***************************
*/
t_cmd	*parsecmd(char *s);
t_cmd	*parseline(char **ps, char *es);
t_cmd	*parsepipe(char **ps, char *es);
t_cmd	*parseredirs(t_cmd *cmd, char **ps, char *es);
t_cmd	*parseblock(char **ps, char *es);
t_cmd	*parseexec(char **ps, char *es);
int		gettoken(char **ps, char *es, char **q, char **eq);
int		peek(char **ps, char *es, char *toks);
t_cmd	*nulterminate(t_cmd *cmd);
t_env	*create_env_node(char *key, char *value);
char	*ft_getenv(const char *key, t_shell *shell);
int		check_builtins(char **argv, t_shell *shell);
char	**convert_env_to_array(t_shell *shell);
int		evaluate_input(char *buffer, t_shell *shell);
char	*expand_variable(char *str, int *i, t_shell *shell);
int		get_token_bonus(char **ps, char *s);
/*
	***************************
*/
/*
	EXECUTOR FUNCTIONS
	***************************
*/
void	runcmd(t_cmd *cmd, t_shell *sh);
void	handle_exec_null(t_execcmd *ecmd);
void	handle_redir_null(t_redircmd *rcmd);
void	handle_pipe_null(t_pipecmd	*pcmd);
void	handle_list_null(t_listcmd	*lcmd);
void	handle_back_null(t_backcmd	*bcmd);
void	handle_and_null(t_andcmd *lcmd);
void	handle_or_null(t_orcmd *lcmd);
void	handle_or_cmd(t_orcmd *lcmd, t_shell *sh);
void	handle_and_cmd(t_andcmd *lcmd, t_shell *sh);
void	handle_heredoc_cmd(char *limiter);
int		ft_try_find_cmd(t_execcmd *ecmd, t_shell *shell);
int		handle_pwd_command(t_shell *shell);
int		handle_exit_command(char **argv, t_shell *shell);
int		handle_echo_command(char **argv, t_shell *shell);
int		handle_env_command(t_shell *shell);
int		handle_cd_command(char **argv, t_shell *shell);
int		handle_export_command(char **argv, t_shell *shell);
int		handle_unset_command(char **argv, t_shell *shell);
int		check_builtins_non_fork(char *buffer, t_shell *shell);
void	unset_var(t_shell *shell, char *key);
void	export_var(t_shell *shell, char *key, char *value);
void	init_env(t_shell *shell, char **envp);
void	ft_sigquit_handler(int sig);
void	update_env_array(t_shell *shell);
/*
	***************************
*/
/*
	STRING/LIBFT FUNCTIONS
	***************************
*/
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
char	*ft_itoa(int n);
void	ft_putendl_fd(const char *s, int fd);
char	*ft_strdup(const char *s);
char	**ft_split(char const *s, char c);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strncpy(char *dest, const char *src, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *s);
char	*ft_strchr(const char *s, int c);
bool	ft_isstralnum(char *str);
/*
	***************************
*/
/*
	UTILS
	***************************
*/
void	free_tree(t_cmd *cmd);
int		fork1(void);
void	panic(char *s, int exit_code, t_shell *shell);
int		getcmd(char *buf, int nbuf);
void	print_tree(t_cmd *cmd, int depth);
void	ft_free_split(char **split);
void	cleanup_env(t_shell *shell);
int		split_free_wrapper(char **split, int i, t_shell *shell);
void	exit_shell(t_shell *shell, int exit_code);
void	free_pipe(t_pipecmd *pcmd);
void	free_list(t_listcmd *lcmd);
void	free_and(t_andcmd *acmd);
void	free_or(t_orcmd *acmd);
void	free_back(t_backcmd *bcmd);
bool	is_non_fork(char **argv);
void	ft_sig_child_handler(int sig);
bool	ft_isdigit(int c);
void	ft_close_descriptors(int *p);
bool	is_empty_or_spaces(const char *str);
void	ft_norm1(char *p1, char *p2);

#endif
