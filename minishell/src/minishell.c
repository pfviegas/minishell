/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:49:34 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/21 17:08:37 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

struct s_global g_data;

void	prompt(void)
{
	char	*input;
//	t_commands	*command;

	while (1)
	{
		g_data.interrupted = 0;
		input = readline("$ ");
		if (!input)
		{
			if (input)
				free(input);
			free_env(&g_data.env);
			free_vars();
			exit(0);
		}
//		adiciona ao historico o comando introduzido 
		add_history(input);

		syntax_handling(input);
//PFV
/*
		command = generate_list(input);
		if (!input[0] || !command->content[0] || !command->content[0][0])
			g_data.exit_status = 0;
		if (command->content[0] && !g_data.interrupted)
			execution(command);
		ft_free_list(&command);
*/		
		free(input);
	}
}

int	main(int argc, char **argv, char **env)
{
//	t_env	*env_list;

//	verifica se o numero de argumentos é valido	
	(void)argv;
	if (argc != 1)
		return (1);
//	limpa o historico do readline
	rl_clear_history();
//	desativa a captura de sinais pelo readline 
	rl_catch_signals = 0;
//	retorna as variaveis de ambiente	
	g_data.env = get_env_var(env);
//	exit status code	
	g_data.exit_status = 0;
//	indica que o here document nao está ativo (1 = ativo).
	g_data.here_doc = 0;
//	inicializa as variaveis
	g_data.vars = init_vars();
//	define o comportamento dos sinais
	signals_behavior();
//	executa o prompt
	prompt();
}
