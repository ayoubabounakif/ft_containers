/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:07:58 by aabounak          #+#    #+#             */
/*   Updated: 2021/10/27 12:58:43 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include <iostream>
# include <stdlib.h>
# include <string>
# include <memory>
# include <iterator>

/* //! if Linux
#define ptrdiff_t __gnu_cxx::ptrdiff_t */

namespace ft {

    /* --       Definition:
        iterator is the base class provided to simplify definitions of the required types for iterators. */

    template <class Category, class T, class Distance = ptrdiff_t,
        class Pointer = T*, class Reference = T&>
    struct iterator {
        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef Category  iterator_category;
    };
;}
