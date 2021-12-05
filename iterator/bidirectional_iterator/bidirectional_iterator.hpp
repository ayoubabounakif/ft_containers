/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 15:29:05 by aabounak          #+#    #+#             */
/*   Updated: 2021/12/05 17:55:38 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "../iterator_traits/iterator_traits.hpp"

//! if Linux
// #define ptrdiff_t __gnu_cxx::ptrdiff_t

namespace ft {
    template < class T >
    class bidirectional_iterator {
        public:
            typedef iterator_traits< iterator<std::bidirectional_iterator_tag, T> > iterator_traits;
            typedef typename iterator_traits::value_type        value_type;
            typedef typename iterator_traits::difference_type   difference_type;
            typedef typename iterator_traits::pointer           pointer;
            typedef typename iterator_traits::reference         reference;
            typedef typename iterator_traits::iterator_category iterator_category;

            bidirectional_iterator() : _data(nullptr) {};
            /* bidirectional_iterator( value_type * element ) : _data(element) {};
            bidirectional_iterator( const bidirectional_iterator& rhs ) : _data(rhs._data) {}
            bidirectional_iterator& operator= ( const bidirectional_iterator& rhs ) { this->_data = rhs._data; return (*this); } 
            virtual ~bidirectional_iterator() {}; */


            bidirectional_iterator& operator+= ( difference_type rhs ) { this->_data += rhs; return *this; };
            bidirectional_iterator& operator-= ( difference_type rhs ) { this->_data -= rhs; return *this; };
            reference operator*() const { return *_data; }
            pointer   operator->() const { return _data; }
            
            // pointer getData( void ) const { return (this->_data); }

        protected:
            pointer  _data;
            
    }
;}