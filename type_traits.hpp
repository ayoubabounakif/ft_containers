/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:10:55 by aabounak          #+#    #+#             */
/*   Updated: 2021/10/19 11:00:30 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <type_traits>

namespace ft {

    template<bool Cond, class T = void> struct enable_if {};
    template<class T> struct enable_if<true, T> { typedef T type; };
    
    template <class T> struct is_integral { static const bool value = false; };
    template <> struct is_integral<bool> { static const bool value = true; };
    template <> struct is_integral<char> { static const bool value = true; };
    template <> struct is_integral<char16_t> { static const bool value = true; };
    template <> struct is_integral<char32_t> { static const bool value = true; };
    template <> struct is_integral<wchar_t> { static const bool value = true; };
    template <> struct is_integral<signed char> { static const bool value = true; };
    template <> struct is_integral<short int> { static const bool value = true; };
    template <> struct is_integral<int> { static const bool value = true; };
    template <> struct is_integral<long int> { static const bool value = true; };
    template <> struct is_integral<long long int> { static const bool value = true; };
    template <> struct is_integral<unsigned char> { static const bool value = true; };
    template <> struct is_integral<unsigned short int> { static const bool value = true; };
    template <> struct is_integral<unsigned int> { static const bool value = true; };
    template <> struct is_integral<unsigned long int> { static const bool value = true; };
    template <> struct is_integral<unsigned long long int> { static const bool value = true; };

}
