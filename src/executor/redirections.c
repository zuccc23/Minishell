#include "../../include/minishell.h"

static int	apply_input_redirection(t_redirection *redir, t_exec *exec)
{
	int	fd;

	if (redir->type != REDIR_INPUT)
		return (0);
	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
	{
		putstr_err("minishell: ", redir->file, ": Permission denied\n");
		exec->last_exit_status = 1;
		exit(-1);
	}
	if (exec->infile_fd != -1)
		safe_close(&exec->infile_fd);
	exec->infile_fd = fd;
	return (0);
}

static int	apply_output_redirection(t_redirection *redir, t_exec *exec)
{
	int	fd;

	if (redir->type != REDIR_OUTPUT)
		return (0);
	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		putstr_err("minishell: ", redir->file, ": Permission denied\n");
		exec->last_exit_status = 1;
		return (-1);
	}
	if (exec->outfile_fd != -1)
		safe_close(&exec->outfile_fd);
	exec->outfile_fd = fd;
	return (0);
}

static int	apply_append_redirection(t_redirection *redir, t_exec *exec)
{
	int	fd;

	if (redir->type != REDIR_APPEND)
		return (0);
	fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		putstr_err("minishell: ", redir->file, ": Permission denied\n");
		exec->last_exit_status = 1;
		return (-1);
	}
	if (exec->outfile_fd != -1)
		safe_close(&exec->outfile_fd);
	exec->outfile_fd = fd;
	return (0);
}

static int	apply_heredoc_redirection(t_redirection *redir, t_exec *exec)
{
	if (redir->type != REDIR_HEREDOC)
		return (0);
	if (redir->fd == -1)
	{
		ft_putstr_fd("minishell: heredoc error\n", STDERR_FILENO);
		exec->last_exit_status = 1;
		return (-1);
	}
	if (exec->infile_fd != -1)
		safe_close(&exec->infile_fd);
	exec->infile_fd = redir->fd;
	return (0);
}

int	apply_redirection(t_command *cmd, t_exec *exec)
{
	t_redirection	*redir;

	redir = NULL;
	redir = cmd->redirections;
	while (redir)
	{
		if (apply_input_redirection(redir, exec) == -1)
			return (-1);
		if (apply_output_redirection(redir, exec) == -1)
			return (-1);
		if (apply_append_redirection(redir, exec) == -1)
			return (-1);
		if (apply_heredoc_redirection(redir, exec) == -1)
			return (-1);
		redir = redir->next;
	}
	return (0);
}
