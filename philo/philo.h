/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosman <nosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 07:32:33 by nosman            #+#    #+#             */
/*   Updated: 2024/07/10 07:12:19 by nosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_philo
{
	int						id;
	pthread_mutex_t			*left_fork_mutex;
	pthread_mutex_t			*right_fork_mutex;
	int						*right_fork_pointer;
	int						*left_fork_pointer;
	int						num_of_philo;
	unsigned long int		time_to_die;
	unsigned long int		time_to_eat;
	unsigned long int		time_to_sleep;
	pthread_t				thread_id;
	struct s_data			*data;
}				t_philo;

typedef struct s_data
{
	int						num_of_philo;
	unsigned long int		time_to_die;
	unsigned long int		time_to_eat;
	unsigned long int		time_to_sleep;
	int						num_of_meals;
	int						meals_counter;
	int						philo_dead;
	unsigned long int		start_time;
	int						*forks_taken;
	pthread_mutex_t			*forks;
	pthread_mutex_t			mutex_dead;
	pthread_mutex_t			mutex_print;
	pthread_mutex_t			mutex_meals;
	t_philo					*philo;
}				t_data;

//---   initialization.c   ---
void				create_threads(t_data *data);
void				join_threads(t_data *data);
int					initialize_philos(t_data *data);
int					create_mutex(t_data *data);
int					init_struct(t_data *data, char **av);

//---   monitoring.c   ---
int					check_last_meal(t_philo *philo);
void				drop_forks(t_philo *philo);
void				is_max_eat(t_philo *philo);
int					check_if_one_is_dead(t_data *data);
int					start_monitoring(void *arg);

//---   parsing.c   ---
long long			ft_atoll(const char *str);
int					check_args(char **arv, int arc);
int					parse(int arc, char **arv);

//---   processes.c   ---
int					is_fork_available(t_philo *philo);
int					philo_takes_forks(t_philo *philo);
int					philo_is_eating(t_philo *philo);
int					philo_is_sleeping(t_philo *philo);
int					philo_is_thinking(t_philo *philo);

//---   routine.c   ---
int					is_philo_dead(t_data *data);
void				one_philo_case(t_philo *philo);
void				print_message(char *str, t_philo *philo);
int					take_fork_eat(t_philo *philo);
void				*philo_routine(void *arguments);

//---   utils.c   ---
void				close_up(t_data *data);
unsigned long int	get_time(void);
int					ft_sleep(unsigned long int time, t_philo *philo);

#endif
