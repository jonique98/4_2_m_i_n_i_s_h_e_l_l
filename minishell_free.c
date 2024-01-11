/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:25:20 by jiko              #+#    #+#             */
/*   Updated: 2024/01/11 22:27:03 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	safe_free(void *str)
{
	if (str)
		free(str);
}

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		safe_free(token->word);
		free(token);
		token = tmp;
	}
}

void	free_cmd_tree(t_cmd_tree *cmd_tree)
{
	if (cmd_tree->left)
		free_cmd_tree(cmd_tree->left);
	if (cmd_tree->right)
		free_cmd_tree(cmd_tree->right);
	safe_free(cmd_tree);
}
