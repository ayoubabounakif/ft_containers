/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pair.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:33:46 by aabounak          #+#    #+#             */
/*   Updated: 2021/12/02 17:18:47 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "pair.hpp"

namespace ft {
    
    /* --       Definition:
    Constructs a pair object with its first element set to x and its second element set to y. */

template <class T1, class T2>
    pair<T1, T2> make_pair (T1 x, T2 y) { return pair<T1, T2>(x, y); }
}