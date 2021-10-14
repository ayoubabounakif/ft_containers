# 42cursus-ft_containers

## Description
The multiple available containers in C++ all have a very different usage. To make sure you understand them all, let's re-implement them!

## Objectives
In this project, you will implement the various container types of the C++ standard
template library.
For each container, turn in the appropriately named class files.
The namespace will always be ft and your containers will be tested using ft::<container>.
You need to respect the structure of the reference container. If it’s missing a part of the
orthodox canonical form, do not implement it.
As a reminder, we are coding in C++98, so any new feature of the containers MUST NOT
be implemented, but every old feature (even deprecated) is expected.
  
## Mandatory part
• Implement the following containers and turn in the necessary files <container>.hpp </br>
• You must also provide a main.cpp which tests everything for your evaluations. (you
need to go further than the example!)</br>
• You must produce one binary with only your containers and one with the same
testing with STL containers.</br>
• Compare outputs and timing (you can be up to 20 times slower).</br>
• member functions, Non-member and overloads are expected.</br>
• respect the naming, take care to details.</br>
• You must use std::allocator.</br>
• You must justify your inner data structure for each container (using a simple array
for a map is not ok).</br>
• If the container has an iterator system, you must implement it.</br>
• iterators_traits, reverse_iterator, enable_if, is_integral, equal/lexicographical compare, std::pair, std::make_pair, must be reimplemented.</br>
• You can use https://www.cplusplus.com/ and https://cppreference.com/ as
references.</br>
• You cannot implement more public functions than the ones offered in the standard
containers. Everything else must be private or protected. Each public function/-
variable must be justified.</br>
• For non-member overloads, the keyword friend is allowed. Each use of friend
must be justified and will be checked during evaluation.</br>
You must turn in the following containers and their associated functions:</br>
• Vector</br>
• Map</br>
• Stack</br>
Your stack will use your vector class as default underlaying container, it must still be
compatible with others containers like the STL one.</br>
STL containers are forbidden.</br>
You are allowed to use the STD library.

</br>
</br>
</br>
TEMPORARY :
• https://www.lix.polytechnique.fr/~liberti/public/computing/prog/libstdc++/
• https://www.lix.polytechnique.fr/~liberti/public/computing/prog/libstdc++/stl_introduction.html
• https://www.lix.polytechnique.fr/~liberti/public/computing/prog/libstdc++/Container.html
• https://www.lix.polytechnique.fr/~liberti/public/computing/prog/libstdc++/Iterators.html
• https://www.lix.polytechnique.fr/~liberti/public/computing/prog/libstdc++/Allocators.html
• https://www.cplusplus.com/reference/iterator/RandomAccessIterator/
• https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator