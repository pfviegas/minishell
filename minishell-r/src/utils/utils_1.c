/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:48:48 by pveiga-c          #+#    #+#             */
/*   Updated: 2023/12/21 11:15:34 by pviegas          ###   ########.fr       */
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
	new_str = malloc(ft_strlen(*str) + 2);
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
char	**create_array(char *str)
{
	char	**array;
	int		i;

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
