/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 20:26:12 by enrgil-p          #+#    #+#             */
/*   Updated: 2024/05/15 13:54:18 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *str, char c, size_t num_words)
{
	size_t	i;
	size_t	c_skip;

	i = 0;
	c_skip = 1;
	while (str[i])
	{
		if (str[i] != c && c_skip == 1)
		{
			num_words++;
			c_skip = 0;
		}
		if (str[i] == c && c_skip == 0)
			c_skip = 1;
		i++;
	}
	return (num_words);
}

static char	**memerror(char **array, size_t n)
{
	while (n <= 0)
		free(array[n--]);
	free(array);
	return (0);
}

static char	**found_words(char **result, char const *str, char c, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	start = i;
	j = 0;
	while (str && j < n)
	{
		if ((str[i] == c || str[i] == '\0') && i != start)
		{
			result[j] = ft_substr(str, start, i - start);
			if (!result[j])
				return (memerror(result, j));
			start = i + 1;
			j++;
		}
		else if (str[i] == c && i == start)
			start++;
		i++;
	}
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	n_ptr;

	if (s)
	{
		n_ptr = 0;
		n_ptr = count_words(s, c, n_ptr);
		array = ft_calloc(n_ptr + 1, sizeof(char *));
		if (!array)
			return (0);
		else if (n_ptr == 0)
			return (array);
		else if (n_ptr > 0)
			array = found_words(array, s, c, n_ptr);
		return (array);
	}
	return (0);
}
/*
int	main(void)
{
	char	**result;
	char	*string;
	char	*searched;
	size_t	i;
	size_t	j;

	string = "Madrid,Barcelona,Valencia,Sevilla,Zaragoza,Málaga,Bilbao,León";
	result = ft_split(string, ',');
	i = 0;
	ft_putendl_fd("If a search at position 5, I will find:", 1);
	ft_putendl_fd(result[5], 1);
	ft_putstr_fd("that's what appears at position 5 of array\n\n", 1);
	while (result[i])
		ft_putendl_fd(result[i++], 1);
	ft_putstr_fd("\n\n", 1);
	i = 0;
	while (result[i])
	{
		if (ft_strncmp(result[i], "Bilbao", ft_strlen(result[i])) == 0)
			printf("Bilbao is at %zu position of the arrary\n\n", i);
		i++;
	}
	i = 0;
	ft_putendl_fd("Now I will search for cities with capital 'M'",1);
	ft_putchar_fd('\0', 1);
	while(result[i])
	{
		if (ft_strchr(result[i], 'M'))
			ft_putendl_fd(result[i], 1);
		i++;
	}
	i = 0;
	j = 0;
	printf("\nTo finish the test, those which doesn't end with '-a'\n");
	while(result[i])
	{
		j = ft_strlen(result[i]) - 1;
		if (!(ft_strrchr(result[i] + j, 'a')))
			ft_putendl_fd(result[i], 1);
		i++;
	}
	free(result);
	return (0);
}*/
