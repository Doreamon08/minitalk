/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabbie <rabbie@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 16:08:18 by rabbie            #+#    #+#             */
/*   Updated: 2022/01/10 21:32:58 by rabbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft/libft.h"
#include <signal.h>

int	sender(int pid, char *str)
{
	int	bit;

	bit = 7;
	while (*str)
	{
		while (bit >= 0)
		{
			if ((*str >> bit) & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			bit--;
			usleep(100);
		}
		bit = 7;
		str++;
		usleep(50);
	}
}

int	main(int av, char **ac)
{
	int	pid;

	if (av != 3)
	{
		wtite(1, "Error\n", 6);
		return (1);
	}
	pid = ft_atoi(ac[1]);
	sender (pid, ac[2]);
	return (0);
}
