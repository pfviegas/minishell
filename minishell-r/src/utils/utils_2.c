/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:46:27 by pveiga-c          #+#    #+#             */
/*   Updated: 2023/12/09 16:48:35 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Função responsável por exibir um erro no terminal.
 *
 * @param exit_code  O código de erro a ser definido.
 * @param str        A mensagem de erro a ser exibida. Se for NULL,
 *                   a mensagem de erro do sistema será exibida.
 * @param error      Indica se o erro deve ser registrado no shell.
 */
void	display_error(int exit_code, char *str, bool error)
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
 * @return           1 se o caractere estiver presente no conjunto, 0 
 * caso contrário.
 */

//PCC
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
 * Verifica se o caractere `c` marca o fim de uma palavra.
 * Uma palavra é considerada finalizada se o caractere for um espaço em branco,
 * um caractere de redirecionamento (>, <) ou se não estiver dentro de quotes.
 *
 * @param c     O caractere a ser verificado.
 * @param quote Indica se o caractere atual está dentro de uma citação.
 * @return      Retorna 1 se o caractere marca o fim de uma palavra, 
 * caso contrário retorna 0.
 */
int	end_word(char c, char quote)
{
	if ((c == '<' || c == '>' || c == '\t' || c == ' ') && !quote)
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
int	end_var(char c)
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
void	expand_exit(char **new, int *curr_pos)
{
	char	*exit_var;
	int		i;

	(*curr_pos)++;
	exit_var = ft_itoa(shell()->exit_code);
	i = 0;
	while (exit_var[i])
	{
		add_char_string(new, exit_var[i]);
		i++;
	}
	free(exit_var);
}
