#ifndef HAND_H
#define HAND_H

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

class Hand{
private:
	int num_cards;
	std::vector<unsigned int> cards;
	bool valid_hand_strength;//is_current hand strength value valid
	unsigned int hand_strength; 
public:
	//default constructor
	Hand();
	//this constructor takes in a pre-process vector
	Hand(int num_cards,const std::vector<unsigned int>& processed_cards);
	//this constructor takes a unprocessed vector
	//all the cards in vector are represented with 0-35 integers
	Hand(const std::vector<int>& unprocessed_cards);

	void add_cards(const std::vector<int>& unprocessed_cards);

	void remove_cards(const std::vector<int>& unprocessed_cards);
	void remove_all_cards();
	void update_hand_strength();
	//return the hand strength in string in English
	std::string get_hand_strength_str();
	int get_num_cards() const{
		return num_cards;
	}

	//return array of processed cards
	const std::vector<unsigned int>& get_card_array() const{
		return cards;
	}
	unsigned int get_hand_strength(){
		if(valid_hand_strength){
			return hand_strength;
		}else{
			update_hand_strength();
			return hand_strength;
		}
	}

};
#endif