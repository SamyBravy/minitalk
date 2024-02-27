/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:47:04 by sdell-er          #+#    #+#             */
/*   Updated: 2024/02/27 15:41:48 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	add_c(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)context;
	g_c++;
	if (kill(info->si_pid, SIGUSR1) == -1)
		exit(EXIT_FAILURE);
}

static void	print_c(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)context;
	g_c--;
	ft_printf("%c", g_c);
	if (kill(info->si_pid, SIGUSR1) == -1)
		exit(EXIT_FAILURE);
	if (g_c == 0)
	{
		usleep(1);
		if (kill(info->si_pid, SIGUSR2) == -1)
			exit(EXIT_FAILURE);
		ft_printf("\n");
	}
	g_c = 0;
}

int	main(void)
{
	struct sigaction	sa1;
	struct sigaction	sa2;

	ft_printf("PID: %d\n", getpid());
	g_c = 0;
	sa1.sa_sigaction = add_c;
	sigemptyset(&sa1.sa_mask);
	sa1.sa_flags = SA_SIGINFO;
	sa2.sa_sigaction = print_c;
	sigemptyset(&sa2.sa_mask);
	sa2.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa1, NULL) == -1)
		exit(EXIT_FAILURE);
	if (sigaction(SIGUSR2, &sa2, NULL) == -1)
		exit(EXIT_FAILURE);
	while (1)
		pause();
	return (0);
}
