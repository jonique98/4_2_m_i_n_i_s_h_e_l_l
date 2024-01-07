/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:27:20 by jiko              #+#    #+#             */
/*   Updated: 2024/01/07 22:45:04 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	remove_space(char *line, int *i)
{
	int	flag;

	flag = 0;
	while (line[*i] && is_space(line[*i]))
	{
		(*i)++;
		flag = 1;
	}
	return (flag);
}

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		if (token->word)
			free(token->word);
		free(token);
		token = tmp;
	}
}



