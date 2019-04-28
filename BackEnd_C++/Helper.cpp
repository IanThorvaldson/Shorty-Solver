#include "Helper.hpp"

//calculate the number of combinations give n and k
unsigned long long int
calculate_num_combos(unsigned long long int n, unsigned long long int k) {
	if (n <= 35 && k <= 6){
		std::vector<int> v = {1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,2,1,0,0,0,0,1,3,3,1,0,0,0,1,4,6,4,1,0,0,1,5,10,10,5,1,0,1,6,15,20,15,6,1,1,7,21,35,35,21,7,1,8,28,56,70,56,28,1,9,36,84,126,126,84,1,10,45,120,210,252,210,1,11,55,165,330,462,462,1,12,66,220,495,792,924,1,13,78,286,715,1287,1716,1,14,91,364,1001,2002,3003,1,15,105,455,1365,3003,5005,1,16,120,560,1820,4368,8008,1,17,136,680,2380,6188,12376,1,18,153,816,3060,8568,18564,1,19,171,969,3876,11628,27132,1,20,190,1140,4845,15504,38760,1,21,210,1330,5985,20349,54264,1,22,231,1540,7315,26334,74613,1,23,253,1771,8855,33649,100947,1,24,276,2024,10626,42504,134596,1,25,300,2300,12650,53130,177100,1,26,325,2600,14950,65780,230230,1,27,351,2925,17550,80730,296010,1,28,378,3276,20475,98280,376740,1,29,406,3654,23751,118755,475020,1,30,435,4060,27405,142506,593775,1,31,465,4495,31465,169911,736281,1,32,496,4960,35960,201376,906192,1,33,528,5456,40920,237336,1107568,1,34,561,5984,46376,278256,1344904,1,35,595,6545,52360,324632,1623160};
	    return v[n*7+k];
	}
    if (k > n) {
        return 0;
    }
    unsigned long long int r = 1;
    for (unsigned long long int d = 1; d <= k; ++d) {
        r *= n--;
        r /= d;
    }
    return r;
}
unsigned long long int get_hash(unsigned long long int bitString){
	unsigned long long int mask = 1;
	int ones = 0;
	unsigned long long int hash = 0;
	for (int i = 0; i < 36; i++) {
		if (bitString & mask) {
			ones++;
			if (ones == 7) break;
		} else {
			hash += calculate_num_combos(35 - i, 6 - ones);
		}
		mask = mask << 1;
	}
	return hash;
}

void find_combo(std::vector<std::vector<int>>& result,std::vector<int>& combo,
	const std::vector<int>& remaining_cards,int offset,int k){
	if(k==0){
		result.push_back(combo);
		return;
	}
	for(int i=offset;i<=(int)remaining_cards.size()-k;++i){
		combo.push_back(remaining_cards[i]);
		find_combo(result,combo,remaining_cards,i+1,k-1);
		combo.pop_back();
	}
}

//get a vector of known cards and number of elements k
//return a vector of vectors of cards
std::vector<std::vector<int>> get_combos(const std::vector<int>& known_cards,int k){
	//get remaining cards
	std::vector<int> remaining_cards;
	std::set<int> s(known_cards.begin(),known_cards.end());
	for(int i=0;i<36;i++){
		//if i is not in set,then added element into reminding cards
		if(!s.count(i)){
			remaining_cards.push_back(i);
		}
	}
	//find all combos
	std::vector<std::vector<int>> result;
	//if not enough cards to form k element combo, return empyt vector
	if(remaining_cards.size() < (unsigned int)k){
		return result;
	}
	//pre reserve space for huge vector
	//maybe try not to reserve

	// long long int pre_size = calculate_num_combos(remaining_cards.size(),k);
	// result.reserve(pre_size);
	std::vector<int> curr_combo;
	find_combo(result,curr_combo,remaining_cards,0,k);
	return result;
}

