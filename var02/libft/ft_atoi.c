/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:49:15 by mchoma            #+#    #+#             */
/*   Updated: 2025/05/05 11:49:18 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int s)
{
	return ((s == '\f') + (s == '\n') + (s == '\r')
		+ (s == '\t') + (s == '\v') + (s == ' '));
}

int	ft_atoi(const char *nptr)
{
	size_t		i;
	long int	nbr;
	long int	porn;

	i = 0;
	porn = 1;
	nbr = 0;
	while (ft_isspace(nptr[i]) && nptr[i])
		i ++;
	if (nptr[i] == '+' && nptr[i])
		i ++;
	else if (nptr[i] == '-' && nptr[i])
	{
		porn = -1;
		i ++;
	}
	while (ft_isdigit(nptr[i]) && nptr[i])
	{
		nbr = nbr * 10 + nptr[i] - '0';
		i ++;
	}
	return ((int)(nbr * porn));
}
