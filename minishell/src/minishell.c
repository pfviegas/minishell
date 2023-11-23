/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:49:34 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/23 15:51:26 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

struct s_global g_var;

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
/*
	printf ("     input: %s\n", input);
	printf ("prep_input: %s\n\n", prep_input);
*/
	g_var.vars->division = ft_split(prep_input, 2);
//PFV
/*
	int indice = 0;
	while (g_var.vars->division[indice])
		printf ("g_var.vars->division: %s\n", g_var.vars->division[indice++]);
*/
	g_var.vars->division = expander(g_var.vars->division, lst_to_arr(g_var.env));
//PFV
/*
	indice = 0;
	printf ("\n");
	while (g_var.vars->division[indice])
		printf ("g_var.vars->division: %s\n", g_var.vars->division[indice++]);
*/
	free(prep_input);
	command = NULL;
	command = lst_new(strlen_array(g_var.vars->division));
//PFV
/*
	printf ("\nPRINT LST (command)\n");
	print_lst(command);
*/
	tokens_redirection(command, g_var.vars->division);

	g_var.vars->head = command;
	free_str_array(&g_var.vars->division);
	return (command);
}

/**
 * @brief Função que solicita ao usuário uma entrada e executa comandos.
 * 
 * Lê a entrada e realiza as seguintes etapas:
 * 1. Verifica se a entrada é NULL. Se for, libera a memória e encerra.
 * 2. Adiciona a entrada ao histórico de comandos.
 * 3. Realiza o tratamento de sintaxe para verificar 
 *    se a entrada possui sintaxe correta.
 * 4. Gera uma lista de comandos a partir da entrada.
 * 5. Verifica se a entrada ou o primeiro comando está vazio. 
 *    Se estiver, define o status de saída como 0.
 * 6. Se a entrada não estiver vazia e nenhuma interrupção ocorrer, 
 *    executa o(s) comando(s).
 * 7. Libera a memória usada pela lista de comandos e pela entrada.
 * 
 * @return void
 */
void	prompt(void)
{
	t_commands	*command;
	char	*input;

	while (1)
	{
		g_var.interrupted = 0;
		input = readline("minishell $ ");
		if (!input)
		{
			if (input)
				free(input);
			free_env(&g_var.env);
			free_vars();
			exit(0);
		}
//		verifica se o input nao é NULL	
		if(*input)
		{
//			adiciona ao historico o comando introduzido 
			add_history(input);
//			verifica se a sintaxe esta correta
			syntax_handling(input);
//			gera a lista de comandos
			command = generate_tokens(input);
			if (!input[0] || !command->content[0] || !command->content[0][0])
				g_var.exit_status = 0;
			if (command->content[0] && !g_var.interrupted)
				executor(command);
			free_list(&command);
			free(input);
		}
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
	g_var.env = get_env_var(env);
//	exit status code	
	g_var.exit_status = 0;
//	indica que o here document nao está ativo (1 = ativo).
	g_var.here_doc = 0;
//	inicializa as variaveis
	g_var.vars = init_vars();
//	define o comportamento dos sinais
	signals_behavior();
//	executa o prompt
	prompt();
}
