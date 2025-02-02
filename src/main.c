/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:48:35 by yustinov          #+#    #+#             */
/*   Updated: 2025/01/31 15:24:35 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <stddef.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

#define EXEC 1
#define REDIR 2
#define PIPE 3
#define LIST 4
#define BACK 5

#define MAXARGS 10

struct cmd
{
	int type;
};

struct execcmd
{
	int type;
	char *argv[MAXARGS];
	char *eargv[MAXARGS];
};

struct redircmd
{
	int type;
	struct cmd *cmd;
	char *file;
	char *efile;
	int mode;
	int fd;
};

struct listcmd
{
	int type;
	struct cmd *left;
	struct cmd *right;
};

struct backcmd
{
	int type;
	struct cmd *cmd;
};

struct pipecmd
{
	int type;
	struct cmd *left;
	struct cmd *right;
};

// Fork wrapper, panics on failure.
int fork1(void);
void panic(char *);
struct cmd *parsecmd(char *);

int	ft_try_find_cmd(struct execcmd *ecmd)
{
	char	*path_env = getenv("PATH");
	char	*path, *full_path;
	size_t	len;

	// Do nothing if the exe present in cwd
	if (access(ecmd->argv[0], X_OK) == 0)
		return 0;

	if (path_env == NULL)
		return -1;

	path = strtok(path_env, ":");
	while (path != NULL)
	{
		len = strlen(path) + strlen(ecmd->argv[0]) + 2;
		full_path = malloc(len);
		if (full_path == NULL)
			panic("malloc");
		snprintf(full_path, len, "%s/%s", path, ecmd->argv[0]);
		if (access(full_path, X_OK) == 0)
		{
			ecmd->argv[0] = full_path;
			return (0);
		}
		free(full_path);
		path = strtok(NULL, ":");
	}
	return -1;
}

void runcmd(struct cmd *cmd)
{
	int p[2];
	struct backcmd *bcmd;
	struct execcmd *ecmd;
	struct listcmd *lcmd;
	struct pipecmd *pcmd;
	struct redircmd *rcmd;

	if (cmd == 0)
		exit(0);

	switch (cmd->type)
	{
	default:
		panic("runcmd");
	case EXEC:
		ecmd = (struct execcmd *)cmd;
		if (ecmd->argv[0] == 0)
			exit(0);
		// Check wether command exists in cwd or in PATH then execute;
		if (ft_try_find_cmd(ecmd) == -1)
		{
			fprintf(stderr, "command %s not found\n", ecmd->argv[0]);
			break ;
		}
		execve(ecmd->argv[0], ecmd->argv, NULL);
		fprintf(stderr, "exec %s failed\n", ecmd->argv[0]);
		break;
	case REDIR:
		rcmd = (struct redircmd *)cmd;
		close(rcmd->fd);
		if (open(rcmd->file, rcmd->mode, 0644) < 0)
		{
			fprintf(stderr, "open %s failed\n", rcmd->file);
			exit(1);
		}
		runcmd(rcmd->cmd);
		break;
	case LIST:
		lcmd = (struct listcmd *)cmd;
		if (fork1() == 0)
			runcmd(lcmd->left);
		wait(0);
		runcmd(lcmd->right);
		break;
	case PIPE:
		pcmd = (struct pipecmd *)cmd;
		if (pipe(p) < 0)
			panic("pipe");
		if (fork1() == 0)
		{
			close(1);
			dup(p[1]);
			close(p[0]);
			close(p[1]);
			runcmd(pcmd->left);
		}
		if (fork1() == 0)
		{
			close(0);
			dup(p[0]);
			close(p[0]);
			close(p[1]);
			runcmd(pcmd->right);
		}
		close(p[0]);
		close(p[1]);
		wait(0);
		wait(0);
		break;
	case BACK:
		bcmd = (struct backcmd *)cmd;
		if (fork1() == 0)
			runcmd(bcmd->cmd);
		break;
	}
	exit(0);
}

char *gets(char *buf, int max)
{
	int i, cc;
	char c;

	for (i = 0; i + 1 < max;)
	{
		cc = read(0, &c, 1);
		if (cc < 1)
			break;
		buf[i++] = c;
		if (c == '\n' || c == '\r')
			break;
	}
	buf[i] = '\0';
	return buf;
}

void *memset(void *s, int c, size_t n)
{
	unsigned char *p = s;
	while (n--)
	{
		*p++ = (unsigned char)c;
	}
	return s;
}

int getcmd(char *buf, int nbuf)
{
	char *input;

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

void ft_sigquit_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int main(void)
{
	static char buffer[100];
	int fd;

	// Handle Ctrl+C Ctrl+\

	signal(SIGINT, ft_sigquit_handler);
	signal(SIGQUIT, SIG_IGN);

	// Ensure that three file descriptors are open.
	while ((fd = open("console", O_RDONLY)) >= 0)
	{
		if (fd >= 3)
		{
			close(fd);
			break;
		}
	}

	// REPL
	while (getcmd(buffer, sizeof(buffer)) >= 0)
	{
		if (buffer[0] == 'c' && buffer[1] == 'd' && buffer[2] == ' ')
		{
			if (chdir(buffer + 3) < 0)
				fprintf(stderr, "cannot cd %s\n", buffer + 3);
			continue;
		}
		if (fork1() == 0)
			runcmd(parsecmd(buffer));
		wait(0);
	}
	exit(0);
}

void panic(char *s)
{
	fprintf(stderr, "%s\n", s);
	exit(1);
}

int fork1(void)
{
	int pid;

	pid = fork();
	if (pid == -1)
		panic("fork");
	return pid;
}

struct cmd *execcmd(void)
{
	struct execcmd *cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = EXEC;
	return (struct cmd *)cmd;
}

struct cmd *redircmd(struct cmd *subcmd, char *file, char *efile, int mode, int fd)
{
	struct redircmd *cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = REDIR;
	cmd->cmd = subcmd;
	cmd->file = file;
	cmd->efile = efile;
	cmd->mode = mode;
	cmd->fd = fd;
	return (struct cmd *)cmd;
}

struct cmd *pipecmd(struct cmd *left, struct cmd *right)
{
	struct pipecmd *cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return (struct cmd *)cmd;
}

struct cmd *listcmd(struct cmd *left, struct cmd *right)
{
	struct listcmd *cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = LIST;
	cmd->left = left;
	cmd->right = right;
	return (struct cmd *)cmd;
}

struct cmd *backcmd(struct cmd *subcmd)
{
	struct backcmd *cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = BACK;
	cmd->cmd = subcmd;
	return (struct cmd *)cmd;
}

char whitespace[] = " \t\r\n\v";
char symbols[] = "<|>&;()\"'";

// we want to also be able to parse "" '' <<(-) &&(?) ||(!)
/*
	Gettoken is going to scan and find the next token
	**ps -> pointer to a variable of the place where to begin the scanning
			after the scan it will update the underlying pointer to the next char so ps->s->(some char)
	*es -> end of the scan -> points to byte after the last one we want to consider
	**q -> points to where the token begins q->token_start
	**eq -> points to byte after the token
*/
int gettoken(char **ps, char *es, char **q, char **eq)
{
	char *s;
	int ret;

	s = *ps;
	while (s < es && strchr(whitespace, *s))
		s++;
	if (q)
		*q = s;
	ret = *s;
	switch (*s)
	{
	case 0:
		break;
	case '|':
	case '(':
	case ')':
	case ';':
	case '&':
	case '<':
		s++;
		break;
	case '>':
		s++;
		if (*s == '>')
		{
			ret = '+';
			s++;
		}
		break;
	default:
		ret = 'a';
		while (s < es && !strchr(whitespace, *s) && !strchr(symbols, *s))
			s++;
		break;
	}
	if (eq)
		*eq = s;
	while (s < es && strchr(whitespace, *s))
		s++;
	*ps = s;
	return ret;
}

