/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:44:48 by mchoma            #+#    #+#             */
/*   Updated: 2025/04/28 16:44:51 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	tmp;

	if (n == INT_MIN)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		ft_putnbr_fd(-1 * n, fd);
		return ;
	}
	else if (n != 0)
	{
		tmp = (n % 10) + '0';
		if (n / 10 != 0)
			ft_putnbr_fd(n / 10, fd);
		write(fd, &tmp, 1);
	}
	else if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
}
