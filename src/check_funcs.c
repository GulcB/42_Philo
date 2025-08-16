/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:23:02 by gbodur            #+#    #+#             */
/*   Updated: 2025/08/16 20:26:33 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long time_in_ms)
{
	long	start_time;
	long	current_time;

	start_time = get_current_time();
	while (1)
	{
		current_time = get_current_time();
		if ((current_time - start_time) >= time_in_ms)
			break ;
		usleep(50);
	}
}

void	print_status(t_philo *philo, char *status)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->data_mutex);
	if (strcmp(status, DIED) == 0 || !philo->data->simulation_end)
	{
		timestamp = get_current_time() - philo->data->start_time;
		ft_putnbr_fd(timestamp, 1);
		write(1, " ", 1);
		ft_putnbr_fd(philo->id, 1);
		write(1, " ", 1);
		ft_putstr_fd(status, 1);
		write(1, "\n", 1);
	}
	pthread_mutex_unlock(&philo->data->data_mutex);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

static int	handle_death(t_data *data, int philo_index)
{
	pthread_mutex_unlock(&data->data_mutex);
	print_status(&data->philos[philo_index], DIED);
	pthread_mutex_lock(&data->data_mutex);
	data->simulation_end = 1;
	pthread_mutex_unlock(&data->data_mutex);
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
	current_time = get_current_time();
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
