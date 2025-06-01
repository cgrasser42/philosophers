/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:51:20 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/01 18:44:30 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	check_input(int ac, char *av[])
{
	int	i;

	if (ac != 5 && ac != 6)
	{
		printf("%s\n", USAGE);
		printf("%119s\n", USAGE_BONUS);
		return (false);
	}
	i = 0;
	while (av[i])
	{
		if (!str_is_numeric(av[i++]))
		{
			printf("Error: invalid argument — digits only expected \n");
			return (false);
		}
	}
	return (true);
}

int	main(int ac, char *av[])
{
	t_data	*data;

	if (!check_input(ac, ++av))
		return (1);
	data = data_new(av);
	if (!data)
		return (printf("Error\n"));
	philos_destroy(data->_philos);
	forks_destroy(data);
	free(data);
	return (0);
}
