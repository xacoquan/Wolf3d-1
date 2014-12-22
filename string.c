/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsisic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 04:34:37 by bsisic            #+#    #+#             */
/*   Updated: 2014/12/16 04:46:23 by bsisic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static int		ft_strlen(char *str)
{
	int			i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		++i;
	return (i);
}

int				puterror(char *str)
{
	write(2, "wolf3d: error with ", 19);
	if (str)
		write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (1);
}
