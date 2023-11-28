/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:48:48 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/28 14:49:28 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Copia um array de strings.
 *
 * Esta função cria uma cópia de um array de strings, 
 * alocando memória para o novo array e duplicando cada elemento de string.
 *
 * @param array O array de strings a ser copiado.
 * @return O array de strings copiado, ou NULL se o array de entrada for NULL 
 *         ou se a alocação de memória falhar.
 */
char	**cp_array(char **array)
{
	char	**new_array;
	int		i;

	if (!array)
		return (NULL);
	i = 0;
	while (array[i])
		i++;
	new_array = malloc(sizeof(char *) * (i + 1));
	if (!new_array)
		return (NULL);
	i = 0;
	while (array[i])
	{
		new_array[i] = ft_strdup(array[i]);
		i++;
	}
	new_array[i] = NULL;
	return (new_array);
}

/**
 * Remove o último caractere de uma string.
 * 
 * @param str A string a ser modificada. 
 *            Este parâmetro é passado por referência.
 */
void	rm_last_char(char **str)
{
	char	*new;
	int		len;
	int		i;

	if (!*str)
		return ;
	len = ft_strlen(*str);
	new = malloc(len);
	i = 0;
	while (i < (len - 1))
	{
		new[i] = (*str)[i];
		i++;
	}
	new[i] = '\0';
	free(*str);
	*str = new;
}

/**
 * Adiciona um caractere ao final de uma string.
 *
 * Esta função recebe um ponteiro para uma string e um caractere `c` 
 * e adiciona o caractere `c` ao final da string.
 * Se a string for nula, a função aloca memória para uma nova string 
 * contendo apenas o caractere `c`.
 * Caso contrário, a função realoca a memória da string original 
 * para adicionar o caractere `c` ao final.
 *
 * @param str Ponteiro para a string a ser modificada.
 * @param c Caractere a ser adicionado.
 */
void	add_char(char **str, char c)
{
	char	*new_str;
	int		i;

	if (!(*str))
	{
		new_str = malloc(2);
		if (!new_str)
			return ;
		new_str[0] = c;
		new_str[1] = '\0';
		*str = new_str;
		return ;
	}
	i = 0;
	while ((*str)[i])
		i++;
	new_str = malloc(i + 2);
	if (!new_str)
		return ;
	i = -1;
	while ((*str)[++i])
		new_str[i] = (*str)[i];
	new_str[i] = c;
	new_str[i + 1] = '\0';
	free(*str);
	*str = new_str;
}

/**
 * Adiciona uma string a um array de strings.
 *
 * Esta função recebe um ponteiro para um array de strings e uma string.
 * Se o array estiver vazio, cria um novo array com a string fornecida.
 * Caso contrário, cria um novo array com tamanho maior que o array original,
 * copia as strings do array original para o novo e adiciona a nova string.
 * Libera a memória do array original e atualiza o ponteiro para o novo.
 *
 * @param array O ponteiro para o array de strings.
 * @param str A string a ser adicionada ao array.
 */
void	add_str_to_array(char ***array, char *str)
{
	char	**new_array;
	int		len;
	int		i;

	if (!(*array))
		*array = create_array(str);
	else
	{
		len = 0;
		while ((*array)[len])
			len++;
		new_array = malloc(sizeof(char *) * (len + 2));
		if (!new_array)
			return ;
		i = -1;
		while ((*array)[++i])
			new_array[i] = ft_strdup((*array)[i]);
		new_array[i] = ft_strdup(str);
		new_array[i + 1] = NULL;
		free_array(array);
		*array = new_array;
	}
}

/**
 * Cria um array de strings a partir de uma string.
 *
 * @param str A string a ser convertida em array.
 * @return O array de strings criado.
 */
char **create_array(char *str)
{
	char **array;
	int i;

	array = malloc(sizeof(char *) * 2);
	if (!array)
		return (NULL);
	i = 0;
	while (str[i])
		i++;
	array[0] = ft_strdup(str);
	if (!array[0])
		return (NULL);
	array[1] = NULL;
	return (array);
}

/**
 * Verifica se o caractere dado é um espaço em branco.
 *
 * @param c O caractere a ser verificado.
 * @return 1 se o caractere for um espaço em branco, 0 caso contrário.
 */
int is_space(char c)
{
	if (c == '\t' || c == ' ')
		return 1;
	return 0;
}

/**
 * Verifica se o caractere é uma aspa (simples ou dupla).
 *
 * @param c O caractere a ser verificado.
 * @return 1 se o caractere for uma aspa, 0 caso contrário.
 */
