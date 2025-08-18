/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:37:08 by gbodur            #+#    #+#             */
/*   Updated: 2025/08/17 10:51:59 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_forks(t_philo *philo)
{
	if (philo->data->num_philos == 1)
	{
		pthread_mutex_lock(&philo->data->forks[0]);
		print_status(philo, TAKING_FORK);
		ft_usleep(philo->data->time_to_die + 1);
		pthread_mutex_unlock(&philo->data->forks[0]);
		return (1);
	}
	if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	}
	print_status(philo, TAKING_FORK);
	print_status(philo, TAKING_FORK);
	return (0);
}

static void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

void	philo_eat(t_philo *philo)
{
	if (get_forks(philo) != 0)
		return ;
	pthread_mutex_lock(&philo->data->data_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->data_mutex);
	print_status(philo, EATING);
	ft_usleep(philo->data->time_to_eat);
	drop_forks(philo);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, SLEEPING);
	ft_usleep(philo->data->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print_status(philo, THINKING);
}
