/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:08:04 by gbodur            #+#    #+#             */
/*   Updated: 2025/08/14 17:14:23 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse_arguments(argc, argv, &data) != 0)
	{
		ft_putendl_fd(ERR_ARGS, 2);
		return (1);
	}
	if (init_data(&data) != 0)
	{
		ft_putendl_fd(ERR_MALLOC, 2);
		return (1);
	}
	if (start_simulation(&data) != 0)
	{
		ft_putendl_fd(ERR_THREAD, 2);
		cleanup_data(&data);
		return (1);
	}
	cleanup_data(&data);
	return (0);
}
