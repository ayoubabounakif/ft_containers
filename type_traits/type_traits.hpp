/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:10:55 by aabounak          #+#    #+#             */
/*   Updated: 2021/10/25 14:20:38 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include <type_traits>

namespace ft {

            /* ----- Miscellaneous transformations ----- */
        /* --       Definition:
            If B is true, enable_if has a public member typedef type, equal to T; otherwise, there is no member typedef.
            This metafunction is a convenient way to leverage SFINAE to conditionally remove functions from overload resolution based on type traits
            and to provide separate function overloads and specializations for different type traits.
            enable_if can be used as an additional function argument (not applicable to operator overloads),
            as a return type (not applicable to constructors and destructors), or as a class template or function template parameter.
            The behavior of a program that adds specializations for enable_if is undefined. */

    template<bool B, class T = void> 
    struct enable_if {};
    template<class T> 
    struct enable_if<true, T> { typedef T type; };
    
            /* --------- Primary type category --------- */
        /* --       Definition:
            Checks whether T is an integral type.
            Provides the member constant value which is equal to true,
            if T is the type bool, char, char8_t (since C++20), char16_t, char32_t, wchar_t, short, int, long, long long,
            or any implementation-defined extended integer types,
            including any signed, unsigned, and cv-qualified variants. Otherwise, value is equal to false. */

    template <class T> struct is_integral { static const bool value = false; };
    template <> struct is_integral<bool> { static const bool value = true; };
    template <> struct is_integral<char> { static const bool value = true; };
    template <> struct is_integral<wchar_t> { static const bool value = true; };
    // template <> struct is_integral<char16_t> { static const bool value = true; };
    // template <> struct is_integral<char32_t> { static const bool value = true; };
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
