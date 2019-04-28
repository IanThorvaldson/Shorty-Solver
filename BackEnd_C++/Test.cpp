#include "Test.hpp"

//test all possible seven cards hands to check the frequency of each hand ranking
std::vector<unsigned int> test_all_seven_cards_combos(){
	std::vector<std::vector<int>> all_combos = std::move(get_combos({},7));
	//unsigned long long int combo_size = all_combos.size();
	Hand testhand;
	std::vector<unsigned int> num_rankings(10,0);
	unsigned int hand_strength_ranking = 0;
	for(unsigned int i=0;i<all_combos.size();i++){
		testhand.add_cards(all_combos[i]);
		hand_strength_ranking = testhand.get_hand_strength();
		hand_strength_ranking = hand_strength_ranking >> 28;
		num_rankings[hand_strength_ranking-1]++;
		testhand.remove_cards(all_combos[i]);
	}
	// std::vector<double> result(10,0);
	// for(int i=0;i<10;i++){
	// 	result[i] = num_rankings[i]/combo_size;
	// }
	return num_rankings;
} 

//test all possible five cards hands to check the frequency of each hand ranking
std::vector<unsigned int> test_all_five_cards_combos(){
	std::vector<std::vector<int>> all_combos = get_combos({},5);
	//unsigned long long int combo_size = all_combos.size();
	Hand testhand;
	std::vector<unsigned int> num_rankings(10,0);
	unsigned int hand_strength_ranking = 0;
	std::vector<std::vector<int>> straight_flush_hands;
	std::vector<int> target_combo = {0,1,2,3,4,8};
	for(unsigned int i=0;i<all_combos.size();i++){
		std::vector<int> temp_vec;
		std::set_intersection(all_combos[i].begin(),all_combos[i].end(),target_combo.begin(),target_combo.end(),
			std::back_inserter(temp_vec));
		if(temp_vec.size()==5){
			std::cout<<"6c7c8c9cAc running"<<std::endl;
		}
		testhand.add_cards(all_combos[i]);
		hand_strength_ranking = testhand.get_hand_strength();
		hand_strength_ranking = hand_strength_ranking >> 28;
		num_rankings[hand_strength_ranking-1]++;
		if(hand_strength_ranking == 9){
			std::vector<std::string> temp_card_strs = covert_card_index_to_card_str_vector(all_combos[i]);
			for(unsigned int j=0;j<temp_card_strs.size();j++){
				std::cout<<temp_card_strs[j];
			}
			std::cout<<std::endl;
			straight_flush_hands.push_back(all_combos[i]);
		}
		testhand.remove_cards(all_combos[i]);
	}
	std::cout<<"straight flush "<<straight_flush_hands.size()<<std::endl;
	return num_rankings;
} 
//test straight hand recognition 
void test_all_straights(){
	std::vector<std::vector<int>> straights = {{0,9,18,27},
												{1,10,19,28},
												{8,17,26,35},
												{2,11,20,29},
												{3,12,21,30}};
	std::vector<std::vector<int>> combos;
	for(int a=0;a<4;a++){
		for(int b=0;b<4;b++){
			for(int c=0;c<4;c++){
				for(int d=0;d<4;d++){
					for(int e=0;e<4;e++){
						std::vector<int> temp_combo;
						temp_combo.push_back(straights[0][a]);
						temp_combo.push_back(straights[1][b]);
						temp_combo.push_back(straights[2][c]);
						temp_combo.push_back(straights[3][d]);
						temp_combo.push_back(straights[4][e]);
						combos.push_back(temp_combo);
					}
				}
			}
		}
	}
	Hand testhand;
	unsigned int temp_hand_strength = 0;
	int counter = 0;
	for(unsigned int i=0;i<combos.size();i++){

		testhand.add_cards(combos[i]);
		temp_hand_strength = testhand.get_hand_strength();
		temp_hand_strength = temp_hand_strength >> 28;
		if(temp_hand_strength != 5 && temp_hand_strength != 9 && temp_hand_strength != 10){
			std::vector<std::string> temp_card_strs = std::move(covert_card_index_to_card_str_vector(combos[i]));
			for(unsigned int j=0;j<temp_card_strs.size();j++){
				std::cout<<temp_card_strs[j];
			}
			std::cout<<std::endl;
		}
		testhand.remove_cards(combos[i]);
		counter++;
	}
	std::cout<<"total count"<<counter<<std::endl;
}