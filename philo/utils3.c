/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:50:37 by mchoma            #+#    #+#             */
/*   Updated: 2025/09/19 14:51:28 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "libft/libft.h"

//numbers are just for string optimatization it sais " is dead\n"
void	print_died(t_philo *data, size_t passed)
{
	size_t				len;
	size_t				offset;
	char				str[100];

	len = llutoa(str, passed, &offset);
	str[offset + len] = ' ';
	len = len + philo_itoa(str + offset + len + 1, data->name);
	*(unsigned long long *)(str + offset + len + 2) = 0xa6465696420;
	pthread_mutex_lock(data->print);
	if (*data->semafor == 1)
		write(1, str + offset, len + 8);
	*data->semafor = 2;
	pthread_mutex_unlock(data->print);
}

int	death_check(t_philo *sopher, t_start *start)
{
	atomic_size_t	i;

	i = get_time_from_start(sopher);
	if ((sopher->ate + start->die) < i)
		return (0);
	return (1);
}