int is_quote(char c)
{
	if (c == '"' || c == '\'')
		return 1;
	return 0;
}

/**
 * Função responsável por exibir um erro no terminal.
 *
 * @param exit_code  O código de erro a ser definido.
 * @param str        A mensagem de erro a ser exibida. Se for NULL,
 *                   a mensagem de erro do sistema será exibida.
 * @param error      Indica se o erro deve ser registrado no shell.
 */
void display_error(int exit_code, char *str, bool error)
{
	if (str)
		ft_putendl_fd(str, STDERR_FILENO);
	else
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	if (error)
		shell()->error = true;
	shell()->exit_code = exit_code;
}

/**
 * Verifica se um caractere está presente em um conjunto de caracteres.
 *
 * @param c          O caractere a ser verificado.
 * @param search_set O conjunto de caracteres onde será feita a busca.
 * @return           1 se o caractere estiver presente no conjunto, 0 caso contrário.
 */
int	is_in_set(char c, char *search_set)
{
	int	i;

	i = -1;
	while (search_set && search_set[++i])
		if (search_set[i] == c)
			return (1);
	return (0);
}

/**
 * Verifica se o caractere fornecido é um sinal de maior ou menor.
 *
 * @param c O caractere a ser verificado.
 * @return 1 se o caractere for '<' ou '>', caso contrário, retorna 0.
 */
int is_great_less(char c)
{
	if (c == '<' || c == '>')
		return 1;
	return 0;
}

/**
 * Verifica se o caractere `c` marca o fim de uma palavra.
 * Uma palavra é considerada finalizada se o caractere for um espaço em branco,
 * um caractere de redirecionamento (>, <) ou se não estiver dentro de quotes.
 *
 * @param c     O caractere a ser verificado.
 * @param quote Indica se o caractere atual está dentro de uma citação.
 * @return      Retorna 1 se o caractere marca o fim de uma palavra, caso contrário retorna 0.
 */
int	end_word(char c, char quote)
{
	if ((is_great_less(c) || is_space(c)) && !quote)
		return (1);
	return (0);
}

/**
 * Verifica se um caractere é o fim de uma variável.
 *
 * Esta função verifica se um caractere é considerado o fim de uma variável.
 * Um caractere é considerado o fim de uma variável se não for uma letra,
 * um dígito ou o caractere de sublinhado ('_'), ou se for o caractere de
 * interrogação ('?').
 *
 * @param c O caractere a ser verificado.
 * @return  1 se o caractere for o fim de uma variável, 0 caso contrário.
 */
int	end_variable(char c)
{
	if (!(ft_isalpha(c) || ft_isdigit(c) || c == '_') || c == '?')
		return (1);
	return (0);
}

/**
 * Expande o código de saída e adiciona os caracteres correspondentes à string.
 *
 * Esta função recebe um ponteiro para uma string e a posição atual na string.
 * Incrementa a posição atual e converte o código de saída em uma string.
 * Em seguida, itera sobre os caracteres da string do código de saída 
 * adiciona-os à string fornecida.
 *
 * @param new_str O ponteiro para a string a ser expandida.
 * @param curr_pos O ponteiro para a posição atual na string.
 */
void	expand_exit_code(char **new_str, int *curr_pos)
{
	char	*exit_var;
	int		i;

	(*curr_pos)++;
	exit_var = ft_itoa(shell()->exit_code);
	i = -1;
	while (exit_var[++i])
		add_char_string(new_str, exit_var[i]);
	free(exit_var);
}

/**
 * Função para expandir uma string substituindo variáveis de ambiente.
 *
 * @param old_str  A string original.
 * @param new_str  O endereço da string expandida.
 * @param start    A posição inicial na string original.
 * @param curr_pos O endereço da posição atual na string original.
 */
void	expander(char *old_str, char **new_str, int start, int *curr_pos)
{
	char	*expand;
	char	*temp;
	int		i;
	int		j;

	expand = NULL;
	temp = NULL;
	while (start < *curr_pos)
		add_char_string(&expand, old_str[start++]);
	i = -1;
	while (shell()->env[++i])
	{
		j = get_var_size(shell()->env[i]);
		temp = ft_substr(shell()->env[i], 0, j);
		if (ft_strcmp(expand, temp) == 0)
		{
			free(temp);
			while (shell()->env[i][++j])
				add_char_string(new_str, shell()->env[i][j]);
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
int get_var_size(char *str)
{
	int i;

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
void print_lst(t_list *lst)
{
	t_list *temp;
	t_command *seg;
	int i;

	temp = lst;
	while (temp)
	{
		printf("----------------------------  tokens  -----------------------------\n");
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