//covert string representation to card index from 0-35
int covert_card_str_to_card_index(const std::string& card_str){
	// if string is not the correct length,
	//return invalid index
	if(card_str.length()!= 2){
		return -1;
	}
	int suit_index = -1;
	int rank_index = -1;
	//find suit
	if(card_str[1]=='c'){
		suit_index = 0;
	}else if(card_str[1]=='d'){
		suit_index = 1;
	}else if(card_str[1]=='h'){
		suit_index = 2;
	}else if(card_str[1]=='s'){
		suit_index = 3;
	}
	//find rank
	if(card_str[0]=='6'){
		rank_index = 0;
	}else if(card_str[0]=='7'){
		rank_index = 1;
	}else if(card_str[0]=='8'){
		rank_index = 2;
	}else if(card_str[0]=='9'){
		rank_index = 3;
	}else if(card_str[0]=='T'){
		rank_index = 4;
	}else if(card_str[0]=='J'){
		rank_index = 5;
	}else if(card_str[0]=='Q'){
		rank_index = 6;
	}else if(card_str[0]=='K'){
		rank_index = 7;
	}else if(card_str[0]=='A'){
		rank_index = 8;
	}

	//if card_str is invalid, return -1 for index
	if(suit_index == -1 || rank_index == -1){
		return -1;
	}
	int result = 9*suit_index + rank_index;
	return result;
}

//covert card index from 0-35 to string representation 
std::string covert_card_index_to_card_str(const int card_index){
	//make sure index is valid
	if(card_index > 35 || card_index < 0){
		return "NA";
	}
	int suit_index = card_index / 9;
	int rank_index = card_index % 9;
	std::string result;
	char first = 0;
	char second = 0;
	if(rank_index==0){
		first = '6';
	}else if(rank_index==1){
		first = '7';
	}else if(rank_index==2){
		first = '8';
	}else if(rank_index==3){
		first = '9';
	}else if(rank_index==4){
		first = 'T';
	}else if(rank_index==5){
		first = 'J';
	}else if(rank_index==6){
		first = 'Q';
	}else if(rank_index==7){
		first = 'K';
	}else if(rank_index==8){
		first = 'A';
	}
	result.push_back(first);
	if(suit_index==0){
		second = 'c';
	}else if(suit_index==1){
		second = 'd';
	}else if(suit_index==2){
		second = 'h';
	}else if(suit_index==3){
		second = 's';
	}
	result.push_back(second);
	return result;
}

//vector version of conversion
std::vector<int> covert_card_str_to_card_index_vector(const std::vector<std::string>& card_strs){
	std::vector<int> result;
	for(auto const& card_str:card_strs){
		result.push_back(covert_card_str_to_card_index(card_str));
	}
	return result;
}
std::vector<std::string> covert_card_index_to_card_str_vector(const std::vector<int>& card_indices){
	std::vector<std::string> result;
	for(auto const& card_index:card_indices){
		result.push_back((covert_card_index_to_card_str(card_index)));
	}
	return result;
}
std::string covert_card_index_to_single_card_str(const std::vector<int>& card_indices){
	std::string result;
	for(auto const& card_index:card_indices){
		result += covert_card_index_to_card_str(card_index);
	}
	return result;
}

unsigned long long int covert_card_index_to_bits(const std::vector<int>& card_indices){
	unsigned long long int result = 0;
	for(auto const& card_index:card_indices){
		result += (1ll<<card_index);
	}
	return result;
}

