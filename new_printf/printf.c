#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

int	print_str(char *str, int len)
{
	int i = 0;
	if (!str)
		str = "(null)";
	while (str[i])
	{
		write(1, &str[i], 1);
		len++;
		i++;
	}
	return (len);
}

int	get_len(int nbr, int len)
{
	if (nbr < 0)
	{
		len++;
		nbr = nbr * -1;
	}
	while (nbr >= 10)
	{
		len++;
		nbr = nbr / 10;
	}
	if (nbr <= 10 && nbr > 0)
		len++;
	return (len);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nbr)
{
	// if (nbr == INT_MIN)
	// 	write(1, "-2147483647", 12);
	if (nbr <= 10 && nbr > 0)
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
	len += get_len(nbr, len);
	ft_putnbr(nbr);
	return (len);
}

void	print_hexa(long int nbr, int *len, int base)
{
	char *base_hexa = "0123456789abcdef";

	if (nbr >= base)
		print_hexa(nbr / base, len, base);
	*len += write(1, &base_hexa[nbr % base], 1);
}

int	ft_printf(const char *str, ...)
{
	int i = 0;
	int	len = 0;
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
				len = print_nbr(va_arg(lst, int), len);
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

int main()
{
	char *str = NULL;
	printf(" voici la len %d\n", ft_printf("salut les gars"));
	printf(" voici la len %d\n", printf("salut les gars"));
	printf(" voici la len %d\n", ft_printf("%s", "je test le s"));
	printf(" voici la len %d\n", printf("%s", "je test le s"));
	printf(" voici la len %d\n", ft_printf("%s affichage apres print", "je test le s"));
	printf(" voici la len %d\n", printf("%s affichage apres print", "je test le s"));
	printf(" voici la len %d\n", ft_printf("%d", 465));
	printf(" voici la len %d\n", printf("%d", 465));
	printf(" voici la len %d\n", ft_printf("%x", 465));
	printf(" voici la len %d\n", printf("%x", 465));
	printf(" voici la len %d\n", ft_printf("%d", 2147483647));
	printf(" voici la len %d\n", printf("%d", 2147483647));
	// printf(" voici la len %d\n", ft_printf("%d", -2147483648));
	// printf(" voici la len %d\n", printf("%d", -2147483648));
	printf(" voici la len %d\n", ft_printf("%d", -2147483647));
	printf(" voici la len %d\n", printf("%d", -2147483647));


	printf("\n\n on passe sur les negatif\n\n");

	printf(" voici la len %d\n", printf("salut les gars"));
	printf(" voici la len %d\n", ft_printf("%s", str));
	printf(" voici la len %d\n", printf("%s", str));
	printf(" voici la len %d\n", ft_printf("%d", -465));
	printf(" voici la len %d\n", printf("%d", -465));
	printf(" voici la len %d\n", ft_printf("%x", -465));
	printf(" voici la len %d\n", printf("%x", -465));
}
