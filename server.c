/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabbie <rabbie@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:42:29 by rabbie            #+#    #+#             */
/*   Updated: 2022/01/10 20:29:50 by rabbie           ###   ########.fr       */
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

// int	sender(char	*str)
// {
// 	int	bit;

// 	bit = 7;
// 	while (*str)
// 	{
// 		while (bit >= 0)
// 		{
// 			if ((*str >> bit) & 1)
// 				writer(1);
// 			else
// 				writer(0);
// 			bit--;
// 		}
// 		bit = 7;
// 		str++;
// 	}
// }

int	main(int ag, char **ac)
{
	int					pid;
	struct sigaction	sa;

	pid = (int)(getpid());
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = writer;
	if (ag != 1)
	{
		printf("Error");
		return (1);
	}
	pid = getpid();
	printf("%d\n", pid);
	while(1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
	}
	// writer(0);//0
	// writer(1);//1
	// writer(0);//2
	// writer(0);//3
	// writer(0);//4
	// writer(0);//5
	// writer(0);//6
	// writer(1);//7
	// ft_putnbr(pid);
	// ft_putchar('\n');
	// char c = 'L';
	// char n = 0b0;
	// int i = 7;
	// while(i >= 0)
	// {
	// 	printf("%c\n", n);
	// 	if((c >> i) & 1)
	// 		n = n | 1; 
	// 	if (i != 0)
	// 		n = n << 1;
	// 	i--;
	// }
	// printf("---%c---\n", n);
}
