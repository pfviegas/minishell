/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:05:44 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/21 14:39:34 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_vars	*init_vars(void)
{
	t_vars	*vars;

	vars = ft_calloc(1, sizeof(t_vars));
	vars->head = NULL;
	vars->str = NULL;
	vars->env = NULL;
	vars->division = NULL;
	return (vars);
}