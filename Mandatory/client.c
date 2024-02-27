/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:47:12 by sdell-er          #+#    #+#             */
/*   Updated: 2024/02/27 17:02:56 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void	set_received(int signum)
{
	(void)signum;
	g_received = 1;
}

static void	send_c(unsigned char c, int pid)
{
	while (1)
	{
		g_received = 0;
		if (kill(pid, SIGUSR1) == -1)
			exit(EXIT_FAILURE);
		signal(SIGUSR1, set_received);
		while (!g_received)
			pause();
		if (c == 0)
			break ;
		c--;
	}
	if (kill(pid, SIGUSR2) == -1)
		exit(EXIT_FAILURE);
	signal(SIGUSR1, set_received);
	while (!g_received)
		pause();
	usleep(1);
}

int	main(int argc, char **argv)
{
	int	s_pid;
	int	i;

	if (argc != 3)
	{
		ft_printf("Error\nValid parameters: <server_pid> <string_to_send>");
		exit(EXIT_FAILURE);
	}
	s_pid = ft_atoi(argv[1]);
	if (s_pid <= 0)
	{
		ft_printf("Error: invalid PID");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (argv[2][i])
		send_c(argv[2][i++], s_pid);
	send_c(argv[2][i], s_pid);
	g_received = 0;
	signal(SIGUSR2, set_received);
	while (!g_received)
		pause();
	ft_printf("Message received!");
	return (0);
}
