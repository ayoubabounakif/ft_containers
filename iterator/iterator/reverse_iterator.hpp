/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 10:08:58 by aabounak          #+#    #+#             */
/*   Updated: 2021/10/23 14:12:38 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/* ------------------------------- iterator --------------------------------- */
# include <iterator>
# include "../random_access_iterator/random_access_iterator.hpp"
# include "../iterator_traits/iterator_traits.hpp"

namespace ft {
    template <class Iterator>
    class reverse_iterator {

        public:
            typedef Iterator    iterator_type;
            typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
            typedef typename iterator_traits<Iterator>::value_type        value_type;
            typedef typename iterator_traits<Iterator>::difference_type   difference_type;
            typedef typename iterator_traits<Iterator>::pointer           pointer;
            typedef typename iterator_traits<Iterator>::reference         reference;

            reverse_iterator() : _iter() {};
            reverse_iterator( iterator_type it ) : _iter(--it) {};
            template< class U >
                reverse_iterator( const reverse_iterator<U>& other ) : _iter(other) {}
            // reverse_iterator( const reverse_iterator<iterator_type>& rev_it ) : _iter(rev_it) {}
            virtual ~reverse_iterator() {};
            reverse_iterator& operator= ( const reverse_iterator& rhs ) { this->_iter = rhs._iter; return (*this); }

                /* Misc Operators */
            reverse_iterator& operator+= ( difference_type rhs ) { this->_iter -= rhs; return *this; };
            reverse_iterator& operator-= ( difference_type rhs ) { this->_iter += rhs; return *this; };

            reference operator*() const { return *_iter; }
            pointer operator->() const { return _iter; }

            reference operator[]( difference_type rhs ) const { return (_iter[rhs]); };

                /* Arithmetic Operators */
            reverse_iterator& operator++() { --_iter; return *this; }
            reverse_iterator& operator--() { ++_iter; return *this; }
            reverse_iterator operator++( int ) { reverse_iterator tmp(*this); --_iter; return tmp; }
            reverse_iterator operator--( int ) { reverse_iterator tmp(*this); ++_iter; return tmp; }

            reverse_iterator operator+( difference_type rhs ) const { return reverse_iterator(_iter - rhs); }
            reverse_iterator operator-( difference_type rhs ) const { return reverse_iterator(_iter + rhs); }

                /* Comparison Operators */
            bool operator==( const reverse_iterator& rhs ) const { return _iter == rhs._iter; }
            bool operator!=( const reverse_iterator& rhs ) const { return _iter != rhs._iter; }
            bool operator>( const reverse_iterator& rhs ) const { return _iter > rhs._iter; }
            bool operator<( const reverse_iterator& rhs ) const { return _iter < rhs._iter; }
            bool operator>=( const reverse_iterator& rhs ) const { return _iter >= rhs._iter; }
            bool operator<=( const reverse_iterator& rhs ) const { return _iter <= rhs._iter; }

            iterator_type base() const { iterator_type tmp(*this); ++_iter; return tmp; }

        protected:
            iterator_type   _iter;
    };
}
