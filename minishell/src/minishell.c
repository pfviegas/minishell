/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:49:34 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/22 16:55:59 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

struct s_global g_data;

/**
 * Generates a list of commands based on the input string.
 *
 * @param input The input string containing the commands.
 * @return A pointer to the generated list of commands.
 */
t_commands *generate_tokens(char *input)
{
	t_commands	*command;
	char		*prep_input;
	int			array[2];

	prep_input = ft_calloc((ft_strlen(input) * 5), 1);
	if (!prep_input)
		return (NULL);
	array[0] = 0;
	array[1] = 0;
//	faz o parsing
	parsing(prep_input, input, 0, array);

//PFV
	printf ("     input: %s\n", input);
	printf ("prep_input: %s\n\n", prep_input);
//

	g_data.vars->division = ft_split(prep_input, 2);

//PFV
	int indice = 0;
	while (g_data.vars->division[indice])
		printf ("g_data.vars->division: %s\n", g_data.vars->division[indice++]);

	g_data.vars->division = expander(g_data.vars->division, lst_to_arr(g_data.env));
	indice = 0;
	printf ("\n");
	while (g_data.vars->division[indice])
		printf ("g_data.vars->division: %s\n", g_data.vars->division[indice++]);
//

	free(prep_input);
	command = NULL;
	command = lst_new(strlen_array(g_data.vars->division));
//PFV
	printf ("\nPRINT LST (command)\n");
	print_lst(command);
//

	tokens_redirection(command, g_data.vars->division);

//PFV
	printf ("\nPRINT LST (command)\n");
	print_lst(command);
//

//PFV
/*
	g_data.vars->head = command;
	ft_free_matrix(&g_data.vars->division);
*/		
	return (command);
}

void	prompt(void)
{
	char	*input;
	t_commands	*command;

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
//		verifica se a sintaxe esta correta
		syntax_handling(input);
		command = generate_tokens(input);
//PFV
/*
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
