/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:50:38 by tpotilli          #+#    #+#             */
/*   Updated: 2024/03/05 16:24:43 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>      // Include the Standard Input and Output library for basic I/O operations
#include <limits.h>    // Include the Integer Limits library for limits of integer types
#include <stdarg.h>    // Include the Standard Arguments library for handling variable number of arguments
#include <unistd.h>
// Define a function to print a string and update the length of the printed characters
void ft_putstr(char *str, int *len)
{
    long int i = 0;    // Initialize a counter i to 0
    if (!str)          // Check if the given string is NULL
        str = "(null)"; // Assign a default value "(null)" to str if it is NULL
    while (str[i])     // Loop through each character in the string until the null terminator
    {
        *len += write(1, &str[i], 1); // Write the character to standard output and update the length
        i++;                          // Increment the counter
    }
}

// Define a function to print a hexadecimal or decimal number and update the length of the printed characters
void ft_puthexa(long long int nbr, int *len, int base)
{
    char *hexa = "0123456789abcdef"; // Define a string representing hexadecimal digits

    if (nbr < 0)                     // Check if the number is negative
    {
        *len += write(1, "-", 1);    // Write a minus sign and update the length
        nbr = -nbr;                  // Make the number positive
    }
    if (nbr >= base)                 // Check if the number is larger than the base
        ft_puthexa(nbr / base, len, base); // Recursively call ft_puthexa to process the digits
    *len += write(1, &hexa[nbr % base], 1); // Write the corresponding digit and update the length
}

// Define a custom printf function that supports %s, %d, and %x specifiers
int ft_printf(const char *format, ...)
{
    va_list ap;         // Declare a variable of type va_list to store the variable arguments
    int len = 0;        // Initialize the length of printed characters to 0

    va_start(ap, format); // Initialize the va_list variable with the last fixed argument
    while (*format)       // Loop through each character in the format string
    {
        if (*format == '%') // Check if the current character is a format specifier
        {
            format++;       // Move to the next character to determine the specifier type
            if (*format == 's')          // Check if the specifier is for a string
                ft_putstr(va_arg(ap, char *), &len); // Call ft_putstr to print the string argument
            else if (*format == 'd')     // Check if the specifier is for a decimal integer
                ft_puthexa(va_arg(ap, long long int), &len, 10); // Call ft_puthexa to print the integer in decimal
            else if (*format == 'x')     // Check if the specifier is for a hexadecimal integer
                ft_puthexa(va_arg(ap, unsigned int), &len, 16); // Call ft_puthexa to print the integer in hexadecimal
        }
        else                 // If the current character is not a format specifier
            len += write(1, format, 1); // Write the character to standard output and update the length
        format++;            // Move to the next character in the format string
    }
    va_end(ap);              // Clean up the va_list variable
    return len;              // Return the total length of printed characters
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
