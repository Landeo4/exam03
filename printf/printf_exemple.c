/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_exemple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:39:42 by tpotilli          #+#    #+#             */
/*   Updated: 2024/03/05 17:39:46 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>

int	print(char *str, int len)
{
	int i = 0;
	if (!str)
		str = "(null)";
	while (str[i])
	{
		len += write(1, &str[i], 1);
		i++;
	}
	return (len);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(char *s)
{
	if (s == NULL)
		return (ft_putstr("(null)"));
	write(1, s, ft_strlen(s));
}

int	get_nb(int tmp, int len)
{
	if (tmp < 0)
	{
		tmp = tmp * -1;
		len++;
	}
	while (tmp >= 10)
	{
		len++;
		tmp = tmp / 10;
	}
	if (tmp <= 10 && tmp > 0)
		len++;
	return (len);
}

void	ft_putnbr(int n)
{
	if (n == INT_MIN)
		ft_putstr("-2147483648");
	else if (n >= 0 && n < 10)
		ft_putchar(n + '0');
	else if (n < 0)
	{
		ft_putchar('-');
		ft_putnbr(n * (-1));
	}
	else
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
}

int	print_num(int n, int len)
{
	int tmp = n;
	len = get_nb(tmp, len);
	ft_putnbr(n);
	return (len);
}

void	ft_hexa(long int nbr, int *len, int base)
{
	char *hexa = "0123456789abcdef";
	
	if (nbr < 0)
	{
		len += write(1, "-", 1);
		nbr *= -1;
	}
	if (nbr >= base)
		ft_hexa(nbr / base, len, base);
	*len += write(1, &hexa[nbr % base], 1);
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
				len = print(va_arg(lst, char *), len);
			else if (str[i] == 'd')
				len = print_num(va_arg(lst, long int), len);
			else if (str[i] == 'x')
				ft_hexa(va_arg(lst, unsigned int), &len, 16);
		}
		else
			len += write(1, &str[i], 1);
		i++;
	}
	va_end(lst);
	return (len);
}
