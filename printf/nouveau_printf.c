/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nouveau_printf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:47:55 by tpotilli          #+#    #+#             */
/*   Updated: 2024/03/07 15:08:25 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <limits.h>
#include <stdio.h>

int	print_str(char *str, int len)
{
	int	i = 0;
	if (str == NULL)
		str = "(null)";
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
		len++;
	}
	return (len);
}

int	get_len(int tmp, int len)
{
	if (tmp < 0)
	{
		tmp *= -1;
		len++;
	}
	while (tmp > 10)
	{
		tmp = tmp / 10;
		len++;
	}
	if (tmp > 0 && tmp < 10)
		len++;
	return (len);
}

void ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nbr)
{
	if (nbr == INT_MIN)
		write(1, "-2147483648", 12);
	else if (nbr <= 10 && nbr > 0)
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

int	print_nbr(long int nbr, int len)
{
	int		tmp = nbr;
	len = get_len(tmp, len);
	ft_putnbr(nbr);
	return (len);
}

void	print_hexa(long int nbr, int *len, int base)
{
	char *hexa_base = "0123456789abcdef";

	if (nbr >= base)
		print_hexa(nbr / base, len, base);
	*len += write(1, &hexa_base[nbr % base], 1);
}

int	ft_printf(const char *str, ...)
{
	int		len = 0;
	int		i = 0;
	va_list lst;

	va_start(lst, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			if (str[i] == 's')
				len = print_str(va_arg(lst, char *), len);
			else if (str[i] == 'd')
				len = print_nbr(va_arg(lst, long long int), len);
			else if (str[i] == 'x')
				print_hexa(va_arg(lst, unsigned int), &len, 16);
		}
		else
			len += write(1, &str[i], 1);
		i++;
	}
	va_end(lst);
	return (len);
}
//gcc -Wall -Werror -Wextra nouveau_printf.c

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
