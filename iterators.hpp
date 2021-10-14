/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:07:58 by aabounak          #+#    #+#             */
/*   Updated: 2021/10/14 13:25:08 by aabounak         ###   ########.fr       */
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
    template <class Category,               // iterator::iterator_category
            class T,                        // iterator::value_type
            class Distance = ptrdiff_t,     // iterator::difference_type
            class Pointer = T*,             // iterator::pointer
            class Reference = T&            // iterator::reference
            > class Iterator {
                typedef Category    iterator_category;
                typedef T           value_type;
                typedef Distance    difference_type;
                typedef Pointer     pointer;
                typedef Reference   reference;
            };
    template <class Iterator>
    class iterator_traits {
        typedef Iterator::difference_type   difference_type;
        typedef Iterator::value_type        value_type;
        typedef Iterator::pointer           pointer;
        typedef Iterator::reference         reference;
        typedef Iterator::iterator_category iterator_category;
    };
;}