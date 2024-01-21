/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_util2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 03:09:27 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/21 20:28:48 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_print_env(char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = -1;
		while (env[i][++j])
		{
			ft_putchar_fd(env[i][j], 1);
			if (env[i][j] == '=')
				ft_putchar_fd('\"', 1);
		}
		if (has_char(env[i], '=') && env[i][j] == '\0')
			ft_putstr_fd("\"", 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (0);
}

char	**ft_sort_env(char **env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[j])
		{
			if (ft_strncmp(env[i], env[j], ft_strlen(env[j])) < 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (env);
}

int	modify_env(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '=')
		{
			if ((*str)[i + 1] == '\0')
			{
				*str = ft_strjoin(*str, "\"\"");
				return (0);
			}
			else
				return (0);
		}
		i++;
	}
	return (0);
}

int	throw_error(char *cmd, char *str, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (str)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(msg, 2);
	return (1);
}

void	free_env_lst(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		safe_free(env->key);
		safe_free(env->value);
		safe_free(env);
		env = tmp;
	}
	return ;
}
