#include "Hand.hpp"
//for unprocessed_cards, we use indices from 0-35
//ranked from 6-A,
//suits ranked by clubs,diamonds,hearts and spades
//rank indices from 0-8
//suit indices from 0-3


//0 hand strength means hand strength is not available 

Hand::Hand()//default constructor
{
	num_cards = 0;
	//9 different ranks with no cards
	cards = std::vector<unsigned int>(9,0);
	valid_hand_strength = false;
	hand_strength = 0;
}
//this constructor takes in a pre-process vector
Hand::Hand(int num_cards,const std::vector<unsigned int>& processed_cards)
{
	this->num_cards = num_cards;
	this->cards = processed_cards;
	this->valid_hand_strength = false;
	this->hand_strength = 0; 
}
//this constructor takes a unprocessed vector
//all the cards in vector are represented with 0-35 integers
Hand::Hand(const std::vector<int>& unprocessed_cards)
{
	this->num_cards = unprocessed_cards.size();
	this->valid_hand_strength = false;
	this->hand_strength = 0;
	std::vector<unsigned int> processed_cards(9,0);
	for(auto const& card:unprocessed_cards ){
		if(card >= 0 && card <= 35 ){
			int suit_index = card / 9;
			int rank_index = card % 9;
			processed_cards[rank_index] += std::pow(2,suit_index);

		}else{
			std::cout<<"wrong card index"<<std::endl;
		}
	}
	this->cards = processed_cards;
}
void Hand::add_cards(const std::vector<int>& unprocessed_cards){
	for(auto const& card:unprocessed_cards){
		if(card>=0 && card<= 35){
			int suit_index = card / 9;
			int rank_index = card % 9;
			//only add if card is not in hand already
			if(!(cards[rank_index]&(1<<suit_index))){
				cards[rank_index] += std::pow(2,suit_index);
				num_cards++;
			} else {
				std::cout<<"Duplicate card added: "<<card<<std::endl;
			}
		}else{ 
			std::cout<<"wrong card index"<<std::endl;
		}
	}
	valid_hand_strength = false;
}
void Hand::remove_cards(const std::vector<int>& unprocessed_cards){
	for(auto const& card:unprocessed_cards){
		if(card>=0 && card<= 35){
			int suit_index = card / 9;
			int rank_index = card % 9;
			//only remove if card is in hand else does nothing
			if(cards[rank_index]&(1<<suit_index)){
				cards[rank_index] -= std::pow(2,suit_index);
				num_cards--;
			}else {
				std::cout<<"Removing nonexist card: "<<card<<std::endl;
			}
		}else{
			std::cout<<"wrong card index"<<std::endl;
		}
	}
	valid_hand_strength = false;
}
void Hand::remove_all_cards(){
	cards = std::vector<unsigned int>(9,0);
	valid_hand_strength = false;
	hand_strength = 0;
	num_cards = 0;
}

