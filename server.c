/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabbie <rabbie@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:42:29 by rabbie            #+#    #+#             */
/*   Updated: 2022/01/10 21:31:21 by rabbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(long num)
{
	if (num < 0)
	{
		ft_putchar('-');
		num = num * -1;
	}
	if (num >= 10)
		ft_putnbr(num / 10);
	ft_putchar((num % 10) + '0');
}

void	writer(int sig, siginfo_t *sa, void *old)
{
	static unsigned char	c;
	static int				i;

	if (sig == SIGUSR1)
		c |= 1;
	if (i == 7)
	{
		i = 0;
		write(1, &c, 1);
		c = 0;
	}
	else
	{
		c = c << 1;
		i++;
	}
}

int	main(int ag, char **ac)
{
	int					pid;
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = writer;
	if (ag != 1)
	{
		printf("Error");
		return (1);
	}
	pid = getpid();
	ft_putnbr(pid);
	ft_putchar('\n');
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
	}
}
