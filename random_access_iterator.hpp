/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:26:04 by aabounak          #+#    #+#             */
/*   Updated: 2021/10/15 18:25:20 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "iterator_traits.hpp"

namespace ft {
    // A very random, random access iterator implementation hh
    template < class T >
    class random_access_iterator {
        public:
                /*     When dealing with templates,
                    you cannot separate the class declaration and class implementation into separate files
                    (at least not without including the .cpp file at the end of the .h file).
                    This is due to how templates are compiled.
                    The simplest ways to do is to inline your functions. */

                        /* These typedefs are the most stupid thing I've seen in life... */
            typedef iterator_traits< iterator<std::random_access_iterator_tag, T> > iterator_traits;
            typedef typename iterator_traits::value_type       value_type;
            typedef typename iterator_traits::difference_type  difference_type;

            random_access_iterator() : _data(nullptr) {};
            random_access_iterator( value_type * element ) : _data(element) {};
            random_access_iterator( const random_access_iterator& rhs ) : _data(rhs._data) {}
            virtual ~random_access_iterator() {};
            inline random_access_iterator& operator= ( const random_access_iterator& rhs ) { this->_data = rhs._data; return (*this); }
            
                /* Misc Operators */
            inline random_access_iterator& operator+= ( difference_type rhs ) { this->_data += rhs; return *this; };
            inline random_access_iterator& operator-= ( difference_type rhs ) { this->_data -= rhs; return *this; };
            
            inline T& operator*() const { return *_data; }
            inline T* operator->() const { return _data; }
            
            inline T& operator[]( difference_type rhs ) { return (_data[rhs]); };

                        /* TO-DO: -- Some of these should be non-member functions */
    
                /* Arithmetic Operators */
            inline random_access_iterator& operator++() { ++_data; return *this; }
            inline random_access_iterator& operator--() { --_data; return *this; }
            inline random_access_iterator operator++( int ) const { random_access_iterator tmp(*this); ++_data; return tmp; }
            inline random_access_iterator operator--( int ) const { random_access_iterator tmp(*this); --_data; return tmp; }

          /*   inline difference_type operator+( const random_access_iterator& rhs ) const { return random_access_iterator(_data + rhs._data); }
            inline difference_type operator-( const random_access_iterator& rhs ) const { return random_access_iterator(_data - rhs._data); }
            inline random_access_iterator operator+( difference_type rhs ) const { return random_access_iterator(_data + rhs); }
            inline random_access_iterator operator-( difference_type rhs ) const { return random_access_iterator(_data - rhs); }
            inline random_access_iterator operator+( difference_type lhs, const random_access_iterator& rhs ) { return random_access_iterator(lhs + rhs._data); }
            inline random_access_iterator operator-( difference_type lhs, const random_access_iterator& rhs ) { return random_access_iterator(lhs - rhs._data); } */
    
                /* Comparison Operators */
            inline bool operator==( const random_access_iterator& rhs ) const { return _data == rhs->_data; }
            inline bool operator!=( const random_access_iterator& rhs ) const { return _data != rhs._data; }
            inline bool operator>( const random_access_iterator& rhs ) const { return _data > rhs._data; }
            inline bool operator<( const random_access_iterator& rhs ) const { return _data < rhs._data; }
            inline bool operator>=( const random_access_iterator& rhs ) const { return _data >= rhs._data; }
            inline bool operator<=( const random_access_iterator& rhs ) const { return _data <= rhs._data; }
 
            value_type  * getData( void ) { return this->_data; };

        private:
            value_type  * _data;
    };
;}