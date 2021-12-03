/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:18:31 by aabounak          #+#    #+#             */
/*   Updated: 2021/12/03 16:11:04 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <stdlib.h>
# include <string>
# include <vector>
# include <stack>
# include <deque>
# include <list>
# include <memory>
# include <cmath>
# include <stdexcept>
# include <iterator>

# include "../AVL/avl.hpp"
# include "../utility/pair.hpp"
# include "../utility/make_pair.hpp"

namespace ft {
    
    /* --       Definition:
    Maps are associative containers that store elements formed by
    a combination of a key value and a mapped value, following a specific order. */

    template <class Key, class T, class Compare = std::less<Key>,
        class Allocator = std::allocator<ft::pair<const Key, T> >
    > class map {
        public:
        
                    /* ------------ Member Types ----------- */
            typedef             Key                 key_type;
            typedef             T                   mapped_type;
            typedef             ft::pair<const key_type, mapped_type>  value_type;
            typedef             ptrdiff_t           difference_type;
            typedef             size_t              size_type;
            typedef             Compare             key_compare;
            // value_compare -> Nested function class to compare elements :: see value_comp
            typedef             Allocator           allocator_type;
            typedef             const_reference     value_type&;
            typedef typename    allocator_type::reference           reference;
            typedef typename    allocator_type::const_reference     const_reference;
            typedef typename    allocator_type::pointer             pointer;
            typedef typename    allocator_type::const_pointer       const_pointer;

                    /* ----------- Member Functions ---------- */    
                /* ---- Constructors & Destructor respectively ---- */
            /* ------------------------ Default ------------------------ */ 
            map() : __tree()
            
            /* ------------------------ Copy ------------------------ */

            /* ------------------ Assignment Operator --------------- */
            
            /* ---------------------- Detructor --------------------- */
            ~map();

            /* ---------------------- Iterators --------------------- */

            /* ----------------------- Capacity --------------------- */

            /* -------------------- Element access ------------------ */

            /* ---------------------- Modifiers --------------------- */

            /* ---------------------- Allocator --------------------- */
            allocator_type get_allocator() const { return this->_alloc; }
    
        private:
            AVL<value_type, key_compare, allocator_type>    __tree;
            allocator_type  _alloc;
    };
                /* ----------- Non-member function overloads ----------- */
    /* ------------------------ Relational Operators ------------------------ */
            /* ---------------- Equivalent Operators --------------- */
            /* Here are some operators whose work is same.
                (a != b) is equivalent to !(a == b)
                (a > b) equivalent to (b < a)
                (a <= b) equivalent to !(b < a) */
}