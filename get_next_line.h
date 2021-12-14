/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 21:34:14 by mialbert          #+#    #+#             */
/*   Updated: 2021/12/14 21:18:37 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define BUF_SIZE 5

/**
 * @brief 
 * 
 */
char	*get_next_line(int fd);
int		ft_strlen(const char *str);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strdup(const char *str);
void	*ft_memmove(void *dst, const void *src, size_t n);
char	*ft_strchr(const char *str, int32_t c);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strjoin(char const *str1, char const *str2);
char	*ft_substr(char const *str, uint32_t start, size_t len);

#endif