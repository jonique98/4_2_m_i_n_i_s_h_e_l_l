/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josumin <josumin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:27:37 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/08 14:24:51 by josumin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
typedef struct s_lst{
    int     fd_in;
    int     fd_out;
	char	**cmd;
    int     prev_pipe;
	struct s_lst *next;
} t_lst;

typedef struct s_arg
{
	char	**env;
	char	**path;
	t_lst	*lst;
} t_arg;

// int ft_cd(t_arg *arg, char **cmd)
// {
// 	if (!check_cmd(cmd))
// 		return (1);
// }

int main(int ac, char **av)
{
	if (access(av[1], F_OK) == 0)
		printf("File exists\n");
	else
	{
		printf("File does not exist\n");
		exit(1);
	}
	
	if (access(av[1], R_OK) == 0)
		printf("File is readable\n");
	else
	{
		printf("File is not readable\n");
		exit(1);
	}
	
	if (chdir(av[1]) == 0)
		printf("Directory changed\n");
	else
	{
		printf("not a directory\n");
		exit(1);
	}
}

