/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_exemple2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:03:19 by tpotilli          #+#    #+#             */
/*   Updated: 2024/03/05 18:03:22 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>

int	ft_putstr(char *str, int len)
{
	int i = 0;
	if (!str)
		str = "(null)";
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
		len++;
	}
	return (len);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_get_nbr(int nbr, int len)
{
	if (nbr < 0)
	{
		nbr = nbr * -1;
		len++;
	}
	while (nbr > 10)
	{
		nbr = nbr / 10;
		len++;
	}
	if (nbr < 10 && nbr > 0)
		len++;
	return (len);
}

void	ft_putnbr(int nbr)
{
	if (nbr == INT_MIN)
		write(1, "-2147483648", 1);
	else if (nbr <= 10 && nbr > 0)
		ft_putchar(nbr + '0');
	else if (nbr < 0)
	{
		ft_putchar('-');
		ft_putnbr(nbr * (-1));
	}
	else
	{
		ft_putnbr(nbr / 10);
		ft_putnbr(nbr % 10);
	}
}

int	ft_putnbr_manager(int nbr, int len)
{
	int		tmp = nbr;
	len = ft_get_nbr(tmp, len);
	ft_putnbr(nbr);
	return (len);
}

void	ft_hexa(long int nbr, int *len, int base)
{
	char *hexa_base = "0123456789abcdef";

	if (nbr < 0)
	{
		len += write(1, "-", 1);
		nbr *= -1;
	}
	if (nbr >= base)
		ft_hexa(nbr / base, len, base);
	*len += write(1, &hexa_base[nbr % base], 1);
}

int	ft_printf(const char *str, ...)
{
	int			len = 0;
	int			i = 0;
	va_list		lst;

	va_start(lst, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			if (str[i] == 's')
				len = ft_putstr(va_arg(lst, char *), len);
			else if (str[i] == 'd')
				len = ft_putnbr_manager(va_arg(lst, long int), len);
			else if (str[i] == 'x')
				ft_hexa(va_arg(lst, unsigned int), &len, 16);
		}
		else
			len += write(1, &str[i], 1);
		i++;
	}
	return (len);
}