/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosman <nosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:48:24 by nosman            #+#    #+#             */
/*   Updated: 2024/07/10 07:13:16 by nosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	close_up(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philo)
	{
		if (pthread_mutex_lock(&data->forks[i]) == 0)
			pthread_mutex_unlock(&data->forks[i]);
		else
			pthread_mutex_unlock(&data->forks[i]);
	}
	i = -1;
	while (++i < data->num_of_philo)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->forks_taken);
	free(data->forks);
	free(data->philo);
}

unsigned long int	get_time(void)
{
	static struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	ft_sleep(unsigned long int time, t_philo *philo)
{
	unsigned long	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		if (is_philo_dead(philo->data))
			return (0);
		usleep(100);
	}
	return (1);
}
