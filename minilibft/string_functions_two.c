/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_functions_two.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelmy <thelmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 00:38:17 by thelmy            #+#    #+#             */
/*   Updated: 2024/11/01 07:08:43 by thelmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_atoi(char *str)
{
	int				i;
	int				sign;
	unsigned long	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > LONG_MAX / 10
			|| (result == LONG_MAX / 10 && str[i] - '0' != LONG_MAX % 10))
			return (-1 * (sign == 1));
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

char	*t_strjoin(char *s1, char *s2)
{
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (t_strlen(s1) + t_strlen(s2) + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, t_strlen(s1) + 1);
	ft_strlcpy(str + t_strlen(s1), s2, t_strlen(s2) + 1);
	free(s1);
	return (str);
}
