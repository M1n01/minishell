/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:23:15 by minabe            #+#    #+#             */
/*   Updated: 2023/08/15 19:28:05 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tokentype	judge_tokentype(char *data)
{
	if (data == NULL)
		return (-1);
	if (data[0] == '|')
		return (CHAR_PIPE);
	if (data[0] == '\'' && data[ft_strlen(data) - 1] == '\'')
		return (CHAR_QUOTE);
	if (data[0] == '\"' && data[ft_strlen(data) - 1] == '\"')
		return (CHAR_DQUOTE);
	if (data[0] == '<' && data[1] == '<')
		return (CHAR_D_LESSER);
	if (data[0] == '>' && data[1] == '>')
		return (CHAR_D_GREATER);
	if (is_redirect(data[0]))
		return (data[0]);
	else
		return (CHAR_GENERAL);
}

t_token	*token_new(char *data)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		exit(EXIT_FAILURE);
	new->data = data;
	new->prev = NULL;
	new->next = NULL;
	new->type = judge_tokentype(data);
	return (new);
}

t_token	*tokenlistadd_back(t_token *token, char *data, int *flag)
{
	t_token	*new;
	t_token	*head;

	if (*data == '\0')
		return (token);
	if (token->data == NULL)
	{
		token->data = data;
		token->type = judge_tokentype(data);
		if (token->type == CHAR_PIPE && token->next == NULL)
		{
			*flag = 1;
			return (NULL);
		}
		return (token);
	}
	head = token;
	new = token_new(data);
	while (token->next != NULL)
		token = token->next;
	token->next = new;
	return (head);
}

void	tokenlist_clear(t_token *token)
{
	t_token	*tmp;

	while (token != NULL)
	{
		tmp = token->next;
		ft_free(token->data);
		ft_free(token);
		token = tmp;
	}
}
