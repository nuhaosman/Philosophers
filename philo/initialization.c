/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosman <nosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:53:22 by nosman            #+#    #+#             */
/*   Updated: 2024/07/10 07:12:45 by nosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->num_of_philo)
	{
		pthread_create(&data->philo[i].thread_id,
			NULL, &philo_routine, (void *)&data->philo[i]);
		i++;
	}
}

void	join_threads(t_data *data)
{
	int	j;

	j = -1;
	while (++j < data->num_of_philo)
	{
		if (pthread_join(data->philo[j].thread_id, 0) != 0)
		{
			printf("Error: pthread_join error\n");
			return ;
		}
	}
}

int	initialize_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].left_fork_pointer = &data->forks_taken[i];
		data->philo[i].left_fork_mutex = &data->forks[i];
		if (data->philo[i].id == data->num_of_philo)
		{
			data->philo[i].right_fork_pointer = &data->forks_taken[0];
			data->philo[i].right_fork_mutex = &data->forks[0];
		}
		else
		{
			data->philo[i].right_fork_pointer = &data->forks_taken[i + 1];
			data->philo[i].right_fork_mutex = &data->forks[i + 1];
		}
		data->philo[i].time_to_die = data->time_to_die;
		data->philo[i].time_to_eat = data->time_to_eat;
		data->philo[i].time_to_sleep = data->time_to_sleep;
		data->philo[i].data = data;
	}
	return (0);
}

int	create_mutex(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	if (!data->forks)
		return (-1);
	data->forks_taken = malloc(sizeof(int) * data->num_of_philo);
	if (!data->forks_taken)
		return (-1);
	data->philo = malloc(sizeof(t_philo) * data->num_of_philo);
	if (!data->philo)
		return (-1);
	while (++i < data->num_of_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	while (++j < data->num_of_philo)
		data->forks_taken[j] = -1;
	pthread_mutex_init(&data->mutex_dead, NULL);
	pthread_mutex_init(&data->mutex_meals, NULL);
	pthread_mutex_init(&data->mutex_print, NULL);
	return (0);
}

int	init_struct(t_data *data, char **av)
{
	data->num_of_philo = ft_atoll(av[1]);
	if (data->num_of_philo <= 0)
		return (-1);
	data->time_to_die = ft_atoll(av[2]);
	data->time_to_eat = ft_atoll(av[3]);
	data->time_to_sleep = ft_atoll(av[4]);
	if (av[5])
	{
		data->num_of_meals = ft_atoll(av[5]);
		if (data->num_of_meals <= 0)
			return (-1);
	}
	else
		data->num_of_meals = -1;
	data->philo_dead = 0;
	data->start_time = 0;
	data->meals_counter = 0;
	if (create_mutex(data) == -1 || initialize_philos(data))
		return (-1);
	return (0);
}
