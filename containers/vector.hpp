/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 14:25:24 by aabounak          #+#    #+#             */
/*   Updated: 2021/10/23 10:09:16 by aabounak         ###   ########.fr       */
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
/* ------------------------------ Exception --------------------------------- */
# include <stdexcept>
/* ------------------------------ Iterator --------------------------------- */
# include <iterator>

# include "../iterator/iterator/iterator.hpp"
# include "../iterator/iterator/reverse_iterator.hpp"
# include "../iterator/iterator_traits/iterator_traits.hpp"
# include "../iterator/random_access_iterator/random_access_iterator.hpp"
# include "../type_traits/type_traits.hpp"
# include "../algorithm/algorithm.hpp"

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
                _capacity(0) {}
    
            /* ------------------------ Fill ------------------------ */
            explicit vector (size_type n, const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type()) :
                _alloc(alloc),
                _size(n),
                _capacity(n) {
                    _buffer = _alloc.allocate(_capacity);
                    for (size_type i  = 0; i < n; i++) _alloc.construct(&_buffer[i], val);
                }

            /* ------------------------ Range ----------------------- */
            template <class InputIterator>
            vector (InputIterator first, InputIterator last,
                    const allocator_type& alloc = allocator_type(),
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator()) :
                _alloc(alloc),
                _size(last - first),
                _capacity(last - first) {
                    _buffer = _alloc.allocate(_capacity);
                    size_type distance = last - first;
                    for (size_type i = 0; i < distance; i++) _alloc.construct(&_buffer[i], *first); first++;
                }
            
            /* ------------------------ Copy ------------------------ */
            vector (const vector& x) { *this = x; };
            
            /* ------------------ Assignment Operator --------------- */
            vector& operator= (const vector& x) {
                if ( this != &x ) {
                    this->_buffer = _alloc.allocate(x._capacity);
                    for (size_type i = 0; i < this->_size; i++)
                       _alloc.construct(&_buffer[i], x._buffer[i]);
                    this->_capacity = x._capacity;
                    this->_alloc = x._alloc;
                    this->_size = x._size;
                }
                return (*this);
            }
            
            /* ---------------------- Detructor --------------------- */
            ~vector() {
                for (size_type i = 0; i < _size; i++) _alloc.destroy(&_buffer[i]);
                _alloc.deallocate(_buffer, _capacity);
            };

            /* ---------------------- Iterators --------------------- */
            iterator        begin() { return iterator(&this->_buffer[0]); }
            const_iterator  begin() const { return iterator(&this->_buffer[0]); }
            iterator        end() { return iterator(&this->_buffer[this->_size]); }
            const_iterator  end() const { return iterator(&this->_buffer[this->_size]); }
                /* TO-DO:
                    - Make a reverse iterator */

            /* ----------------------- Capacity --------------------- */
            size_type   size() const { return this->_size; }
            size_type   max_size() const { return _alloc.max_size(); }
            void        resize (size_type n, value_type val = value_type()) {
                if (n < this->_size) { for (; this->_size > n; this->_size--) _alloc.destroy(&this->_buffer[this->_size]); }
                if (n >= this->_size) { reserve(n); for (; this->_size < n; this->_size++) _alloc.construct(&this->_buffer[this->_size], val); };
            }
            size_type   capacity() const { return this->_capacity; }
            bool        empty() const { return (this->_size == 0 ? true : false); }
            void        reserve (size_type n) {
                if (n <= this->_capacity) return ;
                // PHASE 1 : Create temporary object in temporary_storage
                size_type   new_capacity = n;
                size_type   new_size = this->_size;
                T *         new_data = _alloc.allocate(new_capacity);
                // PHASE 2 : Copy data into temp
                for (size_type i = 0; i < new_size; i++) _alloc.construct(&new_data[i], this->_buffer[i]);
                // PHASE 3 : Swap temporary and current storage
                std::swap(new_capacity, this->_capacity);
                std::swap(new_size, this->_size);
                std::swap(new_data, this->_buffer);
                // PHASE 4 : Deallocate temporary (was the original data)
                for (size_type i = 0; i < _size; i++) _alloc.destroy(&new_data[i]);
                _alloc.deallocate(new_data, _capacity);
            }

            /* -------------------- Element access ------------------ */
            reference       operator[] (size_type n) { return this->_buffer[n]; }
            const_reference operator[] (size_type n) const { return this->_buffer[n]; }
            reference       at(size_type n) { if (n >= this->_size) throw std::out_of_range("vector: element's out of bounds"); return this->_buffer[n]; }
            const_reference at(size_type n) const { if (n >= this->_size) throw std::out_of_range("vector: element's out of bounds"); return this->_buffer[n]; }
            reference       front() { return this->_buffer[0]; }
            const_reference front() const { return this->_buffer[0]; }
            reference       back() { return this->_buffer[this->_size - 1]; }
            const_reference back() const { return this->_buffer[this->_size - 1]; }

            /* ---------------------- Modifiers --------------------- */
            template <class InputIterator>
                void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator()) {
                    size_type distance = std::distance(first, last);
                    if (this->_capacity < distance) reserve(distance);
                    for (size_type i = 0; i < this->_size; i++) _alloc.destroy(&this->_buffer[i]);
                    for (size_type i = 0; i < distance; i++) { _alloc.construct(&this->_buffer[i], *first); first++; }
                    this->_size = distance;
                }
            void    assign (size_type n, const value_type& val) {
                if (this->_capacity < n) reserve(n);
                size_type i = 0;
                for (; i < this->_size; i++) _alloc.destroy(&this->_buffer[i]);
                for (i = 0; i < n; i++) _alloc.construct(&this->_buffer[i], val);
                this->_size = n;
            }
            void    push_back (const value_type& val) {
                if (this->_capacity == 0) reserve(1);
                if (this->_size + 1 > this->_capacity) reserve(this->_capacity * 2);
                this->_buffer[this->_size] = val;
                this->_size++;
            }
            void    pop_back() {
                if (this->_capacity == 0 || this->_size == 0) return ;
                _alloc.destroy(&_buffer[this->_size]);
                this->_size--;
            }
            iterator    insert (iterator position, const value_type& val) {
                difference_type idx = std::distance(begin(), position);
                if (this->_size + 1 > this->_capacity) reserve(this->_capacity * 2);
                for (difference_type i = this->_size - 1; i > idx; i--) _alloc.construct(&_buffer[i + 1], _buffer[i]);
                _alloc.construct(&_buffer[idx], val);
                this->_size++;
                return (iterator(this->_buffer + idx)); 
            }
			void    insert(iterator position, size_type n, const value_type& val)
			{
				difference_type	idx = std::distance(begin(), position);
				if (this->_size + n > this->_capacity) { if (n > _size) reserve(_size + n); else reserve(_capacity * 2); }
				for (difference_type i = this->_size - 1; i >= idx; i--) _alloc.construct(&_buffer[i + n], _buffer[i]);
				for (size_type i = 0; i < n; i++) _alloc.construct(&_buffer[idx + i], val);
				this->_size += n;
			}
			template <class InputIterator>
			void    insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
			{
				difference_type	idx = std::distance(begin(), position);
				size_type n = std::distance(first, last);
				if (this->_size + n > _capacity) { if (n > _size) reserve(_size + n); else reserve(_capacity * 2); }
				for (difference_type i = _size - 1; i >= idx; i--) _alloc.construct(&_buffer[i + n], _buffer[i]);
				for (size_type i = 0; i < n; i++) { _alloc.construct(&_buffer[idx + i], *first); first++; }
				this->_size += n;
			}
            iterator erase (iterator position) {
                difference_type idx = position - begin();
                _alloc.destroy(this->_buffer + idx);
                for (size_type i = idx; i < this->_size; i++)
                    this->_buffer[i] = this->_buffer[i + 1];
                this->_size--;
                return (iterator(this->_buffer + idx));
            }
            iterator erase (iterator first, iterator last) {
                difference_type idx = std::distance(begin(), first);
                difference_type n = std::distance(first, last);
                for (difference_type i = idx; i < n; i++)
                    _alloc.destroy(&this->_buffer[i]);
                this->_size -= n;
                for (size_type i = idx; i < this->_size; i++)
                   this->_buffer[i] = this->_buffer[n++];
                return (iterator(this->_buffer + idx));
            }
            void    swap (vector& x) {
                std::swap(x._buffer, this->_buffer);
                std::swap(x._capacity, this->_capacity);
                std::swap(x._buffer, this->_buffer);
            }
            void    clear() { for (size_type i = 0; i < this->_size; i++) _alloc.destroy(&_buffer[i]); this->_size = 0; }

            /* ---------------------- Allocator --------------------- */
            allocator_type get_allocator() const { return this->_alloc; }

        private:
            value_type   *  _buffer;
            allocator_type  _alloc;
            size_type       _size;
            size_type       _capacity;
    };
            /* ----------- Non-member function overloads ----------- */
    /* ------------------------ Relational Operators ------------------------ */
/* 	template <class T, class Alloc>
	  bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (lhs._buffer == rhs._buffer ? true : false); };
	template <class T, class Alloc>
	  bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (lhs._buffer != rhs._buffer ? true : false ); };
	template <class T, class Alloc>
	  bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (lhs._buffer < rhs._buffer ? true : false ); };
	template <class T, class Alloc>
	  bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (lhs._buffer <= rhs._buffer ? true : false ); };
	template <class T, class Alloc>
	  bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (lhs._buffer > rhs._buffer ? true : false ); };
	template <class T, class Alloc>
	  bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (lhs._buffer >= rhs._buffer ? true : false ); }; */

    /* ------------------------------- Swap --------------------------------- */

}