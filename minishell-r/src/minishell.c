/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: correia <correia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:55:11 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/14 16:09:37 by correia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Estrutura Principal
/**
 * @brief Retorna um ponteiro para a estrutura t_shell.
 * 
 * Esta função retorna um ponteiro para a estrutura t_shell, 
 * que é uma estrutura utilizada para armazenar informações do Minishell.
 * 
 * @return Um ponteiro para a estrutura t_shell.
 */
t_shell	*shell(void)
{
	static t_shell	shell;

	return (&shell);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line_prompt;
	int		i;

	if (argc != 1)
	{
		write(2, "minishell: ", 11);
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, ": No such file or directory\n", 28);
		return (127);
	}
	rl_clear_history();
	rl_catch_signals = 0;
	signals_behavior();
	shell()->prompt = true;
	init_shell_vars(shell(), envp);
	while (shell()->prompt)
	{
		i = 0;
		line_prompt = readline("minishell$ ");
		if (!line_prompt)
		{
			printf("exit\n");
			free_all(true, false, true, false);
			exit(0);
		}
		if (line_prompt[0] != '\n' && line_prompt[0] != '\0')
		{
			while (line_prompt && (line_prompt[i] == ' ' || \
			line_prompt[i] == '\t'))
				i++;
			if (line_prompt[i] == 0)
				continue ;
			add_history(line_prompt);
			parsing(line_prompt);
			if (!shell()->error)
				executor(shell()->segments_lst);
			free_all(false, true, false, false);
		}
	}
	free_all(true, false, true, false);
	rl_clear_history();
	return (shell()->exit_code);
}
