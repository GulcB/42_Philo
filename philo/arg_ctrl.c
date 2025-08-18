/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_ctrl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:14:42 by gbodur            #+#    #+#             */
/*   Updated: 2025/08/17 10:51:59 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit_str(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[0] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int		result;
	int		i;

	result = 0;
	i = 0;
	if (!str)
		return (-1);
	if (str[0] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

static int	validate_arguments(t_data *data)
{
	if (data->num_philos <= 0 || data->num_philos > 200)
		return (0);
	if (data->time_to_die <= 0)
		return (0);
	if (data->time_to_eat <= 0)
		return (0);
	if (data->time_to_sleep <= 0)
		return (0);
	if (data->must_eat_count < -1)
		return (0);
	return (1);
}

int	get_args(int argc, char **argv, t_data *data)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (1);
	i = 1;
	while (i < argc)
	{
		if (!is_digit_str(argv[i]))
			return (1);
		i++;
	}
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->must_eat_count = ft_atoi(argv[5]);
		if (data->must_eat_count <= 0)
			return (1);
	}
	else
		data->must_eat_count = -1;
	data->simulation_end = 0;
	return (!validate_arguments(data));
}
