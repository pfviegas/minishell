/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:55:11 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/19 20:46:37 by pveiga-c         ###   ########.fr       */
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

/**
 * Função responsável por lidar com a saida.
 * Imprime a mensagem "exit" e libera a memória alocada.
 * Encerra o programa com código de saída 0.
 */
void	handle_exit(void)
{
	printf("exit\n");
	free_all(true, false, true, false);
	exit(0);
}

/**
 * Função responsável por processar uma linha de entrada.
 *
 * @param line_prompt A linha de entrada a ser processada.
 */
void	process_input_line(char *line_prompt)
{
	int	i;

	i = 0;
	while (line_prompt && (line_prompt[i] == ' ' || line_prompt[i] == '\t'))
		i++;
	if (line_prompt[i] == '\0')
		add_history(line_prompt);
	else if (line_prompt[i] != '\0' && line_prompt[i] != '\n')
	{
		if (ft_strcmp(shell()->rep_prompt, line_prompt) != 0)
		{
			add_history(line_prompt);
			free(shell()->rep_prompt);
			shell()->rep_prompt = ft_strdup(line_prompt);
		}
		parsing(line_prompt);
		if (!shell()->error)
			executor(shell()->segments_lst);
		free_all(false, true, false, false);
	}
}

/**
 * Função responsável por executar o loop principal do shell.
 */
void	main_shell_loop(void)
{
	char	*line_prompt;

	line_prompt = NULL;
	while (shell()->prompt)
	{
		line_prompt = readline("minishell$ ");
		if (!line_prompt)
			handle_exit();
		if (line_prompt[0] != '\n' && line_prompt[0] != '\0')
			process_input_line(line_prompt);
	}
}

/**
 * Função principal do programa minishell.
 * 
 * Esta função é responsável por executar o minishell, 
 * um interpretador de comandos simplificado. 
 * Recebe os argumentos da linha de comando, 
 * bem como o ambiente do sistema e executa o loop principal do shell.
 * 
 * @param argc O número de argumentos da linha de comando.
 * @param argv Um array de strings contendo os argumentos da linha de comando.
 * @param envp Um array de strings contendo as variáveis de ambiente do sistema.
 * @return O código de saída do shell.
 */
int	main(int argc, char **argv, char **envp)
{
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
	main_shell_loop();
	free_all(true, false, true, false);
	rl_clear_history();
	return (shell()->exit_code);
}
