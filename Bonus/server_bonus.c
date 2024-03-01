/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:42:30 by sdell-er          #+#    #+#             */
/*   Updated: 2024/03/01 16:09:28 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_bonus.h"

static int	ft_pow(int n, int exp)
{
	int	res;

	res = 1;
	while (exp)
	{
		res *= n;
		exp--;
	}
	return (res);
}

static void	print_c(int pid, unsigned char c)
{
	ft_printf("%c", c);
	if (c == 0)
	{
		if (kill(pid, SIGUSR2) == -1)
			exit(EXIT_FAILURE);
		ft_printf("\n");
	}
	else
	{		
		if (kill(pid, SIGUSR1) == -1)
			exit(EXIT_FAILURE);
	}
}

static void	add(int signum, siginfo_t *info, void *context)
{
	static int				e = 0;
	static unsigned char	c = 0;

	(void)context;
	if (signum == SIGUSR1)
		c += ft_pow(2, e);
	e++;
	usleep(1);
	if (kill(info->si_pid, SIGUSR1) == -1)
		exit(EXIT_FAILURE);
	if (e == 8)
	{
		print_c(info->si_pid, c);
		c = 0;
		e = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("PID: %d\n", getpid());
	sa.sa_sigaction = add;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		exit(EXIT_FAILURE);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		exit(EXIT_FAILURE);
	while (1)
		pause();
	return (0);
}
