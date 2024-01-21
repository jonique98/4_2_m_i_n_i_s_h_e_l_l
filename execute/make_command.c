/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 19:48:59 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/22 03:30:34 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	parse_commands(t_arg *arg, char **cmd)
{
	int		i;
	char	*arr;

	i = 0;
	if (arg->path == NULL)
	{
		throw_error(cmd[0], "No Such file or directory", 0);
		exit(127);
	}
	while (arg->path[i])
	{
		arr = ft_strdup(arg->path[i]);
		arr = ft_strjoin(arr, cmd[0]);
		if (access(arr, F_OK) == 0)
		{
			cmd[0] = arr;
			return ;
		}
		free(arr);
		i++;
	}
	throw_error(cmd[0], "command not found", 0);
	exit(127);
}

char	**return_commands(t_arg	*arg, char **cmd)
{
	if (cmd[0][0] != '/' && cmd[0][0] != '.')
	{
		parse_commands(arg, cmd);
		return (cmd);
	}
	if (access(cmd[0], F_OK) == -1)
	{
		throw_error(cmd[0], 0, "No Such file or directory");
		exit(127);
	}
	if (opendir(cmd[0]) != NULL)
	{
		throw_error(cmd[0], 0, "is a directory");
		exit(126);
	}
	if (access(cmd[0], X_OK) == -1)
	{
		throw_error(cmd[0], 0, "Permission denied");
		exit(126);
	}
	return (cmd);
}
