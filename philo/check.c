/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 21:18:03 by gbodur            #+#    #+#             */
/*   Updated: 2025/08/18 21:18:53 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meal_completion(t_data *data)
{
	int	i;
	int	finished_eating;

	if (data->must_eat_count == -1)
		return (0);
	finished_eating = 0;
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->data_mutex);
		if (data->philos[i].meals_eaten >= data->must_eat_count)
			finished_eating++;
		pthread_mutex_unlock(&data->data_mutex);
		i++;
	}
	if (finished_eating == data->num_philos)
	{
		pthread_mutex_lock(&data->data_mutex);
		data->simulation_end = 1;
		pthread_mutex_unlock(&data->data_mutex);
		return (1);
	}
	return (0);
}

void	check_simulation(t_data *data)
{
	while (!simulation_should_end(data))
	{
		if (check_death(data))
			break ;
		if (check_meal_completion(data))
			break ;
		usleep(1000);
	}
}
