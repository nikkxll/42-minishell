/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:39:11 by dshatilo          #+#    #+#             */
/*   Updated: 2023/11/28 18:02:34 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft.h"
# include <stdarg.h>

int		ft_printf(const char *str, ...);
int		ft_switch(char **s, va_list *args);
int		ft_print_char(va_list *args);
int		ft_putchar(char c);
int		ft_print_str(va_list *args);
int		ft_putstr(char *s);
int		ft_print_ptr(va_list *args);
int		ft_print_x_low(va_list *args);
int		ft_print_x_cap(va_list *args);
int		ft_numlenbase(unsigned long num, int base);
char	*ft_dec_tobase(unsigned long num, char *base);
int		ft_print_dec(va_list *args);
int		ft_print_unsigned_dec(va_list *args);

#endif