//calculate equity of hands
std::vector<double> get_hands_equity
	(const std::vector<std::vector<int>>& hole_cards,
		const std::vector<int>& board,const std::vector<int>& deadCards){

	//vector of winning and drawing times of each hand
	std::vector<std::vector<int>> outputs(hole_cards.size(),std::vector<int>(2,0));
	std::vector<double> result(hole_cards.size(),0);
	//get a vector to count the winning times of each hand
	//since sometime hands can have same hand strength and all win
	//we use float to count the total number of winnings
	std::vector<float> winning_counts(hole_cards.size(),0);
	//add all known cards together
	std::vector<int> known_cards = board;
	known_cards.insert(known_cards.end(),deadCards.begin(),deadCards.end());
	//create a vector of Hand objects for hand strength
	std::vector<Hand> input_hands;
	//add cards in hand into known_cards vector
	for(const auto& hole_card : hole_cards){
		known_cards.insert(known_cards.end(),hole_card.begin(),hole_card.end());
		input_hands.push_back(Hand(hole_card));
	}
	//if board is not empty,add board cards to hands
	if(board.size() != 0){
		for(unsigned int i=0;i<input_hands.size();i++){
			input_hands[i].add_cards(board);
		}
	}
	std::vector<std::vector<int>> board_combos = get_combos(known_cards,5-board.size());
	unsigned int num_combos = board_combos.size();
	//find best hand for each combo
	//and update winning_counts
	for(const auto& board_combo : board_combos){
		//update hand strength
		std::vector<unsigned int> hand_strength_vec(input_hands.size(),0);
		for(unsigned int i=0;i<input_hands.size();i++){
			input_hands[i].add_cards(board_combo);
			hand_strength_vec[i] = input_hands[i].get_hand_strength();
			input_hands[i].remove_cards(board_combo);
		}
		std::vector<int> max_element_indices;
		unsigned int curr_max = 0;
		for(unsigned int i=0;i<hand_strength_vec.size();i++){
			if(curr_max==hand_strength_vec[i]){
				max_element_indices.push_back(i);
			}else if(curr_max < hand_strength_vec[i]){
				max_element_indices.clear();
				max_element_indices.push_back(i);
				curr_max = hand_strength_vec[i];
			}else{
				//if curr_max is larger than i hand strength do nothing
			}
		}
		//increment output vector
		if(max_element_indices.size()==1){
			outputs[max_element_indices[0]][0]++;
		}else{
			for(unsigned int i=0;i<max_element_indices.size();i++){
				outputs[max_element_indices[i]][1]++;
			}
		}

		//increment winning counts properly 
		float increment = (float)1/(float)max_element_indices.size();
		for(unsigned int i=0;i<max_element_indices.size();i++){
			winning_counts[max_element_indices[i]] += increment;
		}
	}
	for(unsigned int i=0;i<winning_counts.size();i++){
		result[i] = winning_counts[i]/(double)num_combos;
	}
	//print out outputs vector
	// for(unsigned int i=0;i<hole_cards.size();i++){
	// 	std::cout<<"Hand "<<i<<" wins:"<<outputs[i][0]<<" times"
	// 	<<" and draws"<<outputs[i][1]<<" times"<<std::endl;
	// }
	return result;
}

//TODO
//for this function, all suited combos are treated the same and all the offsuit combos are the same
//for example, JhTh == JsTs, AhAd == AsAc
// std::vector<std::vector<int>> get_all_starting_hands(){
// 	std::vector<int> result = {
// 		//all pairs
// 		{0,9},{1,10},{2,11},{3,12},{4,13},{5,14},{6,15},{7,16},{8,17},
		


// 								}


// 	return result;
// }


void get_all_starting_hands_equity_against_all_combos_in_heads_up_pot(int firstCard,int secondCard){
	//get the ranking
	std::vector<std::vector<int>> all_combos = get_combos({},2);
	//std::vector<std::vector<int>> all_starting_hands = get_all_starting_hands();
	std::vector<int> testing_combo;
	testing_combo.push_back(firstCard);
	testing_combo.push_back(secondCard);
	double result = 0;
	double coefficent = 1.0/630;
	for(unsigned int i=0;i<all_combos.size();i++){
		//std::cout<<i<<" testing"<<std::endl;
		std::vector<std::vector<int>> hole_cards;
		hole_cards.push_back(testing_combo);
		hole_cards.push_back(all_combos[i]);
		double temp_equity = get_hands_equity(hole_cards,{},{})[0];
		result += coefficent * temp_equity;
		//std::cout<<"temp_equity is "<<temp_equity<<std::endl;
	}
	std::cout<<firstCard<<" "<<secondCard<<" "<<"final result is"<<result<<std::endl;
	return;
}



std::vector<std::string> splitString(const std::string& inputStr,const std::string& delimiter=" "){
    std::vector<std::string> result;
    if(inputStr.length()==0){
        return result;
    }
    size_t pos = 0;
    std::string token;
    std::string s = inputStr;
    while((pos = s.find(delimiter))!= std::string::npos){
        token = s.substr(0,pos);
        result.push_back(token);
        s.erase(0,pos+delimiter.length());
    }
    return result;
}    


