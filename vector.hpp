/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 14:25:24 by aabounak          #+#    #+#             */
/*   Updated: 2021/10/16 10:35:41 by aabounak         ###   ########.fr       */
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

# include "iterator.hpp"
# include "iterator_traits.hpp"
# include "random_access_iterator.hpp"

namespace ft {
    template < class T, class Alloc = std::allocator<T> >  // generic template
    class vector {
        public:
            typedef             T                                   value_type;
            typedef             Alloc                               allocator_type;
            typedef typename    allocator_type::reference           reference;
            typedef typename    allocator_type::const_reference     const_reference;
            typedef typename    allocator_type::pointer             pointer;
            typedef typename    allocator_type::const_pointer       const_pointer;
            
            typedef             random_access_iterator<value_type>  iterator; /* const iterator | reverse iterator | Const reverse iterator */
            typedef             random_access_iterator<const value_type>  const_iterator;
            typedef             ptrdiff_t                           difference_type;
            typedef             size_t                              size_type;

            /* ---- Constructors & Destructor respectively ---- */
            // Default
            explicit vector (const allocator_type& alloc = allocator_type()) : _buffer(nullptr), _alloc(alloc), _size(0), _capacity(0) {}
            
            /* ----------------------- Later ---------------------- */
            explicit vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type()): _alloc(alloc), _size(n), _capacity(n)
            {
                if (n)
                    _buffer = _alloc.allocate(n);
                for (size_t i = 0; i < _size; i++)
                    _alloc.construct(&_buffer[i], val);
            }
            /* template <class InputIterator> */
            /* vector (InputIterator first, InputIterator last, */
            /*         const allocator_type& alloc = allocator_type()); // Range */
            /* ---------------------------------------------------- */

            vector (const vector& x) { *this = x; }; // Copy
            vector& operator= (const vector& x) { // Assignment operator
                if ( this != &x ) {
                    this->_buffer = x._buffer;
                    this->_alloc = x._alloc;
                    this->_size = x._size;
                    this->_capacity = x._capacity;
                }
                return (*this);
            }
            ~vector() {
                for (size_t i = 0; i < _size; i++)
                    _alloc.destroy(&_buffer[i]);
                _alloc.deallocate(_buffer, _capacity);
            };

            // iterators
            iterator begin() { return iterator(this->_buffer); };
            const_iterator begin() const { return iterator(this->_buffer); };
            iterator end() { return iterator(this->_buffer + this->_size); };
            const_iterator end() const { return iterator(this->_buffer + this->_size); };
            // reverse iterator

            // capacity
            size_type size() const { return this->_size; };
            // max_size
            // resize
            // capacity
            bool empty() const { return (this->_size == 0 ? true : false); }
            // reserve

            // element access
            reference operator[] (size_type n) { return this->_buffer[n]; };
            const_reference operator[] (size_type n) const { return this->_buffer[n]; };
            reference at(size_type n) { return this->_buffer[n]; };
            const_reference at(size_type n) const { return this->_buffer[n]; };
            reference front() { return this->_buffer[0]; };
            const_reference front() const { return this->_buffer[0]; };
            reference back() { return this->_buffer[this->_size - 1]; };
            const_reference back() const { return this->_buffer[this->_size - 1]; };

            // modifiers
            void pop_back() { _alloc.destroy(&_buffer[this->_size]); this->_size--; };

            // wlahila haram bellah
            void push_back (const value_type& val) {
                static size_type   new_size = 0;
/*                 if (this->_size + 1 >= this->_capacity)
                    _buffer = _alloc.allocate(this->_size * 2); */
                this->_buffer[new_size] = val;
                new_size++;
            };
        
        private:
            T   *           _buffer;
            allocator_type  _alloc;
            size_type       _size;
            size_type       _capacity;
    }
    
;}