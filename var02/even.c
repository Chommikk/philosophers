/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 20:24:39 by mchoma            #+#    #+#             */
/*   Updated: 2025/08/29 21:39:22 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

int		even_start_threads(t_philo *sopher, t_start *start)
{
	int	i;

	i = 0;


}

void	even_immortal(t_philo *sopher, t_start *start)
{
	even_start_threads(sopher, start);

}

void	even_philosophers(t_philo *sopher, t_start *start)
{
	if (sopher->lifetime == -1)
		even_immortal(sopher, start);
	
}

