#ifndef TEST_H
#define TEST_H

#include <vector>
#include <set>
#include <iostream>
#include <utility>
#include <string>
#include <cmath>
#include <bitset>
#include <cstdlib>
#include <algorithm>
#include <iterator>
#include "Hand.hpp"
#include "Helper.hpp"

//test all possible seven cards hands to check the frequency of each hand ranking
std::vector<unsigned int> test_all_seven_cards_combos();
//test all possible five cards hands to check the frequency of each hand ranking
std::vector<unsigned int> test_all_five_cards_combos();
//test straight hand recognition 
void test_all_straights();
#endif