/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosman <nosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 07:31:50 by nosman            #+#    #+#             */
/*   Updated: 2024/07/10 07:13:01 by nosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	int		philo_dead_id;

	if (parse(ac, av) == -1)
		return (-1);
	if (init_struct(&data, av) == -1)
		return (write(2, "Invalid argument\n", 17), 1);
	create_threads(&data);
	if (data.num_of_philo == 1)
		one_philo_case(data.philo);
	else
	{
		philo_dead_id = start_monitoring(&data);
		join_threads(&data);
		if (philo_dead_id)
		{
			pthread_mutex_lock(&data.mutex_print);
			printf("\033[0;31m%lu %d died \033[0m\n", get_time()
				- data.philo->data->start_time, philo_dead_id);
			pthread_mutex_unlock(&data.mutex_print);
		}
	}
	close_up(&data);
	return (0);
}
