/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:32:49 by aabounak          #+#    #+#             */
/*   Updated: 2021/10/25 14:20:14 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft {

                    /* ----------- Algorithm ----------- */

    /* --- Equal -------------------------------------------------------- */
        /* --       Definition:
            Compares the elements in the range [first1,last1) with those in the range beginning at first2,
            and returns true if all of the elements in both ranges match. */
        /* --       Return values:
            true if all the elements in the range [first1,last1) compare equal to those of the range starting at first2.
            false otherwise. */

    template <class InputIterator1, class InputIterator2>
    bool equal (InputIterator1 first1, InputIterator1 last1,
                InputIterator2 first2) {
        while (first1 != last1) { if (!(*first1 == *first2)) return false;
            ++first1; ++first2;
        } return true;
    }

    template <class InputIterator1, class InputIterator2, class BinaryPredicate>
    bool equal (InputIterator1 first1, InputIterator1 last1,
                InputIterator2 first2, BinaryPredicate pred) {
        while (first1 != last1) { if (!pred(*first1, *first2)) return false;
            ++first1; ++first2;
        } return true;  
    }

    /* --- Lexicographical_compare -------------------------------------- */
        /* --       Definition:
            Returns true if the range [first1,last1) compares lexicographically less than the range [first2,last2).
            A lexicographical comparison is the kind of comparison generally used to sort words alphabetically in dictionaries;
            It involves comparing sequentially the elements that have the same position in both ranges against each other until one element is not equivalent to the other.
            The result of comparing these first non-matching elements is the result of the lexicographical comparison.
            If both sequences compare equal until one of them ends, the shorter sequence is lexicographically less than the longer one.
            The elements are compared using operator< for the first version, and comp for the second.
            Two elements, a and b are considered equivalent if (!(a<b) && !(b<a)) or if (!comp(a,b) && !comp(b,a)). */
        /* --       Return values:
            true if the first range compares lexicographically less than the second.
            false otherwise (including when all the elements of both ranges are equivalent). */
    
    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                  InputIterator2 first2, InputIterator2 last2) {
        while (first1 != last1) {
            if (first2 == last2 || *first2 < *first1) return false;
            else if (*first1 < *first2) return true;
            ++first1; ++first2;
        } return (first2 != last2);
    }

    template <class InputIterator1, class InputIterator2, class Compare>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                    InputIterator2 first2, InputIterator2 last2,
                                    Compare comp) {
        while (first1 != last1) {
            if (first2 == last2 || comp(*first2, *first1)) return false;
            else if (comp(*first1, *first2)) return true;
            ++first1; ++first2;
        } return (first2 != last2);                                    
    }
}