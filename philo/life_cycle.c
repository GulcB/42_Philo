/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:37:08 by gbodur            #+#    #+#             */
/*   Updated: 2025/08/18 21:27:55 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	get_forks_ordered(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	if (philo->left_fork < philo->right_fork)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	pthread_mutex_lock(&philo->data->forks[first_fork]);
	print_status(philo, TAKING_FORK);
	pthread_mutex_lock(&philo->data->forks[second_fork]);
	print_status(philo, TAKING_FORK);
}

static void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

void	philo_eat(t_philo *philo)
{
	if (philo->data->num_philos == 1)
	{
		pthread_mutex_lock(&philo->data->forks[0]);
		print_status(philo, TAKING_FORK);
		ft_usleep(philo->data->time_to_die);
		pthread_mutex_unlock(&philo->data->forks[0]);
		return ;
	}
	get_forks_ordered(philo);
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
	long	think_time;

	print_status(philo, THINKING);
	if (philo->data->num_philos % 2 == 0)
		return ;
	think_time = (philo->data->time_to_eat * 2) - philo->data->time_to_sleep;
	if (think_time > 0)
		ft_usleep(think_time / 2);
}
