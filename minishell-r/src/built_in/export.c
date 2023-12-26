/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:29:15 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/26 10:11:15 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Função que exibe uma mensagem de erro informando 
 * que o identificador fornecido não é válido.
 *
 * @param cmd O comando fornecido como argumento.
 */
void	not_valid_identifier(char **cmd)
{
	char	*msg;
	char	*msg_aux;

	msg_aux = ft_strjoin("minishell: `", cmd[1]);
	msg = ft_strjoin(msg_aux, "=': not a valid identifier");
	free(msg_aux);
	display_error(1, msg, true);
	free(msg);
}

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

	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	i = 0;
	while (str[++i] && str[i] != '=')
	{
		if (!(ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_'))
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

	new = cp_array(array);
	i = -1;
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
	while (sorted_env[i])
	{
		temp = get_env_var_name(sorted_env[i]);
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
void	execute_export(char **cmd)
{
	int		i;
	char	**export_array;

	i = 0;
	if (!cmd[1])
	{
		export_array = sort_alpha_array(shell()->env);
		print_export(export_array);
		free_array(&export_array);
	}
	else
	{
		while (cmd[++i])
		{
			if (!check_export_conditions(cmd[i]))
				not_valid_identifier(cmd);
			else
				update_env(&shell()->env, cmd[i]);
		}
	}
}
