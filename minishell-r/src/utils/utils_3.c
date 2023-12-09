/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:47:53 by pveiga-c          #+#    #+#             */
/*   Updated: 2023/12/09 17:00:38 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Função para expandir uma string substituindo variáveis de ambiente.
 *
 * @param old_str  A string original.
 * @param new_str  O endereço da string expandida.
 * @param start    A posição inicial na string original.
 * @param curr_pos O endereço da posição atual na string original.
 */
void	expander(char *old, char **new, int start, int *curr_pos)
{
	char	*expand;
	char	*temp;
	int		i;
	int		j;

	expand = NULL;
	temp = NULL;
	while (start < *curr_pos)
		add_char_string(&expand, old[start++]);
	i = -1;
	while (shell()->env[++i])
	{
		j = get_var_size(shell()->env[i]);
		temp = ft_substr(shell()->env[i], 0, j);
		if (ft_strcmp(expand, temp) == 0)
		{
			free(temp);
			while (shell()->env[i][++j])
				add_char_string(new, shell()->env[i][j]);
			break ;
		}
		free(temp);
	}
	free(expand);
}

/**
 * Retorna o tamanho da variável em uma string.
 *
 * Esta função recebe uma string contendo uma variável no formato "nome=valor"
 * e retorna o tamanho do nome da variável.
 *
 * @param str A string contendo a variável.
 * @return O tamanho do nome da variável.
 */
int	get_var_size(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

/**
 * Imprime os elementos de uma lista encadeada.
 * Cada elemento da lista é do tipo t_command, que contém informações 
 * sobre comandos e redirecionamentos.
 * Para cada segmento, imprime os argumentos do comando 
 * e os argumentos de redirecionamento.
 *
 * @param lst A lista encadeada a ser impressa.
 */
void	print_lst(t_list *lst)
{
	t_list		*temp;
	t_command	*seg;
	int			i;

	temp = lst;
	while (temp)
	{
		printf("---------------------  tokens  --------------------\n");
		seg = (t_command *)temp->content;
		i = -1;
		while (seg->cmd && seg->cmd[++i])
			printf("cmd_arg[%d] - %s\n", i, seg->cmd[i]);
		i = -1;
		while (seg->red && seg->red[++i])
			printf("red_arg[%d] - %s\n", i, seg->red[i]);
		temp = temp->next;
	}
}

void	rm_str_from_array(char ***array, int index)
{
	char	**new_array;
	int		len;
	int		i;

	if (!(*array))
		return ;
	else
	{
		len = 0;
		while ((*array)[len])
			len++;
		new_array = malloc(sizeof(char *) * len);
		if (!new_array)
			return ;
		i = -1;
		len = 0;
		while ((*array)[++i])
		{
			if (i != index)
				new_array[len++] = ft_strdup((*array)[i]);
		}
		new_array[len] = NULL;
		free_array(array);
		*array = new_array;
	}
}

/**
 * Função que redireciona a saída de erro padrão (stderr) para /dev/null.
 * Qualquer mensagem de erro escrita em stderr será descartada.
 * 
 * @return void
 */
void	stderr_null(void)
{
	int	null_fd;

	null_fd = open("/dev/null", O_WRONLY);
	if (null_fd == -1) 
	{
		perror("Erro ao abrir /dev/null");
		exit(1);
	}
	// Redirecionar stderr para /dev/null
	if (dup2(null_fd, STDERR_FILENO) == -1)
	{
		perror("Erro ao redirecionar stderr");
		exit(1);
	}
	close(null_fd);
}
