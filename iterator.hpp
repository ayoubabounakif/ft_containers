/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:07:58 by aabounak          #+#    #+#             */
/*   Updated: 2021/10/15 14:29:03 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/* --------------------------- Base Libraries  ------------------------------ */
# include <iostream>
# include <stdlib.h>
# include <string>
/* ------------------------------ Allocator --------------------------------- */
# include <memory>
/* ------------------------------- iterator --------------------------------- */
# include <iterator>

namespace ft {
    template <class Category,               // iterator::iterator_category
            class T,                        // iterator::value_type
            class Distance = ptrdiff_t,     // iterator::difference_type
            class Pointer = T*,             // iterator::pointer
            class Reference = T&            // iterator::reference
            > class iterator {
                public:
                    typedef Category    iterator_category;
                    typedef T           value_type;
                    typedef Distance    difference_type;
                    typedef Pointer     pointer;
                    typedef Reference   reference;
            };
;}
