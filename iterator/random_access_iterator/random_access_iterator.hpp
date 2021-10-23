/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:26:04 by aabounak          #+#    #+#             */
/*   Updated: 2021/10/23 12:17:31 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "../iterator_traits/iterator_traits.hpp"

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
            typedef typename iterator_traits::value_type        value_type;
            typedef typename iterator_traits::difference_type   difference_type;
            typedef typename iterator_traits::pointer           pointer;
            typedef typename iterator_traits::reference         reference;
            typedef typename iterator_traits::iterator_category iterator_category;

            random_access_iterator() : _data(nullptr) {};
            random_access_iterator( value_type * element ) : _data(element) {};
            random_access_iterator( const random_access_iterator& rhs ) : _data(rhs._data) {}
            virtual ~random_access_iterator() {};
            random_access_iterator& operator= ( const random_access_iterator& rhs ) { this->_data = rhs._data; return (*this); }
            
                /* Misc Operators */
            random_access_iterator& operator+= ( difference_type rhs ) { this->_data += rhs; return *this; };
            random_access_iterator& operator-= ( difference_type rhs ) { this->_data -= rhs; return *this; };
            
            reference operator*() const { return *_data; }
            pointer operator->() const { return _data; }
            
            reference operator[]( difference_type rhs ) const { return (_data[rhs]); };
    
                /* Arithmetic Operators */
            random_access_iterator& operator++() { ++_data; return *this; }
            random_access_iterator& operator--() { --_data; return *this; }
            random_access_iterator operator++( int ) { random_access_iterator tmp(*this); ++_data; return tmp; }
            random_access_iterator operator--( int ) { random_access_iterator tmp(*this); --_data; return tmp; }

            difference_type operator+( const random_access_iterator& rhs ) const { return _data + rhs._data; }
            difference_type operator-( const random_access_iterator& rhs ) const { return _data - rhs._data; }
            random_access_iterator operator+( difference_type rhs ) const { return random_access_iterator(_data + rhs); }
            random_access_iterator operator-( difference_type rhs ) const { return random_access_iterator(_data - rhs); }
    
                /* Comparison Operators */
            bool operator==( const random_access_iterator& rhs ) const { return _data == rhs._data; }
            bool operator!=( const random_access_iterator& rhs ) const { return _data != rhs._data; }
            bool operator>( const random_access_iterator& rhs ) const { return _data > rhs._data; }
            bool operator<( const random_access_iterator& rhs ) const { return _data < rhs._data; }
            bool operator>=( const random_access_iterator& rhs ) const { return _data >= rhs._data; }
            bool operator<=( const random_access_iterator& rhs ) const { return _data <= rhs._data; }

            operator random_access_iterator<const value_type> () const { return random_access_iterator<const value_type>(_data) ; }
 
        protected:
            pointer  _data;
    };
;}