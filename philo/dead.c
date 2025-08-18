/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 21:20:22 by gbodur            #+#    #+#             */
/*   Updated: 2025/08/17 10:51:59 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_death(t_philo *philo)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	timestamp = get_time() - philo->data->start_time;
	ft_putnbr_fd(timestamp, 1);
	write(1, " ", 1);
	ft_putnbr_fd(philo->id, 1);
	write(1, " ", 1);
	ft_putstr_fd(DIED, 1);
	write(1, "\n", 1);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

static int	handle_death(t_data *data, int philo_index)
{
	data->simulation_end = 1;
	pthread_mutex_unlock(&data->data_mutex);
	print_death(&data->philos[philo_index]);
	return (1);
}

int	check_death(t_data *data)
{
	int		i;
	long	current_time;

	pthread_mutex_lock(&data->data_mutex);
	if (data->simulation_end)
	{
		pthread_mutex_unlock(&data->data_mutex);
		return (1);
	}
	current_time = get_time();
	i = 0;
	while (i < data->num_philos)
	{
		if ((current_time - data->philos[i].last_meal_time) > data->time_to_die)
			return (handle_death(data, i));
		i++;
	}
	pthread_mutex_unlock(&data->data_mutex);
	return (0);
}
