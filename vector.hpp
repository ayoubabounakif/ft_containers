/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 14:25:24 by aabounak          #+#    #+#             */
/*   Updated: 2021/10/18 12:25:15 by aabounak         ###   ########.fr       */
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
/* -------------------------------- Math ------------------------------------ */
# include <cmath>

# include "iterator.hpp"
# include "iterator_traits.hpp"
# include "random_access_iterator.hpp"

namespace ft {
    template < class T, class Alloc = std::allocator<T> >  // generic template
    class vector {
        public:
                    /* ------------ Member Types ----------- */
            typedef             T                                   value_type;
            typedef             Alloc                               allocator_type;
            typedef typename    allocator_type::reference           reference;
            typedef typename    allocator_type::const_reference     const_reference;
            typedef typename    allocator_type::pointer             pointer;
            typedef typename    allocator_type::const_pointer       const_pointer;
            typedef             random_access_iterator<value_type>          iterator;
            typedef             random_access_iterator<const value_type>    const_iterator;
            typedef             ptrdiff_t                           difference_type;
            typedef             size_t                              size_type;

                    /* ----------- Member Functions ---------- */    
                /* ---- Constructors & Destructor respectively ---- */
            /* ------------------------ Default ------------------------ */
            explicit vector (const allocator_type& alloc = allocator_type()) :
                _buffer(nullptr),
                _alloc(alloc),
                _size(0),
                _max_size(alloc.max_size()),
                _capacity(0) {}        
    
            /* ------------------------ Fill ------------------------ */
            explicit vector (size_type n, const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type()) :
                _alloc(alloc),
                _size(n),
                _max_size(alloc.max_size()),
                _capacity(n) {
                    _buffer = _alloc.allocate(_capacity);
                    for (size_t i = 0; i < n; i++)
                        _buffer[i] = val;
                }
            /* ------------------------ Range ----------------------- */
            /* template <class InputIterator> */
            /* vector (InputIterator first, InputIterator last, */
            /*         const allocator_type& alloc = allocator_type()); */
            
            /* ------------------------ Copy ------------------------ */
            vector (const vector& x) { *this = x; };
            
            /* ------------------ Assignment Operator --------------- */
            vector& operator= (const vector& x) {
                if ( this != &x ) {
                    this->_buffer = x._buffer;
                    this->_alloc = x._alloc;
                    this->_size = x._size;
                    this->_capacity = x._capacity;
                    this->_max_size = x._max_size;
                }
                return (*this);
            }
            /* ---------------------- Detructor --------------------- */
            ~vector() {
                _alloc.deallocate(_buffer, _capacity);
            };

            /* ---------------------- Iterators --------------------- */
            iterator        begin() { return iterator(this->_buffer); }
            const_iterator  begin() const { return iterator(this->_buffer); }
            iterator        end() { return iterator(this->_buffer + this->_size); }
            const_iterator  end() const { return iterator(this->_buffer + this->_size); }
            // reverse iterator

            /* ----------------------- Capacity --------------------- */
            size_type   size() const { return this->_size; }
            size_type   max_size() const { return this->_max_size; }
            /* void        resize (size_type n, value_type val = value_type()) {} // Needs insert */
            size_type   capacity() const { return this->_capacity; }
            bool        empty() const { return (this->_size == 0 ? true : false); }
            void        reserve (size_type n) {
                if (n <= this->_capacity)
                    return ;
                // PHASE 1 : Create temporary object in temporary_storage
                size_type   new_capacity = n;
                size_type   new_size = this->_size;
                T *         new_data = _alloc.allocate(new_capacity);
                // PHASE 2 : Copy data into temp
                for (size_type i = 0; i < new_size; i++)
                    new_data[i] = this->_buffer[i];
                // PHASE 3 : Swap temporary and current storage
                std::swap(new_capacity, this->_capacity);
                std::swap(new_size, this->_size);
                std::swap(new_data, this->_buffer);
                // PHASE 4 : Deallocate temporary (was the original data)
                _alloc.deallocate(new_data, _capacity);
            }

            /* -------------------- Element access ------------------ */
            reference       operator[] (size_type n) { return this->_buffer[n]; }
            const_reference operator[] (size_type n) const { return this->_buffer[n]; }
            reference       at(size_type n) { return this->_buffer[n]; }
            const_reference at(size_type n) const { return this->_buffer[n]; }
            reference       front() { return this->_buffer[0]; }
            const_reference front() const { return this->_buffer[0]; }
            reference       back() { return this->_buffer[this->_size - 1]; }
            const_reference back() const { return this->_buffer[this->_size - 1]; }

            /* ---------------------- Modifiers --------------------- */
            /* template <class InputIterator>
                void assign (InputIterator first, InputIterator last); */
            void    assign (size_type n, const value_type& val) {
                if (this->_capacity < n)
                    reserve(n);
                for (size_type i = 0; i < n; i++)
                    this->_buffer[i] = val;
                this->_size = n;
            }
            void    push_back (const value_type& val) {
                if (this->_capacity == 0)
                    reserve(1);
                if (this->_size + 1 > this->_capacity)
                    reserve(this->_capacity * 2);
                this->_buffer[this->_size] = val;
                this->_size++;
            };
            void    pop_back() {
                if (this->_capacity == 0 || this->_size == 0)
                    return ;
                this->_size--;
            }
            
            /* TO-DO:
                1 - Make the insert method for resize
                2 - Reverse iterator */

            /* ---------------------- Allocator --------------------- */
            allocator_type get_allocator() const { return this->_alloc; }

        private:
            value_type   *  _buffer;
            allocator_type  _alloc;
            size_type       _size;
            size_type       _max_size;
            size_type       _capacity;
    }
    
;}