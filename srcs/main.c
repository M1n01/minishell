/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 20:26:51 by minabe            #+#    #+#             */
/*   Updated: 2023/07/24 19:45:38 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	(void)argv;
	if (argc == 1)
		minishell(envp);
	return (0);
}

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q minishell");
// }
