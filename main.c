/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:53:03 by jiko              #+#    #+#             */
/*   Updated: 2024/01/26 01:10:00 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	heredoc_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	set_signal(int sig_int, int sig_quit)
{
	if (sig_int == IGN)
		signal(SIGINT, SIG_IGN);
	if (sig_int == DFL)
		signal(SIGINT, SIG_DFL);
	if (sig_int == SHE)
		signal(SIGINT, signal_handler);
	if (sig_quit == IGN)
		signal(SIGQUIT, SIG_IGN);
	if (sig_quit == DFL)
		signal(SIGQUIT, SIG_DFL);
	if (sig_quit == SHE)
		signal(SIGQUIT, signal_handler);
	if (sig_int == HED)
		signal(SIGINT, SIG_DFL);
	if (sig_quit == HED)
		signal(SIGQUIT, SIG_IGN);
}

t_env	*main_init(int argc, char **argv, char **env)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	set_signal(SHE, SHE);
	(void)argc;
	(void)argv;
	return (make_env_lst(env));
}

int	main(int argc, char **argv, char **env)
{
	char			*line;
	t_token			*token;
	t_cmd_tree		*cmd_tree;
	t_env			*env_lst;
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	env_lst = main_init(argc, argv, env);
	while (1)
	{
		token = NULL;
		cmd_tree = NULL;
		line = readline("minishell$ ");
		if (!line)
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			exit(g_exit);
		}
			// break ;
		add_history(line);
		if (tokenizer(line, &token) || parser(&cmd_tree, &token))
			continue ;
		// print_token(token); //test
		// test_tr_print_tree(cmd_tree); //test
		// test_tr_print_tree(cmd_tree); //test
		start_exec(cmd_tree, env_lst);
		free_cmd_tree(cmd_tree);
		free_token(token);
	}
	free_env_lst(env_lst);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (g_exit);
}
