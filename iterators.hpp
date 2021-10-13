/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:07:58 by aabounak          #+#    #+#             */
/*   Updated: 2021/10/13 11:57:45 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/* --------------------------- Base Libraries  ------------------------------ */
# include <iostream>
# include <stdlib.h>
# include <string>
/* ------------------------------ Allocator --------------------------------- */
# include <memory>
/* ------------------------------- Iterator --------------------------------- */
# include <iterator>

namespace ft {
    template <class Iterator>
    class iterator_traits {
        typedef Iterator::difference_type   diffrence_type;
        typedef Iterator::value_type        value_type;
        typedef Iterator::pointer           pointer;
        typedef Iterator::reference         reference;
        typedef Iterator::iterator_category iterator_category;
    }

    template <class T>
    class iterator_traits<T*> {
        typedef ptrdiff_t                   diffrence_type;
        typedef T                           value_type;
        typedef T*                          pointer;
        typedef T&                          reference;
        typedef random_access_iterator_tag  iterator_category;
    }

    template <class T>
    class iterator_traits<const T*> {
        typedef ptrdiff_t                   diffrence_type;
        typedef T                           value_type;
        typedef const T*                    pointer;
        typedef const T&                    reference;
        typedef random_access_iterator_tag  iterator_category;
    }
}