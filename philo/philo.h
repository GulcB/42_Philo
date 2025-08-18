/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:01:32 by gbodur            #+#    #+#             */
/*   Updated: 2025/08/17 10:27:56 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

# define TAKING_FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define RESET "\033[0m"

# define ERR_ARGS "Usage: ./philo number_of_philosophers time_to_die \
	time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"
# define ERR_INVALID "Error: Invalid arguments"
# define ERR_MALLOC "Error: Memory allocation failed"
# define ERR_THREAD "Error: Thread creation failed"
# define ERR_MUTEX "Error: Mutex initialization failed"

typedef struct s_philo
{
	int					id;
	int					meals_eaten;
	long				last_meal_time;
	int					left_fork;
	int					right_fork;
	struct s_data		*data;
	pthread_t			thread;
}						t_philo;

typedef struct s_data
{
	int					num_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat_count;
	int					simulation_end;
	long				start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		data_mutex;
	t_philo				*philos;
}						t_data;

int		get_args(int argc, char **argv, t_data *data);
int		ft_atoi(const char *str);
int		is_digit_str(const char *str);

int		init_data(t_data *data);
int		init_philos(t_data *data);
int		init_mutexes(t_data *data);

void	*philosopher_life(void *arg);
int		run_simulation(t_data *data);

void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);

long	get_time(void);
void	ft_usleep(long time_in_ms);
void	print_status(t_philo *philo, char *status);
int		check_death(t_data *data);

int		ft_strlen(char *str);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(long n, int fd);

void	cleanup_data(t_data *data);
void	destroy_mutexes(t_data *data);

#endif