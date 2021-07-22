# include <unistd.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/types.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>


int ft_len(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr(char *s)
{
	if (!s)
		return ;
	write(1, s, ft_len(s));
}

void ft_error(int i)
{
	if (i == 1)
		ft_putstr("incorrect pid\n");
	else if (i == 2)
		ft_putstr("incorrect nb of arguments\n");
	exit(0);
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
			ft_error(1);
		else
			tot = (tot * 10) + (str[i] - '0');
		if (tot > 2147483647)
			ft_error(1);
		i++;
	}
	return (tot);
}

void ft_char_to_server(char c, int pid)
{
	int i = 0;

	while (i < 8)
	{
		usleep(10000);
		if (c & 1)
			kill(pid, SIGUSR1);//1
		else
			kill(pid, SIGUSR2);//0
		c >>= 1;
		i++;
	}
}

int	ft_string_to_server(char *str, int pid)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_char_to_server(str[i], pid);
		i++;
	}
	ft_char_to_server('\n', pid);
}

int main (int argc, char **argv)
{
	int pid;

	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		ft_string_to_server(argv[2], pid);
	}
	else
		ft_error(2);
	return (0);
}