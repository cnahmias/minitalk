/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnahmias <cnahmias@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 16:58:52 by clbouche          #+#    #+#             */
/*   Updated: 2021/07/08 10:06:07 by clbouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	power(int i)
{
	int	n;

	n = 1;
	while (i > 0)
	{
		n *= 2;
		i--;
	}
	return (n);
}

void	ft_putnbr(int nb)
{
	char			c;

	if (nb < 10)
	{
		c = nb + '0';
		write(1, &c, 1);
	}
	else
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
		i++;
	write(1, s, i);
}

void	sig_handler(int signum)
{
	static char	c = 0;
	static int	i = 0;

	if (signum == SIGUSR1)
		c += power(i);
	i++;
	if (i == 8)
	{
		write(1, &c, 1);
		if (c == '\n')
			ft_putstr("Signal received and displayed.\n");
		i = 0;
		c = 0;
	}
}

int	main(void)
{
	int	pid;

	pid = getpid();
	ft_putstr("The PID is ");
	ft_putnbr(pid);
	ft_putstr(".\n");
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	while (1)
	{
	}
	return (0);
}
