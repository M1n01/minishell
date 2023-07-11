/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:17:39 by minabe            #+#    #+#             */
/*   Updated: 2023/07/11 18:08:40 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	lexer(char *str)
{
	size_t	i;
	size_t	j;
	t_token	*token;

	i = 0;
	while (line[i] != '\0')
	{
		j = 0;
		while (str[i + j] != ' ' && str[i + j] != '\0')
			j++;
		tokenlistadd_back(ft_substr(str, i, j));
		i += j;
	}
	return (token);
}