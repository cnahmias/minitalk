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

void	sig_handler(int signum, siginfo_t *info, void *ni)
{
	static char	c = 0;
	static int	i = 0;

	ft_putstr("handling signal\n");
	if (signum == SIGUSR1)
		c += power(i);
	i++;
	if (i == 8)
	{
		write(1, &c, 1);
		if (c == 10)
		{
			sleep(1);
			if (kill(info->si_pid, SIGUSR1) == -1)
			{
				ft_putstr("Error in sending the signal\n");
				exit(0);
			}
			ft_putstr("The message from client ");
			ft_putnbr(info->si_pid);	
			ft_putstr(" has been received and displayed.\n");
			sleep(1);
		}
		c = 0;
		i = 0;
	}
	printf("i = %i\n", i);
}

int	main(void)
{
	struct sigaction sig;
	int	pid;

	pid = getpid();
	ft_putstr("The PID of the server is ");
	ft_putnbr(pid);
	ft_putstr(".\n");
	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = sig_handler;
	if ((sigaction(SIGUSR1, &sig, NULL) != 0) ||
		(sigaction(SIGUSR2, &sig, NULL) != 0))
		return (0);
	while (1)
		pause();
	return (0);
}
