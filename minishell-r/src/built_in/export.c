/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:29:15 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/09 16:34:39 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Verifica as condições para exportar uma variável.
 *
 * A string deve começar com uma letra ou um sublinhado, e os caracteres 
 * subsequentes podem ser letras, dígitos ou sublinhados. 
 * A string também não pode conter o caractere '='.
 *
 * @param str A string a ser verificada.
 * @return 1 se a string atende às condições de exportação, 0 caso contrário.
 */
int	check_export_conditions(char *str)
{
	int	i;
//	Verifica se a string começa com uma letra ou um sublinhado
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	i = 0;
//	Verifica se os caracteres subsequentes são letras, dígitos ou sublinhados
	while (str[++i] && str[i] != '=')
	{
		if (!(ft_isalpha(str[i]) || ft_isdigit(str[i] || str[i] == '_')))
			return (0);
	}
	return (1);
}

/**
 * Ordena um array de strings em ordem alfabética.
 *
 * @param array  O array de strings a ser ordenado.
 * @return       O array de strings ordenado em ordem alfabética.
 */
char	**sort_alpha_array(char **array)
{
	char	**new;
	char	*temp;
	int		i;
	int		j;

//	Copia o array de strings
	new = cp_array(array);
	i = -1;
//	Ordena o array de strings - Bubble Sort
	while (new && new[++i] && new[i + 1])
	{
		j = -1;
		while (new && new[++j] && new[j + 1])
		{
			if (ft_strcmp(new[j], new[j + 1]) > 0)
			{
				temp = new[j];
				new[j] = new[j + 1];
				new[j + 1] = temp;
			}
		}
	}
	return (new);
}

/**
 * Imprime as variáveis de ambiente exportadas.
 * 
 * Esta função recebe um array de strings contendo as variáveis de ambiente
 * ordenadas e as imprime no formato "declare -x nome_variavel=valor".
 * 
 * @param sorted_env O array de strings com as variáveis de ambiente ordenadas.
 */
void	print_export(char **sorted_env)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
//	Percorre o array de variáveis de ambiente
	while (sorted_env[i])
	{
//		Obtém o nome da variável de ambiente
		temp = get_env_var_name(sorted_env[i]);
//		Verifica se o nome da variável de ambiente é diferente de "_"
		if (ft_strcmp(temp, "_") != 0)
		{
			printf("declare -x %s", temp);
			j = 0;
			while (temp[j])
				j++;
			if (sorted_env[i][j] == '=')
				printf("=\"%s\"\n", &sorted_env[i][j + 1]);
			else
				printf("\n");
		}
		free(temp);
		i++;
	}
}

/**
 * Função responsável por executar o comando "export" no shell.
 *
 * @param cmd O array de strings contendo os argumentos do comando.
 */
void	execute_export(char	**cmd)
{
	int		i;
	char	**export_array;
	char	*msg;
	char	*msg_aux;

	i = 0;
//PFV	
//	if (!cmd || ft_strcmp(cmd[0], "export") != 0)
//		return ;
//	Se não houver argumentos, imprime todas as variáveis de ambiente
	if (!cmd[1])
	{
//		ordena o array de variáveis de ambiente
		export_array = sort_alpha_array(shell()->env);
//		imprime o array ordenado
		print_export(export_array);
		free_array(&export_array);
	}
	else
	{
//		Se houver argumentos, atualiza as variáveis de ambiente
		while (cmd[++i])
		{
			// Verifica se a string atende às condições de exportação
			if (!check_export_conditions(cmd[i]))
			{
				msg_aux = ft_strjoin("minishell: export: `", cmd[1]);
				msg = ft_strjoin(msg_aux, "': not a valid identifier");
				free(msg_aux);
				display_error(1, msg, true);
				free(msg);
//				shell()->exit_code = 1;
			}
			else
			// Atualiza a variável de ambiente
				update_env(&shell()->env, cmd[i]);
		}
	}
}
