/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:55:32 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/07 16:55:56 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_cd_error(char *path)
{
	char	*msg_aux;
	char	*msg;

	msg_aux = ft_strjoin("minishell: cd: ", path);
	msg = ft_strjoin(msg_aux, ": No such file or directory");
	free(msg_aux);
	display_error(1, msg, true);
	free(msg);
}
