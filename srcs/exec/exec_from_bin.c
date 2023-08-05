/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_from_bin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:41:58 by khorike           #+#    #+#             */
/*   Updated: 2023/08/04 22:04:07 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	support_fork(char **cmds)
{
	if (ft_fork() == 0)
	{
		execve(cmds[0], cmds, NULL);
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
		return ;
	}
}

static int	check_permission_fd(char **cmds, t_directory *dir)
{
	int	tmp;

	tmp = check_file_permission(cmds[0]);
	if (tmp)
	{
		dir->error.error_num = tmp;
		return (FAILURE);
	}
	else if (check_fd_or_dir(cmds[0]))
	{
		dir->error.error_num = 127;
		return (FAILURE);
	}
	return (SUCCESS);
}

void	exec_from_bin(char **cmds, t_directory *dir, t_env_var **env_vars)
{
	struct stat	s;

	if (judgement_desuno(cmds, dir, env_vars))
		return ;
	if (stat(cmds[0], &s) == 0 && ft_strchr(cmds[0], '/'))
	{
		if (S_ISDIR(s.st_mode))
		{
			error_printf("minishell: is a directory", cmds[0]);
			dir->error.error_num = 126;
			return ;
		}
		else if (access(cmds[0], X_OK) == 0)
			support_fork(cmds);
		else
		{
			if (check_permission_fd(cmds, dir))
				return ;
		}
	}
	else
		dir->error.error_num = execute_command(cmds[0], cmds, env_vars);
	return ;
}
