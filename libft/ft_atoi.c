/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:15:13 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/01/17 19:05:15 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		sign = 1 - 2 * (*str == '-');
		str++;
	}
	while (*str >= '0' && *str <= '9')
		result = 10 * result + (*str++ - '0');
	return (result * sign);
}
/*
int main(void)
{
    char  *text;
    int   num;
    int   num_expected;
    
    text = "   \n  +33_42";
    num_expected = atoi(text);
    num = ft_atoi(text);
	printf("\nString is: %s.\n\n", text);
	printf("Expected was: %d;\nMy result is: %d.\n", num_expected, num);
	return (0);
}*/
