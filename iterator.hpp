/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:07:58 by aabounak          #+#    #+#             */
/*   Updated: 2021/10/15 18:13:25 by aabounak         ###   ########.fr       */
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
