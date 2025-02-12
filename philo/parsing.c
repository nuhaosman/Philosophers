/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosman <nosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:51:07 by nosman            #+#    #+#             */
/*   Updated: 2024/07/10 07:12:56 by nosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atoll(const char *str)
{
	long		i;
	long		sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	if ((str[i] == 45) || (str[i] == 43))
	{
		if (str[i] == 45)
			sign *= -1;
		i++;
	}
	while (str[i])
	{
		result = result * 10 + str[i] - '0';
		i++;
		if (result * sign < 0 || result * sign > INT_MAX)
			return (-1);
	}
	return (result * sign);
}

int	check_args(char **arv, int arc)
{
	int	i;
	int	j;

	i = 0;
	while (++i < arc)
	{
		j = 0;
		if ((arv[i][0] == '0') && (arv[i][1] == '\0'))
			return (printf("Args should be bigger than zero\n"), -1);
		if (arv[i][0] == '\0')
			return (printf("Arguments can not be empty string\n"), -1);
		if (arv[i][0] == '+')
			j++;
		while (arv[i][j] != '\0')
		{
			if ((arv[i][j] >= 48) && (arv[i][j] <= 57))
				j++;
			else
				return (printf("Only accept digits\n"), -1);
		}
		if (ft_atoll(arv[i]) == -1)
			return (printf("use arguments less than INT_MAX\n"), -1);
	}
	return (0);
}

int	parse(int arc, char **arv)
{
	if (arc < 5 || arc > 6)
		return (printf ("invalid ammount of arguments\n"), -1);
	if (check_args(arv, arc) == -1)
		return (-1);
	return (0);
}
