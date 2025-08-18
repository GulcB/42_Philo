/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:23:02 by gbodur            #+#    #+#             */
/*   Updated: 2025/08/17 10:51:59 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long time_in_ms)
{
	long	start_time;
	long	current_time;

	start_time = get_time();
	while (1)
	{
		current_time = get_time();
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
	if (!philo->data->simulation_end)
	{
		timestamp = get_time() - philo->data->start_time;
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
