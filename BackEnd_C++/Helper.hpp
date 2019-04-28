#ifndef HELPER_H
#define HELPER_H

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
#include <fstream>
#include <ios>
#include <chrono>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include "Hand.hpp"

//calculate the number of combinations give n and k
unsigned long long int
calculate_num_combos(unsigned long long int n, unsigned long long int k);
unsigned long long int get_hash(unsigned long long int bitString);
void find_combo(std::vector<std::vector<int>>& result,std::vector<int>& combo,
	const std::vector<int>& remaining_cards,int offset,int k);

//get a vector of known cards and number of elements k
//return a vector of vectors of cards
std::vector<std::vector<int>> get_combos(const std::vector<int>& known_cards,int k);
//get a vector of all starting hands in unprocessed indices
//std::vector<int> get_all_starting_hands();
// std::vector<std::pair<std::string,double>> 
void get_all_starting_hands_equity_against_all_combos_in_heads_up_pot(int,int);

//covert string representation to card index from 0-35
int covert_card_str_to_card_index(const std::string& card_str);
//covert card index from 0-35 to string representation 
std::string covert_card_index_to_card_str(const int card_index);
//vector version
std::vector<int> covert_card_str_to_card_index_vector(const std::vector<std::string>& card_strs);
std::vector<std::string> covert_card_index_to_card_str_vector(const std::vector<int>& card_indices);
std::string covert_card_index_to_single_card_str(const std::vector<int>& card_indices);
unsigned long long int covert_card_index_to_bits(const std::vector<int>& card_indices);
//calculate equity of hands
std::vector<double> get_hands_equity
	(const std::vector<std::vector<int>>& hole_cards,
		const std::vector<int>& board,const std::vector<int>& deadCards);
std::vector<std::string> splitString(const std::string& inputStr,const std::string& delimiter);


//cahce functions
//all C(36,2) combos
void output_starting_hand_indices();
//all C(36,5) combos
void output_board_indices();
//C(36,2) * C(36,5) hand strength
void output_hand_strength_matrix();
//C(36,7) hand strength vector
void output_hand_strength_vector();
//read cache data
void read_cached_data_trips_version(std::unordered_map<unsigned long long int,unsigned int>&);
void read_cached_data_straight_version(std::unordered_map<unsigned long long int,unsigned int>&);
void read_cached_data_own_hash(unsigned int *score_table);
void read_cached_data_flop_dist_trips_version(std::unordered_map<unsigned long long int,std::unordered_map<unsigned long long int,std::vector<unsigned int>>>&);
void read_cached_data_flop_dist_straight_version(std::unordered_map<unsigned long long int,std::unordered_map<unsigned long long int,std::vector<unsigned int>>>&);
std::vector<double> get_hands_equity
	(const std::vector<std::vector<int>>& hole_cards,
		const std::vector<int>& board,const std::vector<int>& deadCards,
		const std::unordered_map<unsigned long long int,unsigned int>& score_table);

std::vector<double> get_monte_carlo_range_equity
	(const std::vector<std::vector<std::vector<int>>> player_hands,
		const std::vector<int>& board,const std::vector<int>& deadCards,
		const std::unordered_map<unsigned long long int,unsigned int>& score_table);

#endif