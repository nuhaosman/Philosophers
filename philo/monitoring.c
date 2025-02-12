/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosman <nosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 07:32:09 by nosman            #+#    #+#             */
/*   Updated: 2024/07/10 07:12:50 by nosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_dead);
	if (get_time() - philo->data->start_time >= philo->time_to_die)
	{
		philo->data->philo_dead = 1;
		pthread_mutex_unlock(&philo->data->mutex_dead);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->mutex_dead);
		return (1);
	}
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork_mutex);
	*philo->left_fork_pointer = philo->id;
	pthread_mutex_unlock(philo->left_fork_mutex);
	pthread_mutex_lock(philo->right_fork_mutex);
	if (philo->id == philo->num_of_philo)
		*philo->right_fork_pointer = philo->id;
	else
		*philo->right_fork_pointer = philo->id;
	pthread_mutex_unlock(philo->right_fork_mutex);
}

void	is_max_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_meals);
	if (philo->data->num_of_meals != -1
		&& philo->data->meals_counter >= (philo->data->num_of_philo
			* philo->data->num_of_meals))
	{
		pthread_mutex_lock(&philo->data->mutex_dead);
		philo->data->philo_dead = 1;
		pthread_mutex_unlock(&philo->data->mutex_dead);
	}
	pthread_mutex_unlock(&philo->data->mutex_meals);
}

int	check_if_one_is_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (check_last_meal(&data->philo[i]) == 0)
			return (i + 1);
		i++;
	}
	return (0);
}

int	start_monitoring(void *arg)
{
	t_data	*data;
	int		dead_philo;

	data = (t_data *)arg;
	while (1)
	{
		if (is_philo_dead(data))
			return (0);
		dead_philo = check_if_one_is_dead(data);
		if (dead_philo)
			return (dead_philo);
		usleep(200);
	}
}
