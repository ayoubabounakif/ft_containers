/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 14:25:24 by aabounak          #+#    #+#             */
/*   Updated: 2021/10/14 13:25:43 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/* --------------------------- Base Libraries  ------------------------------ */
# include <iostream>
# include <stdlib.h>
# include <string>
/* ----------------------------- Containers --------------------------------- */
# include <vector>
# include <stack>
# include <deque>
# include <list>
/* ------------------------------ Allocator --------------------------------- */
# include <memory>

# include "iterators.hpp"

namespace ft {
    
    // A very random, random access iterator implementation hh
    template < class T>
    class VectorIterator : public iterator_traits< Iterator<std::random_access_iterator_tag, T> > {
        public:
            VectorIterator() {};
            VectorIterator(const VectorIterator& vI) { *this = vI; };
            VectorIterator& operator= (const VectorIterator& vI);
            ~VectorIterator() {};

        private:
            value_type  _data;
    };

    template < class T, class Alloc = std::allocator<T> >  // Generic template
    class vector {
        public:
            typedef T           value_type;
            typedef Alloc       allocator_type;
            typedef ptrdiff_t   difference_type;
            typedef reference   allocator_type::reference;
            typedef pointer     allocator_type::pointer;
            typedef size_t      size_type;

            /* ---- Constructors & Destructor respectively ---- */
            // Default
            explicit vector (const allocator_type& alloc = allocator_type()) : _arr(nullptr), _alloc(alloc), _size(0), _capacity(0) {}
            
            /* ----------------------- Later ---------------------- */
            explicit vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type()): _alloc(alloc), _size(n), _capacity(n)
            {
                if (n)
                    _arr = _alloc.allocate(n);
                for (size_t i = 0; i < _size; i++)
                    _alloc.construct(&_arr[i], val);
            }
            /* template <class InputIterator> */
            /* vector (InputIterator first, InputIterator last, */
            /*         const allocator_type& alloc = allocator_type()); // Range */
            /* ---------------------------------------------------- */

            vector (const vector& x) { *this = x; }; // Copy
            vector& operator= (const vector& x); // Assignment operator
            ~vector() {
                for (size_t i = 0; i < _size; i++)
                    _alloc.destroy(&_arr[i]);
                _alloc.deallocate(_arr, _capacity);
            };
        
        private:
            T   *           _arr;
            allocator_type  _alloc;
            size_type       _size;
            size_type       _capacity;
    }
    
;}