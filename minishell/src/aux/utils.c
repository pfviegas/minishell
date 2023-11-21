/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:43:55 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/21 11:33:08 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isspace(int c)
{
	return ((c == ' '));
}


// redirecciona o STDERROR para /dev/NULL para nao escrever o 
// comando exit no terminal apos a mensagem de erro.
// falta testar se sai do MiniShell ou nao (nao pode sair)
// PFV
void	stderr_null(void)
{
	int null_fd = open("/dev/null", O_WRONLY);

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

void	sort_array(char **arr, int size)
{
	int		i;
	int		changed;
	char	*temp;

	changed = 1;
	while (changed)
	{
		changed = 0;
		i = 0;
		while (i < size - 1)
		{
			if (str_cmp(arr[i], arr[i + 1]) > 0)
			{
				temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
				changed = 1;
			}
		i++;
		}
		size--;
	}
}
// Compara a string1 com a string2
int	str_cmp(char *s1, char *s2)
{
	unsigned int	i;

	if (s1 && s2)
	{
		i = 0;
		while (s1[i] == s2[i] && (s1[i] != '\0' && s2[i] != '\0'))
			i++;
		return (s1[i] - s2[i]);
	}
	return (1);
}

// Calcula o size de uma variavel do tipo char**
int	strlen_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] && array[i][0] != 3)
		i++;
	return (i);
}

// Compara dois elementos ate um deles acabar
int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	if (s1 && s2)
	{
		i = 0;
		while (s1[i] == s2[i] && (s1[i] != '\0' && s2[i] != '\0'))
			i++;
		return (s1[i] - s2[i]);
	}
	return (1);
}

// Verifica se a string so tem elementos alfabumericos
int	str_is_alphanum(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9') || 
			!(str[i] >= 'a' && str[i] <= 'z') || 
			!(str[i] >= 'A' && str[i] <= 'Z'))
			return (0);
		i++;
	}
	return (1);
}

// Fecha os file descriptors
void	close_fds(t_commands **command, int flag)
{
	t_commands	*temp;

	temp = (*command);
	if (flag)
		lst_first(command);
	while ((*command))
	{
		close((*command)->fd[0]);
		close((*command)->fd[1]);
		if ((*command)->fd_master[1] > 2)
			close((*command)->fd_master[1]);
		if ((*command)->fd_master[0] > 2)
			close((*command)->fd_master[0]);
		if (!flag)
			break ;
		(*command) = (*command)->next;
	}
	(*command) = temp;
}

int	check_fds(t_commands *command)
{
	int	res;

	res = 0;
	while (command)
	{
		if (command->fd_master[0] == -1 || command->fd_master[1] == -1 \
			|| command->fd_master_error[0] || command->fd_master_error[1])
			res++;
		command = command->next;
	}
	return (res);
}