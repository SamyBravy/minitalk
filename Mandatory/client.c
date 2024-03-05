/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:47:12 by sdell-er          #+#    #+#             */
/*   Updated: 2024/03/05 16:52:40 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void	set_received(int signum)
{
	(void)signum;
}

static void	send_c(unsigned char c, int pid)
{
	int	i;
	int	sig;

	i = 0;
	while (i < 8)
	{
		if (c % 2)
			sig = SIGUSR1;
		else
			sig = SIGUSR2;
		if (kill(pid, sig) == -1)
			exit(EXIT_FAILURE);
		c /= 2;
		pause();
		usleep(1);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	s_pid;
	int	i;

	signal(SIGUSR1, set_received);
	signal(SIGUSR2, set_received);
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
	ft_printf("Message received!");
	return (0);
}
