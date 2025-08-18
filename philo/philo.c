/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:08:04 by gbodur            #+#    #+#             */
/*   Updated: 2025/08/17 10:51:59 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (get_args(argc, argv, &data) != 0)
	{
		ft_putendl_fd(ERR_ARGS, 2);
		return (1);
	}
	if (init_data(&data) != 0)
	{
		ft_putendl_fd(ERR_MALLOC, 2);
		return (1);
	}
	if (run_simulation(&data) != 0)
	{
		ft_putendl_fd(ERR_THREAD, 2);
		cleanup_data(&data);
		return (1);
	}
	cleanup_data(&data);
	return (0);
}