//cache functions
void output_starting_hand_indices(){
	//no known cards and choose 2 from all 36 cards
	//630 combos in total
	std::vector<std::vector<int>> all_starting_hands = get_combos({},2);
	//get output_file ready
	std::ofstream myfile;
	myfile.open ("starting_hand_indices.txt");
	for(unsigned int i = 0;i<all_starting_hands.size();i++){
		myfile<<covert_card_index_to_single_card_str(all_starting_hands[i])<<" "<<covert_card_index_to_bits(all_starting_hands[i])<<" "<<i<<std::endl;
	}
	myfile.close();
	return;
}
void output_board_indices(){
	std::vector<std::vector<int>> all_boards = get_combos({},5);
	//get output_file ready
	std::ofstream myfile;
	myfile.open ("board_indices.txt");
	//myfile.open ("board_indices.dat", std::ios::out | std::ios::binary);
	for(unsigned int i = 0;i<all_boards.size();i++){
		/*unsigned long long temp_board = covert_card_index_to_bits(all_boards[i]);
		myfile.write((char*) &temp_board, sizeof(unsigned long long));
		myfile.write((char*) &i, sizeof(unsigned int));*/
		myfile<<covert_card_index_to_single_card_str(all_boards[i])<<" "<<covert_card_index_to_bits(all_boards[i])<<" "<<i<<std::endl;
	}
	myfile.close();
	return;
}
void output_hand_strength_matrix(){
	std::vector<std::vector<int>> all_starting_hands = get_combos({},2);
	std::vector<std::vector<int>> all_boards = get_combos({},5);
	Hand score_hand;
	std::ofstream myfile;
	myfile.open ("hand_strength_matrix.txt");
	for(unsigned int i=0;i<all_starting_hands.size();i++){
		std::cout<<"working on "<<i<<"th"<<std::endl;
		score_hand.add_cards(all_starting_hands[i]);
		std::cout<<"starting hand is added"<<std::endl;
		unsigned long long int starting_hand_bits = covert_card_index_to_bits(all_starting_hands[i]);
		for(unsigned int j=0;j<all_boards.size();j++){
			unsigned long long int board_bits = covert_card_index_to_bits(all_boards[j]);
			if((starting_hand_bits & board_bits)==0){
				score_hand.add_cards(all_boards[j]);
				myfile<<score_hand.get_hand_strength()<<" ";
				score_hand.remove_cards(all_boards[j]);
			}else{
				myfile<<0<<" ";
			}
		}
		score_hand.remove_cards(all_starting_hands[i]);
		myfile<<std::endl;
	}
	myfile.close();
	return;
}
void output_hand_strength_vector(){
	Hand score_hand;
	std::vector<std::vector<int>> all_combos = get_combos({},7);
	std::ofstream myfile;
	myfile.open ("hand_strength_vec_data_simple_straight_beats_trips.txt");
	for(unsigned int i=0;i<all_combos.size();i++){
		std::cout<<"working on "<<i<<std::endl;
		score_hand.add_cards(all_combos[i]);
		myfile<<covert_card_index_to_bits(all_combos[i])<<" ";
		myfile<<i<<" ";
		myfile<<score_hand.get_hand_strength()<<std::endl;
		score_hand.remove_cards(all_combos[i]);
	}
	myfile.close();
	return;
}
void read_cached_data_trips_version(std::unordered_map<unsigned long long int,unsigned int>& score_table_trips){
	std::ifstream infile("hand_strength_vec_data_simple_trips_beats_straight.txt");
	unsigned long long int a;
	unsigned int b;
	unsigned int c;
	while (infile >> a >> b >> c)
	{
	    score_table_trips[a] = c;
	}
}
void read_cached_data_straight_version(std::unordered_map<unsigned long long int,unsigned int>& score_table_straight){
	std::ifstream infile("hand_strength_vec_data_simple_straight_beats_trips.txt");
	unsigned long long int a;
	unsigned int b;
	unsigned int c;
	while (infile >> a >> b >> c)
	{
	    score_table_straight[a] = c;
	}
}


