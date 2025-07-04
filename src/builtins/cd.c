/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:31:23 by dahmane           #+#    #+#             */
/*   Updated: 2025/06/30 18:31:24 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//changes current working directory
//returns 1 if any error occurs, 0 if ok
int	bltin_cd(t_command *cmd, char ***env)
{
	DIR		*dir;

	if (cd_errors(cmd) != ER_OK)
		return (1);
	dir = opendir(cmd->args[1]);
	if (dir == NULL)
	{
		putstr_err("minishell: cd: ", cmd->args[1], ": ");
		perror("");
		return (1);
	}
	if (chdir(cmd->args[1]) == -1)
	{
		putstr_err("minishell: ", "cd: error changing", " directories\n");
		closedir(dir);
		return (1);
	}
	change_env(&(*env));
	if (closedir(dir) == -1)
	{
		ft_putstr_fd("minishell: \n", STDERR_FILENO);
		ft_putstr_fd("cd: error closing directory stream\n", STDERR_FILENO);
		return (1);
	}
	return (ER_OK);
}

//handles errors messages of cd
int	cd_errors(t_command *cmd)
{
	if (!cmd->args[1])
	{
		ft_putstr_fd("minishell: cd: an absolute or ", STDERR_FILENO);
		ft_putstr_fd("relative path must be given\n", STDERR_FILENO);
		return (1);
	}
	if (cmd->args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	return (ER_OK);
}

// returns a char ** with the result of pwd
char	**return_pwd(char **env)
{
	char	**dir;
	char	buff[1024];
	char	*getenv_res;

	getenv_res = ft_getenv("PWD", env);
	dir = malloc(sizeof(char *) * 3);
	if (!dir || !getenv_res)
		return (NULL);
	free(getenv_res);
	dir[0] = ft_strdup("export");
	if (!dir[0])
	{
		free(dir);
		return (NULL);
	}
	dir[1] = ft_strjoin("PWD=", getcwd(buff, 1024));
	if (!dir[1])
	{
		free_strs(dir);
		return (NULL);
	}
	dir[2] = NULL;
	return (dir);
}

// returns a char ** with the result of oldpwd
char	**return_oldpwd(char **env)
{
	char	**dir;
	char	*getenv_res;

	dir = malloc(sizeof(char *) * 3);
	if (!dir)
		return (NULL);
	getenv_res = ft_getenv("PWD", env);
	dir[0] = ft_strdup("export");
	if (!dir[0] || !getenv_res)
	{
		free(dir);
		return (NULL);
	}
	dir[1] = ft_strjoin("OLDPWD=", getenv_res);
	free(getenv_res);
	if (!dir[1])
	{
		free_strs(dir);
		return (NULL);
	}
	dir[2] = NULL;
	return (dir);
}

int	change_env(char ***env)
{
	char	**pwd;
	char	**oldpwd;

	oldpwd = return_oldpwd(*env);
	if (!oldpwd)
		return (0);
	bltin_export(oldpwd, env);
	free_strs(oldpwd);
	pwd = return_pwd(*env);
	if (!pwd)
	{
		if (oldpwd)
			free_strs(oldpwd);
		return (0);
	}
	bltin_export(pwd, env);
	free_strs(pwd);
	return (ER_OK);
}
