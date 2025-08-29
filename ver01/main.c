/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 18:49:04 by mchoma            #+#    #+#             */
/*   Updated: 2025/08/15 19:14:52 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"
#include "libft/libft.h"

void	test_initialize(t_start *arg);
void	initialize(t_start *arg, int argc, char **argv)
{
	arg->philosophers = ft_atoi(argv[1]);
	arg->die = ft_atoi(argv[2]);
	arg->eat = ft_atoi(argv[3]);
	arg->sleep = ft_atoi(argv[4]);
	if (argc == 6)
		arg->lifetime = ft_atoi(argv[5]);
	else 
		arg->lifetime = 0;
}

int	main(int argc, char **argv)
{
	t_start	arguments;

	if (argc != 5 && argc != 6)
		return (1); //error message
	initialize(&arguments, argc, argv);
	
	//test_initialize(&arguments);
	
	if (arguments.philosophers % 2 == 0)
		even_philosophers(&arguments);
}


void	test_initialize(t_start *arg)
{
	printf("philosophers == %lu\n", arg->philosophers);
	printf("die == %lu\n", arg->die);
	printf("eat == %lu\n", arg->eat);
	printf("sleep == %lu\n", arg->sleep);
	printf("lifetime == %lu\n", arg->lifetime);
}
