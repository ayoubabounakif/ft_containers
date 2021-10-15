/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:26:04 by aabounak          #+#    #+#             */
/*   Updated: 2021/10/15 14:32:55 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "iterator_traits.hpp"

namespace ft {
    // A very random, random access iterator implementation hh
    template < class T >
    class random_access_iterator : public iterator_traits< iterator<std::random_access_iterator_tag, T> > {
        public:
            typedef iterator::value_type       value_type;
            typedef iterator::difference_type  difference_type;

            random_access_iterator() : _data(nullptr) {};
            random_access_iterator( value_type * element ) : _data(element) {};
            random_access_iterator( const random_access_iterator& rhs ) : _data(rhs._data) {}
            random_access_iterator& operator= ( const random_access_iterator& rhs ) { this->_data = rhs._data; return (*this); }
            
            //      Misc Operators
            random_access_iterator& operator+= ( difference_type rhs ) { this->_data += rhs; return *this; };
            random_access_iterator& operator-= ( difference_type rhs ) { this->_data -= rhs; return *this; };
            T& operator*() const { return *_data; }
            T* operator->() const { return _data; }
            T& operator[]( difference_type rhs ) { return (_data[rhs]); };
    /*         TO-DO:           Some of these should be non-member functions */
            //      Arithmetic Operators
            random_access_iterator& operator++() { ++_data; return *this; }
            random_access_iterator& operator--() { --_data; return *this; }
            random_access_iterator operator++( int ) const { random_access_iterator tmp(*this); ++_data; return tmp; }
            random_access_iterator operator--( int ) const { random_access_iterator tmp(*this); --_data; return tmp; }
            /* difference_type operator+( const random_access_iterator& rhs ) const { return random_access_iterator(_data + rhs.ptr); }
            difference_type operator-( const random_access_iterator& rhs ) const { return random_access_iterator(_data - rhs.ptr); }
            random_access_iterator operator+( difference_type rhs ) const { return random_access_iterator(_data + rhs); }
            random_access_iterator operator-( difference_type rhs ) const { return random_access_iterator(_data - rhs); }
            random_access_iterator operator+( difference_type lhs, const random_access_iterator& rhs ) { return random_access_iterator(lhs + rhs._data); }
            random_access_iterator operator-( difference_type lhs, const random_access_iterator& rhs ) { return random_access_iterator(lhs - rhs._data); } */
            //      Comparison Operators
            bool operator==( const random_access_iterator& rhs ) const { return _data == rhs._data; }
            bool operator!=( const random_access_iterator& rhs ) const { return _data != rhs._data; }
            bool operator>( const random_access_iterator& rhs ) const { return _data > rhs._data; }
            bool operator<( const random_access_iterator& rhs ) const { return _data < rhs._data; }
            bool operator>=( const random_access_iterator& rhs ) const { return _data >= rhs._data; }
            bool operator<=( const random_access_iterator& rhs ) const { return _data <= rhs._data; }
 
            virtual ~random_access_iterator() {};

        private:
            value_type  * _data;
    };
;}