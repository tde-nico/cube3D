/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:27:39 by tde-nico          #+#    #+#             */
/*   Updated: 2022/09/12 10:13:39 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_charjoin(char *s1, char s2)
{
	size_t	i;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1)
		return (NULL);
	str = malloc((ft_strlen(s1) + 2) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	str[i++] = s2;
	str[ft_strlen(s1) + 1] = '\0';
	free(s1);
	return (str);
}

char	**ft_arrdup(char **src)
{
	int		i;
	char	**tmp;

	i = 0;
	while (src[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (src[++i])
		tmp[i] = ft_strdup(src[i]);
	tmp[i] = NULL;
	return (tmp);
}

void	ft_strrev(char *str)
{
	char	tmp;
	size_t	i;
	size_t	size;

	i = -1;
	size = ft_strlen(str);
	while (++i < --size)
	{
		tmp = str[size];
		str[size] = str[i];
		str[i] = tmp;
	}
}
