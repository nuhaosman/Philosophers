/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosman <nosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:50:34 by nosman            #+#    #+#             */
/*   Updated: 2024/07/10 07:13:06 by nosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_fork_available(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork_mutex);
	if (*philo->left_fork_pointer && *philo->left_fork_pointer != philo->id)
		pthread_mutex_unlock(philo->left_fork_mutex);
	else
	{
		pthread_mutex_unlock(philo->left_fork_mutex);
		return (0);
	}
	pthread_mutex_lock(philo->right_fork_mutex);
	if (*philo->right_fork_pointer && *philo->right_fork_pointer != philo->id)
	{
		*philo->right_fork_pointer = philo->id;
		pthread_mutex_unlock(philo->right_fork_mutex);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork_mutex);
		return (0);
	}
	return (1);
}

int	philo_takes_forks(t_philo *philo)
{
	if (is_fork_available(philo))
	{
		pthread_mutex_lock(philo->left_fork_mutex);
		*philo->left_fork_pointer = 0;
		pthread_mutex_unlock(philo->left_fork_mutex);
		pthread_mutex_lock(philo->right_fork_mutex);
		*philo->right_fork_pointer = 0;
		pthread_mutex_unlock(philo->right_fork_mutex);
	}
	else
		return (1);
	print_message("\033[1;90mhas taken a fork\033[0m", philo);
	print_message("\033[1;90mhas taken a fork\033[0m", philo);
	return (0);
}

int	philo_is_eating(t_philo *philo)
{
	print_message("\033[1;35m\033[0m\033[1;35mis eating\033[0m", philo);
	pthread_mutex_lock(&philo->data->mutex_dead);
	philo->time_to_die = (get_time() - philo->data->start_time)
		+ philo->data->time_to_die;
	pthread_mutex_unlock(&philo->data->mutex_dead);
	if (is_philo_dead(philo->data))
		return (drop_forks(philo), 0);
	if (!ft_sleep(philo->data->time_to_eat, philo))
		return (drop_forks(philo), 0);
	pthread_mutex_lock(&philo->data->mutex_meals);
	if (philo->data->meals_counter != -1)
		philo->data->meals_counter++;
	pthread_mutex_unlock(&philo->data->mutex_meals);
	drop_forks(philo);
	return (1);
}

int	philo_is_sleeping(t_philo *philo)
{
	if (!is_philo_dead(philo->data))
	{
		print_message("\033[1;34mis sleeping\033[0m", philo);
		if (!ft_sleep(philo->data->time_to_sleep, philo))
			return (0);
		return (1);
	}
	else
		return (0);
}

int	philo_is_thinking(t_philo *philo)
{
	if (!is_philo_dead(philo->data))
	{
		print_message("\033[1;96mis thinking\033[0m", philo);
		return (1);
	}
	else
		return (0);
}