int peek(char **ps, char *es, char *toks)
{
	char *s;

	s = *ps;
	while (s < es && strchr(whitespace, *s))
		s++;
	*ps = s;
	return *s && strchr(toks, *s);
}

struct cmd *parseline(char **, char *);
struct cmd *parsepipe(char **, char *);
struct cmd *parseexec(char **, char *);
struct cmd *nulterminate(struct cmd *);

struct cmd *parsecmd(char *s)
{
	char *es;
	struct cmd *cmd;

	es = s + strlen(s);
	cmd = parseline(&s, es);
	peek(&s, es, "");
	if (s != es)
	{
		fprintf(stderr, "leftovers: %s\n", s);
		panic("syntax");
	}
	nulterminate(cmd);
	return cmd;
}

struct cmd *parseline(char **ps, char *es)
{
	struct cmd *cmd;

	cmd = parsepipe(ps, es);
	while (peek(ps, es, "&"))
	{
		gettoken(ps, es, 0, 0);
		cmd = backcmd(cmd);
	}
	if (peek(ps, es, ";"))
	{
		gettoken(ps, es, 0, 0);
		cmd = listcmd(cmd, parseline(ps, es));
	}
	return cmd;
}

struct cmd *parsepipe(char **ps, char *es)
{
	struct cmd *cmd;

