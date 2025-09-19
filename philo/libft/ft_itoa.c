/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:17:43 by mchoma            #+#    #+#             */
/*   Updated: 2025/04/27 17:17:48 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_itoa(int n)
{
	int		counter;
	char	*str;
	long	number;

	counter = 0 +(n <= 0);
	number = (long) n;
	while (n != 0 && counter ++ > -10)
		n = n / 10;
	str = malloc((counter + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '-' * (number < 0) + '0' * (number == 0);
	str[counter] = 0;
	number = number - 2 * number * (number < 0);
	while (number != 0)
	{
		str[--counter] = (int)(number % 10) + '0';
		number = number / 10;
	}
	return (str);
}
