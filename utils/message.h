/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:00:43 by mchoma            #+#    #+#             */
/*   Updated: 2025/08/15 17:07:14 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_H
# define MESSAGE_H
#include <sys/time.h>
#include <stdio.h>
#include "../philosophers.h"

void	print_eating(t_philo *data);
void	print_fork(t_philo *data);
void	print_sleeping(t_philo *data);
void	print_thinking(t_philo *data);
void	print_died(t_philo *data);
#endif