	cmd = parseexec(ps, es);
	if (peek(ps, es, "|"))
	{
		gettoken(ps, es, 0, 0);
		cmd = pipecmd(cmd, parsepipe(ps, es));
	}
	return cmd;
}

struct cmd *parseredirs(struct cmd *cmd, char **ps, char *es)
{
	int tok;
	char *q, *eq;

	while (peek(ps, es, "<>"))
	{
		tok = gettoken(ps, es, 0, 0);
		if (gettoken(ps, es, &q, &eq) != 'a')
			panic("MIssing file for redirection");
		switch (tok)
		{
		case '<':
			cmd = redircmd(cmd, q, eq, O_RDONLY, 0);
			break;
		case '>':
			cmd = redircmd(cmd, q, eq, O_WRONLY | O_CREAT, 1);
			break;
		case '+': // >>
			cmd = redircmd(cmd, q, eq, O_WRONLY | O_CREAT | O_APPEND, 1);
			break;
		}
	}
	return cmd;
}

struct cmd *parseblock(char **ps, char *es)
{
	struct cmd *cmd;

	if (!peek(ps, es, "("))
		panic("parseblock");
	gettoken(ps, es, 0, 0);
	cmd = parseline(ps, es);
	if (!peek(ps, es, ")"))
		panic("syntax - missing )");
	gettoken(ps, es, 0, 0);
	cmd = parseredirs(cmd, ps, es);
	return cmd;
}

struct cmd *parseexec(char **ps, char *es)
{
	char *q, *eq;
	int tok, argc;
	struct execcmd *cmd;
	struct cmd *ret;

	if (peek(ps, es, "("))
		return parseblock(ps, es);
	ret = execcmd();
	cmd = (struct execcmd *)ret;

	argc = 0;
	ret = parseredirs(ret, ps, es);
	while (!peek(ps, es, "|)&;"))
	{
		if ((tok = gettoken(ps, es, &q, &eq)) == 0)
			break;
		if (tok != 'a')
			panic("syntax");
		cmd->argv[argc] = q;
		cmd->eargv[argc] = eq;
		argc++;
		if (argc > MAXARGS)
			panic("too many args");
		ret = parseredirs(ret, ps, es);
	}
	cmd->argv[argc] = 0;
	cmd->eargv[argc] = 0;
	return ret;
}

struct cmd *nulterminate(struct cmd *cmd)
{
	int i;
	struct backcmd *bcmd;
	struct execcmd *ecmd;
	struct listcmd *lcmd;
	struct pipecmd *pcmd;
	struct redircmd *rcmd;

	if (cmd == 0)
		return 0;

	switch (cmd->type)
	{
	case EXEC:
		ecmd = (struct execcmd *)cmd;
		for (i = 0; ecmd->argv[i]; i++)
			*ecmd->eargv[i] = 0;
		break;

	case REDIR:
		rcmd = (struct redircmd *)cmd;
		nulterminate(rcmd->cmd);
		*rcmd->efile = 0;
		break;

	case PIPE:
		pcmd = (struct pipecmd *)cmd;
		nulterminate(pcmd->left);
		nulterminate(pcmd->right);
		break;

	case LIST:
		lcmd = (struct listcmd *)cmd;
		nulterminate(lcmd->left);
		nulterminate(lcmd->right);
		break;

	case BACK:
		bcmd = (struct backcmd *)cmd;
		nulterminate(bcmd->cmd);
		break;
	}
	return cmd;
}