void Hand::update_hand_strength(){
	//if current hand_strength is valid, then do nothing
	if(valid_hand_strength){
		return;
	}
	//if num_cards is less than 5 or more than 7, then hand strength is 0
	if(num_cards < 5 || num_cards > 7){
		hand_strength = 0;
		valid_hand_strength = true;
		return;
	}
	//find all conditions about current hand
	std::vector<unsigned int> has_ranks;
	std::vector<unsigned int> has_pairs;
	std::vector<unsigned int> has_trips;
	std::vector<unsigned int> has_nothing_ranks;//ranks have no pair no trips
	int has_quad = -1;//-1 means no quads 
	//loop through from A to 6
	//thus all the pair and trips are in descending order 
	for(int i=8;i>=0;i--){
		if(cards[i] != 0){
			has_ranks.push_back(i);
		}else{
			continue;
		}
		if(cards[i] == 15){
			has_quad = i;
		}else if(cards[i] == 7 || cards[i]== 11||
			cards[i]==13||cards[i]==14){
			has_trips.push_back(i);
		}else if(cards[i]==3 || cards[i]==5||cards[i]==6||
			cards[i]==9||cards[i]==10||cards[i]==12){
			has_pairs.push_back(i);
		}else{
			has_nothing_ranks.push_back(i);
		}

	}
	//check for straights
	unsigned int straight_count = 1;//how many connected ranks are in hand
	unsigned int curr_highest_straight = has_ranks[0];//start from Ace thus index 8
	unsigned int curr_straight = has_ranks[0];//straight index pointer
	bool has_stright = false;
	//since there are at least 5 cards, there are at least two ranks in the vector
	for(unsigned int i=1;i<has_ranks.size();i++){
		//if difference is 1
		if(curr_straight - has_ranks[i]==1){
			curr_straight = has_ranks[i];
			straight_count++;
			//if straight is found,then finish loop
			if(straight_count == 5){
				has_stright = true;
				break;
			}
		}else{
			curr_highest_straight = has_ranks[i];
			curr_straight = has_ranks[i];
			straight_count = 1;
		}
		//A-9 straight special case
		//if current straight is 9 and  Ace is in hand and straight count is 4
		if(curr_highest_straight == 3 && straight_count== 4 && has_ranks[8]!= 0 ){
			straight_count = 5;
			has_stright = true;
			break;
		}
	}
	//now we check flush and straight_flush
	bool has_flush = false;
	//if there is a flush, the suit index for flush
	unsigned int flush_suit = -1;
	std::vector<std::vector<unsigned int>> suits(4,std::vector<unsigned int>());
	for(int i=8;i>=0;i--){
		if(cards[i]==0){
			continue;
		}
		//check for each suit
		//suit is indexed from 0-3
		for(unsigned int suit_index = 0;suit_index<4;suit_index++){
			if(cards[i]&(1<<suit_index)){
				suits[suit_index].push_back(i);
			}
		}
	}
	//since there are at most 7 cards, each hand can have at most 1 suit flush
	for(unsigned int suit_index = 0;suit_index<4;suit_index++){
		if(suits[suit_index].size()>=5){
			has_flush = true;
			flush_suit = suit_index;
			break;
		}
	}
	//check straight flush
	//only check if both straight and flush are available
	bool has_stright_flush = false;
	unsigned int straight_flush_count = 1;
	unsigned int curr_highest_straight_flush = 0;
	unsigned int curr_straight_flush = 0;
	if(has_flush && has_stright){
		curr_highest_straight_flush = suits[flush_suit][0];
		curr_straight_flush = suits[flush_suit][0];
		//similar algorithm for detecting straight
		for(unsigned int i=1;i<suits[flush_suit].size();i++){
			if(curr_straight_flush - suits[flush_suit][i] == 1){
				curr_straight_flush = suits[flush_suit][i];
				straight_flush_count++;
				if(straight_flush_count == 5){
					has_stright_flush = true;
					break;
				}
			}else{
				curr_highest_straight_flush = suits[flush_suit][i];
				curr_straight_flush = suits[flush_suit][i];
				straight_flush_count = 1;
			}
			//A-9 straight special case
			//if current straight flush is 9 and largest element in flush suit is Ace and straight flush count is 4
			if(curr_highest_straight_flush == 3 && straight_flush_count== 4 && suits[flush_suit][0]== 8 ){
				straight_flush_count = 5;
				has_stright_flush = true;
			}
		}
	}

	//with above information, we determine the strongest hand strength available 
	unsigned int result = 0;
	unsigned int hand_strength_ranking = 0;
	unsigned int hand_strength_signature = 0;
	//determine hand strength 
	if(has_stright_flush){
		//normal straight flush and royal flush
		if(curr_highest_straight_flush==8){//royal flush
			hand_strength_ranking = 10;
			hand_strength_signature = 0;
		}else{
			hand_strength_ranking = 9;
			hand_strength_signature = curr_highest_straight_flush;
		}
	}else if(has_quad!=-1){
		hand_strength_ranking = 8;
		hand_strength_signature = has_quad;
	}else if(has_flush){
		hand_strength_ranking = 7;
		for(int i=0;i<5;i++){
			hand_strength_signature += (1<<suits[flush_suit][i]);
		}
	}else if((has_trips.size()>0&&has_pairs.size()>0)||(has_trips.size()>=2)){//full house
		//full house can use lower trips for pair if there is one
		hand_strength_ranking = 6;
		if(has_trips.size()==1){
			hand_strength_signature = (1<<has_trips[0]);
			hand_strength_signature = hand_strength_signature << 9;
			hand_strength_signature += (1<<has_pairs[0]);
		}else{
			hand_strength_signature = (1<<has_trips[0]);
			hand_strength_signature = hand_strength_signature << 9;
			hand_strength_signature += (1<<has_trips[1]);
		}
	}else if(has_stright){
		hand_strength_ranking = 5;
		hand_strength_signature = curr_highest_straight;
	}else if(has_trips.size() > 0){
		hand_strength_ranking = 4;
		hand_strength_signature = (1<<has_trips[0]);
		hand_strength_signature = hand_strength_signature << 9;
		hand_strength_signature += (1<<has_nothing_ranks[0]);
		hand_strength_signature += (1<<has_nothing_ranks[1]);
	}else if(has_pairs.size()>=2){
		hand_strength_ranking = 3;
		hand_strength_signature = (1<<has_pairs[0]);
		hand_strength_signature += (1<<has_pairs[1]);
		hand_strength_signature = hand_strength_signature << 9;
		hand_strength_signature += (1<<has_nothing_ranks[0]);
	}else if(has_pairs.size()==1){
		hand_strength_ranking = 2;
		hand_strength_signature += (1<<has_pairs[0]);
		hand_strength_signature = hand_strength_signature << 9;
		for(int i=0;i<3;i++){
			hand_strength_signature += (1<<has_nothing_ranks[i]);
		}
	}else{
		hand_strength_ranking = 1;
		for(int i=0;i<5;i++){
			hand_strength_signature += (1<<has_ranks[i]);
		}

	}
	hand_strength_ranking = hand_strength_ranking <<28;
	result = hand_strength_ranking + hand_strength_signature;
	this->hand_strength = result;
	valid_hand_strength = true;

}

std::string Hand::get_hand_strength_str(){
	if(!valid_hand_strength){
		update_hand_strength();
	}
	std::string result;
	//get the most significant bit of hand strength first
	unsigned int hand_strength_bits = 15;
	unsigned int curr_hand_ranking = (hand_strength>>28) & hand_strength_bits;
	if(curr_hand_ranking==1){
		result += "High Card";
	}else if(curr_hand_ranking==2){
		result += "One Pair";
	}else if(curr_hand_ranking==3){
		result += "Two Pair";
	}else if(curr_hand_ranking==4){
		result += "Straight";
	}else if(curr_hand_ranking==5){
		result += "Three of a kind";
	}else if(curr_hand_ranking==6){
		result += "Full House";
	}else if(curr_hand_ranking==7){
		result += "Flush";
	}else if(curr_hand_ranking==8){
		result += "Four of a kind";
	}else if(curr_hand_ranking==9){
		result += "Stright Flush";
	}else if(curr_hand_ranking==10){
		result += "Royal Flush";
	}
	return result;
}

