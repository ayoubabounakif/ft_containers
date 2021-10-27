/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:26:50 by aabounak          #+#    #+#             */
/*   Updated: 2021/10/27 12:58:43 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "../iterator/iterator.hpp"

/* //! if Linux
#define ptrdiff_t __gnu_cxx::ptrdiff_t */

namespace ft {
    /* --       Definition:
        iterator_traits is the type trait class that provides uniform interface to the properties of LegacyIterator types.
        This makes it possible to implement algorithms only in terms of iterators.
        The template can be specialized for user-defined iterators so that the information about the iterator can be retrieved
        even if the type does not provide the usual typedefs. */
    
    template < class Iterator >
    struct iterator_traits {
        typedef typename Iterator::difference_type   difference_type;
        typedef typename Iterator::value_type        value_type;
        typedef typename Iterator::pointer           pointer;
        typedef typename Iterator::reference         reference;
        typedef typename Iterator::iterator_category iterator_category;
    };
    template < class T >
    struct iterator_traits<T*> {
        typedef ptrdiff_t                   difference_type;
        typedef T                           value_type;
        typedef T*                          pointer;
        typedef T&                          reference;
        typedef typename std::random_access_iterator_tag    iterator_category;
    };
    template < class T >
    struct iterator_traits<const T*> {
        typedef ptrdiff_t                   difference_type;
        typedef T                           value_type;
        typedef const T*                    pointer;
        typedef const T&                    reference;
        typedef typename std::random_access_iterator_tag    iterator_category;
    };

/*     template<class InputIterator>
        typename iterator_traits<InputIterator>::difference_type distance (InputIterator first, InputIterator last) {
            typename iterator_traits<InputIterator>::difference_type rtn = 0;
            while (first != last) { first++; rtn++; } return (rtn);
        } */

}
