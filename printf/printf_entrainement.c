/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_entrainement.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:05:47 by tpotilli          #+#    #+#             */
/*   Updated: 2024/03/05 18:18:34 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <stdarg.h>

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
		write(1, "-2147483648", 12);
	if (nbr > 0 && nbr <= 10)
		ft_putchar(nbr + '0');
	else if (nbr < 0)
	{
		write(1, "-", 1);
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
		nbr *= -1;
		len += write(1, "-", 1);
	}
	if (nbr >= base)
		ft_hexa(nbr / base, len, base);
	*len += write(1, &hexa_base[nbr % base], 1);
}

int ft_printf(const char *str, ...)
{
	int 		i = 0;
	int 		len = 0;
	va_list 	lst;

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

int main()
{
	char *str = NULL;
	ft_printf("salut\n");
	ft_printf("test pour phrase %s\n", "DSAKJ;LSADDKASL;LDAKS");
	ft_printf("test pour int %d\n", 456456);
	ft_printf("test pour hexa %x\n", 456);
	printf("MAINTENANT PRINTF\n");
	printf("salut\n");
	printf("test pour phrase %s\n", "DSAKJ;LSADDKASL;LDAKS");
	printf("test pour int %d\n", 456456);
	printf("test pour hexa %x\n", 456);
	
	printf("\n===\nMAINTENANT VERIF DE LA LEN\n===\n");

	printf("len = %d\n", ft_printf("salut\n"));
	printf("len = %d\n", ft_printf("test pour phrase %s\n", "DSAKJ;LSADDKASL;LDAKS"));
	printf("len = %d\n", ft_printf("test pour int %d\n", 456456));
	printf("len = %d\n", ft_printf("test pour hexa %x\n", 456));
	printf("MAINTENANT PRINTF\n");
	printf("len = %d\n", printf("salut\n"));
	printf("len = %d\n", printf("test pour phrase %s\n", "DSAKJ;LSADDKASL;LDAKS"));
	printf("len = %d\n", printf("test pour int %d\n", 456456));
	printf("len = %d\n", printf("test pour hexa %x\n", 456));

	printf("\ntest d'erreur\n\n");
	printf("len = %d\n", ft_printf("si null = %s\n", str));
	printf("len = %d\n", printf("si null = %s\n", str));
	printf("len = %d\n", ft_printf("si neg = %d\n", -465));
	printf("len = %d\n", printf("si neg = %d\n", -465));
	printf("len = %d\n", ft_printf("si hexa neg = %x\n", -465));
	printf("len = %d\n", printf("si hexa neg = %x\n", -465));
	printf("len = %d\n", ft_printf("pour int_min = %d\n", -2147483649));
	// fonction a reviser:
	/*
	putnbr
	ft_hexa
	ft_printf
	
	*/
}

/*
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
*/