void read_cached_data_flop_dist_trips_version(std::unordered_map<unsigned long long int,std::unordered_map<unsigned long long int,std::vector<unsigned int>>>& flop_dist){
	std::ifstream infile("flop_distribution_trips_beats_straight.txt");
	unsigned long long int a;
	unsigned long long int b;
	unsigned int dist1;
	unsigned int dist2;
	unsigned int dist3;
	unsigned int dist4;
	unsigned int dist5;
	unsigned int dist6;
	unsigned int dist7;
	unsigned int dist8;
	unsigned int dist9;
	unsigned int dist10;
	while(infile >> a >> b >> dist1>>dist2>>dist3>>dist4>>dist5>>dist6>>dist7>>dist8>>dist9>>dist10){
		std::vector<unsigned int> tempVec{dist1,dist2,dist3,dist4,dist5,dist6,dist7,dist8,dist9,dist10};
		if ( flop_dist.find(a) == flop_dist.end() ) {
  			// not found
  			flop_dist[a] = std::unordered_map<unsigned long long int,std::vector<unsigned int>>();
  			flop_dist[a][b] = tempVec;
		} else {
			flop_dist[a][b] = tempVec;
		}
	}
}



void read_cached_data_flop_dist_straight_version(std::unordered_map<unsigned long long int,std::unordered_map<unsigned long long int,std::vector<unsigned int>>>& flop_dist){
	std::ifstream infile("flop_distribution_straight_beats_trips.txt");
	unsigned long long int a;
	unsigned long long int b;
	unsigned int dist1;
	unsigned int dist2;
	unsigned int dist3;
	unsigned int dist4;
	unsigned int dist5;
	unsigned int dist6;
	unsigned int dist7;
	unsigned int dist8;
	unsigned int dist9;
	unsigned int dist10;
	while(infile >> a >> b >> dist1>>dist2>>dist3>>dist4>>dist5>>dist6>>dist7>>dist8>>dist9>>dist10){
		std::vector<unsigned int> tempVec{dist1,dist2,dist3,dist4,dist5,dist6,dist7,dist8,dist9,dist10};
		if ( flop_dist.find(a) == flop_dist.end() ) {
  			// not found
  			flop_dist[a] = std::unordered_map<unsigned long long int,std::vector<unsigned int>>();
  			flop_dist[a][b] = tempVec;
		} else {
			flop_dist[a][b] = tempVec;
		}
	}
}

void read_cached_data_own_hash(unsigned int *score_table){
	std::ifstream infile("hand_strength_vec_data_simple.txt");
	unsigned long long int a;
	unsigned int b;
	unsigned int c;
	while (infile >> a >> b >> c)
	{
	    score_table[get_hash(a)] = c;
	}
	std::cout<<">"<<std::endl;
}

std::vector<double> get_hands_equity
	(const std::vector<std::vector<int>>& hole_cards,
		const std::vector<int>& board,const std::vector<int>& deadCards,
		const std::unordered_map<unsigned long long int,unsigned int>& score_table){
	
	std::vector<int> known_cards;
	known_cards.insert(known_cards.end(),board.begin(),board.end());
	known_cards.insert(known_cards.end(),deadCards.begin(),deadCards.end());
	for(const auto hole_card : hole_cards){
		known_cards.insert(known_cards.end(),hole_card.begin(),hole_card.end());
	}
	std::vector<std::vector<int>> all_combos = get_combos(known_cards,5-board.size());
	std::vector<double> result;
	std::vector<double> winning_counts(hole_cards.size(),0.0);
	for(const auto combo : all_combos){
		std::vector<unsigned int> temp_hand_strengths;
		for(const auto player : hole_cards){
			std::vector<int> currCards;
			currCards.insert(currCards.end(),player.begin(),player.end());
			currCards.insert(currCards.end(),combo.begin(),combo.end());
			currCards.insert(currCards.end(),board.begin(),board.end());
			unsigned long long int currBitString = covert_card_index_to_bits(currCards);
			unsigned int currHandStrength = score_table.find(currBitString)->second;
			temp_hand_strengths.push_back(currHandStrength);
		}
		unsigned int curr_max = 0;
		std::vector<unsigned int> max_indices;
		for(unsigned int i=0;i<temp_hand_strengths.size();i++){
			if(curr_max < temp_hand_strengths[i]){
				curr_max = temp_hand_strengths[i];
				max_indices.clear();
				max_indices.push_back(i);
			}else if(curr_max == temp_hand_strengths[i]){
				max_indices.push_back(i);
			}
		}
		for(const auto index : max_indices){
			winning_counts[index] += (1.0/(double)max_indices.size());
		}
	}
	for(const auto winning_count : winning_counts){
		result.push_back(winning_count/(double)all_combos.size());
	}
	return result;
}

