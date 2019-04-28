#include "Hand.hpp"
#include "Helper.hpp"
#include "Test.hpp"

#include <unordered_map>
#include <iomanip>
#include <bitset>
#include <chrono>

int main(int argc, char *argv[]){
	//loading cached data
	std::unordered_map<unsigned long long int,unsigned int> score_table_trips;
	score_table_trips.reserve(calculate_num_combos(36,7)*10);
	read_cached_data_trips_version(score_table_trips);
	score_table_trips.rehash(calculate_num_combos(36,7)*10);

	std::unordered_map<unsigned long long int,unsigned int> score_table_straight;
	score_table_straight.reserve(calculate_num_combos(36,7)*10);
	read_cached_data_straight_version(score_table_straight);
	score_table_straight.rehash(calculate_num_combos(36,7)*10);
	//ready for input
	std::cout<<">"<<std::endl;
	for (std::string line; std::getline(std::cin, line);) {
        std::vector<std::string> inputs = splitString(line," ");
        if(inputs[0]=="handequity_trips"){
			std::vector<std::vector<int>> hole_cards;
	        std::vector<int> board;
	        std::vector<int> deadCards;
	        int num_hands = stoi(inputs[1]);
	        int num_board = stoi(inputs[2]);
	        int num_dead_cards = stoi(inputs[3]);
	        for(int i=0;i<num_hands;i++){
				int temp_card_index = 4+i*2;
				std::vector<int> hole_card;
				hole_card.push_back(stoi(inputs[temp_card_index]));
				temp_card_index++;
				hole_card.push_back(stoi(inputs[temp_card_index]));
				hole_cards.push_back(hole_card);
			}
			for(int i=0;i<num_board;i++){
				int board_index = 2*num_hands+4+i;
				board.push_back(stoi(inputs[board_index]));

			}
			for(int i = 0;i<num_dead_cards;i++){
				int deadCard_index = 4+2*num_hands+num_board+i;
				deadCards.push_back(stoi(inputs[deadCard_index]));

			}
            std::vector<int> known_cards;
            known_cards.push_back(hole_cards[0][0]);
            known_cards.push_back(hole_cards[0][1]);
            known_cards.push_back(hole_cards[1][0]);
            known_cards.push_back(hole_cards[1][1]);

            std::vector<std::vector<int>> board_combos = get_combos(known_cards,3);
            //unsigned int num_combos = board_combos.size();

            int buckets[10] = {0};
            for(const auto& board_combo : board_combos){
	           std::vector<double> equities = get_hands_equity(hole_cards,board_combo,deadCards,score_table_straight);
               int bucket = (int)(equities[0]*10);
               if (bucket == 10) bucket = 9;
               buckets[bucket]++;
            }

	        for(const auto bucket : buckets){
	        	std::cout<<bucket<<" ";
	        }
	        std::cout<<std::endl;
	        std::cout<<">"<<std::endl;
        }else if(inputs[0]=="rangeequity_trips"){
        	int num_players = stoi(inputs[1]);
        	int num_combos = stoi(inputs[2]);
        	int num_board = stoi(inputs[3]);
        	int num_dead_cards = stoi(inputs[4]);
        	std::vector<std::vector<std::vector<int>>> hole_cards_combos;
        	std::vector<int> board;
	        std::vector<int> deadCards;
	        for(int comboIndex = 0;comboIndex<num_combos;comboIndex++){
		        std::vector<std::vector<int>> hole_cards;
		        for(int i=0;i<num_players;i++){
					int temp_card_index = 5+i*2+comboIndex*2*num_players;
					std::vector<int> hole_card;
					hole_card.push_back(stoi(inputs[temp_card_index]));
					temp_card_index++;
					hole_card.push_back(stoi(inputs[temp_card_index]));
					hole_cards.push_back(hole_card);
				}
				hole_cards_combos.push_back(hole_cards);
			}	
			for(int i=0;i<num_board;i++){
				int board_index = 2*num_combos*num_players+5+i;
				board.push_back(stoi(inputs[board_index]));

			}
			for(int i = 0;i<num_dead_cards;i++){
				int deadCard_index = 5+2*num_combos*num_players+num_board+i;
				deadCards.push_back(stoi(inputs[deadCard_index]));

			}
			std::vector<double> equities(num_players,0.0);
			for(int i = 0;i<num_combos;i++){
				std::vector<double> curr_equities = get_hands_equity(hole_cards_combos[i],board,deadCards,score_table_trips);
				for(int j=0;j<num_players;j++){
					equities[j] += curr_equities[j];
				}
			}
			for(int i=0;i<num_players;i++){
				equities[i] = equities[i]/(double)num_combos;
				std::cout<<equities[i]<<" ";
			}
			std::cout<<std::endl;
	        std::cout<<">"<<std::endl;
        }else if(inputs[0]=="montecarlorangeequity_trips"){
        	int num_players = stoi(inputs[1]);
        	int num_board = stoi(inputs[2]);
        	int num_dead_cards = stoi(inputs[3]);
        	std::vector<int> num_player_hands(num_players,0);
        	for(int i=0;i<num_players;i++){
        		num_player_hands[i] = stoi(inputs[i+4]);
        	}
        	std::vector<std::vector<std::vector<int>>> player_hands;
        	for(int i=0;i<num_players;i++){
        		player_hands.push_back(std::vector<std::vector<int>>(num_player_hands[i],{0,0}));
        	}
        	int inputIndex = 3+num_players+1;
        	for(int i=0;i<num_players;i++){
        		for(int j=0;j<num_player_hands[i];j++){
        			player_hands[i][j][0] = stoi(inputs[inputIndex]);
        			inputIndex++;
        			player_hands[i][j][1] = stoi(inputs[inputIndex]);
        			inputIndex++;
        		}
        	}
        	std::vector<int> board;
        	for(int i=0;i<num_board;i++){
        		board.push_back(stoi(inputs[inputIndex]));
        		inputIndex++;
        	}
        	std::vector<int> deadCards;
        	for(int i=0;i<num_dead_cards;i++){
        		deadCards.push_back(stoi(inputs[inputIndex]));
        		inputIndex++;
        	}
    		std::vector<double> equities = get_monte_carlo_range_equity(player_hands,board,deadCards,score_table_trips);
			for(int i=0;i<num_players;i++){
				std::cout<<equities[i]<<" ";
			}
			std::cout<<std::endl;
	        std::cout<<">"<<std::endl;
        }else if(inputs[0]=="handequity_straight"){
			std::vector<std::vector<int>> hole_cards;
	        std::vector<int> board;
	        std::vector<int> deadCards;
	        int num_hands = stoi(inputs[1]);
	        int num_board = stoi(inputs[2]);
	        int num_dead_cards = stoi(inputs[3]);
	        for(int i=0;i<num_hands;i++){
				int temp_card_index = 4+i*2;
				std::vector<int> hole_card;
				hole_card.push_back(stoi(inputs[temp_card_index]));
				temp_card_index++;
				hole_card.push_back(stoi(inputs[temp_card_index]));
				hole_cards.push_back(hole_card);
			}
			for(int i=0;i<num_board;i++){
				int board_index = 2*num_hands+4+i;
				board.push_back(stoi(inputs[board_index]));

			}
			for(int i = 0;i<num_dead_cards;i++){
				int deadCard_index = 4+2*num_hands+num_board+i;
				deadCards.push_back(stoi(inputs[deadCard_index]));

			}
	        std::vector<double> equities = get_hands_equity(hole_cards,board,deadCards,score_table_straight);
	        for(const auto equity : equities){
	        	std::cout<<equity<<" ";
	        }
	        std::cout<<std::endl;
	        std::cout<<">"<<std::endl;
        }else if(inputs[0]=="rangeequity_straight"){
        	int num_players = stoi(inputs[1]);
        	int num_combos = stoi(inputs[2]);
        	int num_board = stoi(inputs[3]);
        	int num_dead_cards = stoi(inputs[4]);
        	std::vector<std::vector<std::vector<int>>> hole_cards_combos;
        	std::vector<int> board;
	        std::vector<int> deadCards;
	        for(int comboIndex = 0;comboIndex<num_combos;comboIndex++){
		        std::vector<std::vector<int>> hole_cards;
		        for(int i=0;i<num_players;i++){
					int temp_card_index = 5+i*2+comboIndex*2*num_players;
					std::vector<int> hole_card;
					hole_card.push_back(stoi(inputs[temp_card_index]));
					temp_card_index++;
					hole_card.push_back(stoi(inputs[temp_card_index]));
					hole_cards.push_back(hole_card);
				}
				hole_cards_combos.push_back(hole_cards);
			}	
			for(int i=0;i<num_board;i++){
				int board_index = 2*num_combos*num_players+5+i;
				board.push_back(stoi(inputs[board_index]));

			}
			for(int i = 0;i<num_dead_cards;i++){
				int deadCard_index = 5+2*num_combos*num_players+num_board+i;
				deadCards.push_back(stoi(inputs[deadCard_index]));

			}
			std::vector<double> equities(num_players,0.0);
			for(int i = 0;i<num_combos;i++){
				std::vector<double> curr_equities = get_hands_equity(hole_cards_combos[i],board,deadCards,score_table_straight);
				for(int j=0;j<num_players;j++){
					equities[j] += curr_equities[j];
				}
			}
			for(int i=0;i<num_players;i++){
				equities[i] = equities[i]/(double)num_combos;
				std::cout<<equities[i]<<" ";
			}
			std::cout<<std::endl;
	        std::cout<<">"<<std::endl;
        }else if(inputs[0]=="montecarlorangeequity_straight"){
        	int num_players = stoi(inputs[1]);
        	int num_board = stoi(inputs[2]);
        	int num_dead_cards = stoi(inputs[3]);
        	std::vector<int> num_player_hands(num_players,0);
        	for(int i=0;i<num_players;i++){
        		num_player_hands[i] = stoi(inputs[i+4]);
        	}
        	std::vector<std::vector<std::vector<int>>> player_hands;
        	for(int i=0;i<num_players;i++){
        		player_hands.push_back(std::vector<std::vector<int>>(num_player_hands[i],{0,0}));
        	}
        	int inputIndex = 3+num_players+1;
        	for(int i=0;i<num_players;i++){
        		for(int j=0;j<num_player_hands[i];j++){
        			player_hands[i][j][0] = stoi(inputs[inputIndex]);
        			inputIndex++;
        			player_hands[i][j][1] = stoi(inputs[inputIndex]);
        			inputIndex++;
        		}
        	}
        	std::vector<int> board;
        	for(int i=0;i<num_board;i++){
        		board.push_back(stoi(inputs[inputIndex]));
        		inputIndex++;
        	}
        	std::vector<int> deadCards;
        	for(int i=0;i<num_dead_cards;i++){
        		deadCards.push_back(stoi(inputs[inputIndex]));
        		inputIndex++;
        	}
    		std::vector<double> equities = get_monte_carlo_range_equity(player_hands,board,deadCards,score_table_straight);
			for(int i=0;i<num_players;i++){
				std::cout<<equities[i]<<" ";
			}
			std::cout<<std::endl;
	        std::cout<<">"<<std::endl;
	    }
        
    }
    return 0;

}
