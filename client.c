/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnahmias <cnahmias@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 16:58:52 by clbouche          #+#    #+#             */
/*   Updated: 2021/07/08 10:06:07 by clbouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

int	ft_atoi(const char *str)
{
	int		i;
	long	tot;

	i = 0;
	tot = 0;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
		{
			ft_putstr("The pid is incorrect - enter an int\n");
			exit(0);
		}
		else
			tot = (tot * 10) + (str[i] - '0');
		if (tot > 2147483647)
		{
			ft_putstr("The pid is incorrect - enter an int\n");
			exit(0);
		}
		i++;
	}
	return (tot);
}

void	ft_char_to_server(char c, int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		usleep(10);
		if (c & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		c >>= 1;
		i++;
		usleep(10);
	}
}

void	ft_string_to_server(char *str, int pid)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_char_to_server(str[i], pid);
		i++;
	}
	ft_char_to_server('\n', pid);
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		ft_string_to_server(argv[2], pid);
	}
	else
	{
		ft_putstr("incorrect nb of parameters\n");
		exit(0);
	}
}
