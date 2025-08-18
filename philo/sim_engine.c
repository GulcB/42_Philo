/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_engine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:38:10 by gbodur            #+#    #+#             */
/*   Updated: 2025/08/17 10:51:59 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_meal_completion(t_data *data)
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

static int	simulation_should_end(t_data *data)
{
	int	end;

	pthread_mutex_lock(&data->data_mutex);
	end = data->simulation_end;
	pthread_mutex_unlock(&data->data_mutex);
	return (end);
}

void	*philosopher_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philos == 1)
	{
		print_status(philo, TAKING_FORK);
		ft_usleep(philo->data->time_to_die + 1);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2);
	while (!simulation_should_end(philo->data))
	{
		philo_eat(philo);
		if (simulation_should_end(philo->data))
			break ;
		philo_sleep(philo);
		if (simulation_should_end(philo->data))
			break ;
		philo_think(philo);
	}
	return (NULL);
}

static void	check_simulation(t_data *data)
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

int	run_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				philosopher_life, &data->philos[i]) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		pthread_detach(data->philos[i].thread);
		i++;
	}
	check_simulation(data);
	return (0);
}
