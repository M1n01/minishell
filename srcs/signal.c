/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 11:15:47 by khorike           #+#    #+#             */
/*   Updated: 2023/08/05 16:04:25 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_interrupted = 0;

void	handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
		;
	g_interrupted = 1;
}

void	setup_signals(void)
{
	if (signal(SIGINT, handle_signal) == SIG_ERR)
	{
		exit(EXIT_FAILURE);
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		exit(EXIT_FAILURE);
	}
}

static void	execute_and_reset_error(t_node *node, t_directory *dir,
		t_env_var **env_vars, int *error)
{
	if (node == NULL)
	{
		if (*error == 2)
			dir->error.error_num = 2;
		if (*error == 1)
			dir->error.error_num = 1;
	}
	execution(node, dir, env_vars);
	*error = 0;
}

void	handle_interruption(t_node *node, t_directory *dir,
			t_env_var **env_vars, int *error)
{
	if (g_interrupted == 1)
	{
		*error = g_interrupted;
		dir->error.error_num = g_interrupted;
		g_interrupted = 0;
	}
	execute_and_reset_error(node, dir, env_vars, error);
}
