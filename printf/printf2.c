#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
void	put_string(char *string, int *length)
{
	if (!string)
		string = "(null)";
	while (*string)
		*length += write(1, string++, 1);
}

void	put_digit(long long int number, int base, int *length)
{
	char	*hexadecimal = "0123456789abcdef";

	if (number < 0)
	{
		number *= -1;
		*length += write(1, "-", 1);
	}
	if (number >= base)
		put_digit((number / base), base, length);
	*length += write(1, &hexadecimal[number % base], 1);
}

int	ft_printf(const char *format, ...)
{
	int length = 0;

	va_list	pointer;
	va_start(pointer, format);

	while (*format)
	{
		if ((*format == '%') && ((*(format + 1) == 's') || (*(format + 1) == 'd') || (*(format + 1) == 'x')))
		{
			format++;
			if (*format == 's')
				put_string(va_arg(pointer, char *), &length);
			else if (*format == 'd')
				put_digit((long long int)va_arg(pointer, int), 10, &length);
			else if (*format == 'x')
				put_digit((long long int)va_arg(pointer, unsigned int), 16, &length);
		}
		else
			length += write(1, format, 1);
		format++;
	}
	return (va_end(pointer), length);
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
}