std::vector<double> get_monte_carlo_range_equity
	(const std::vector<std::vector<std::vector<int>>> player_hands,
		const std::vector<int>& board,const std::vector<int>& deadCards,
		const std::unordered_map<unsigned long long int,unsigned int>& score_table){


	std::vector<double> result(player_hands.size(),0.0);
	//number of simulations for monte carlo
	int total_simulations = 100000;
	int actual_simulations = 0;
	std::vector<double> winning_counts(player_hands.size(),0.0);
	std::default_random_engine generator;

	for(int k=0;k<total_simulations;k++){
		std::unordered_set<int> known_cards(board.begin(),board.end());
		std::vector<std::vector<int>> hole_cards(player_hands.size(),{0,0});
		for(unsigned int i=0;i<deadCards.size();i++){
			known_cards.insert(deadCards[i]);
		}
		std::uniform_int_distribution<int> first_distribution(0,player_hands[0].size()-1);
		int tempIndexFirstPlayer = first_distribution(generator);
		hole_cards[0] = player_hands[0][tempIndexFirstPlayer];
		known_cards.insert(hole_cards[0][0]);
		known_cards.insert(hole_cards[0][1]);
		//find all the other hands
		bool found_hand = false;
		for(unsigned int i=1;i<player_hands.size();i++){
			found_hand = false;
			int num_trials = 0;
			std::uniform_int_distribution<int> temp_distribution(0,player_hands[i].size()-1);
			while(found_hand == false && num_trials < 100){
				int tempIndex = temp_distribution(generator);
				if(known_cards.count(player_hands[i][tempIndex][0])==0&&
					known_cards.count(player_hands[i][tempIndex][1])==0){
					hole_cards[i] = player_hands[i][tempIndex];
					known_cards.insert(player_hands[i][tempIndex][0]);
					known_cards.insert(player_hands[i][tempIndex][1]);
					found_hand = true;
				}
				num_trials++;
			}
			if(found_hand == false){
				break;
			}
		}
		if(found_hand == false){
			continue;
		}
		//if hold cards are all founded, then find board
		std::uniform_int_distribution<int> board_distribution(0,35);
		std::vector<int> remaining_board(5-board.size(),-1);
		unsigned int found_remaining_board = 0;
		while(found_remaining_board < remaining_board.size()){
			int tempCard = board_distribution(generator);
			if(known_cards.count(tempCard)==0){
				remaining_board[found_remaining_board] = tempCard;
				found_remaining_board++;
				known_cards.insert(tempCard);
			}
		}
		std::vector<int> complete_board;
		complete_board.insert(complete_board.end(),board.begin(),board.end());
		complete_board.insert(complete_board.end(),remaining_board.begin(),remaining_board.end());
		std::vector<unsigned int> hand_strength_vec(player_hands.size(),0);
		for(unsigned int i = 0;i<player_hands.size();i++){
			std::vector<int> currCards;
			currCards.insert(currCards.end(),complete_board.begin(),complete_board.end());
			currCards.insert(currCards.end(),hole_cards[i].begin(),hole_cards[i].end());
			unsigned long long int currBitString = covert_card_index_to_bits(currCards);
			hand_strength_vec[i] = score_table.find(currBitString)->second;
		}

		unsigned int curr_max = 0;
		std::vector<unsigned int> max_indices;
		for(unsigned int i=0;i<hand_strength_vec.size();i++){
			if(curr_max < hand_strength_vec[i]){
				curr_max = hand_strength_vec[i];
				max_indices.clear();
				max_indices.push_back(i);
			}else if(curr_max == hand_strength_vec[i]){
				max_indices.push_back(i);
			}
		}
		for(const auto index : max_indices){
			winning_counts[index] += (1.0/(double)max_indices.size());
		}
		actual_simulations++;
	}
	//if no simulation has been conducted, then we have to return a vector of zero
	if(actual_simulations != 0){
		for(unsigned int i =0;i<player_hands.size();i++){
			result[i] = winning_counts[i]/(double)actual_simulations;
		}
	}
	std::cout<<actual_simulations<<" ";
	return result;

}