from loadData import tableScores, tableMap
import itertools
import time

def find_combo(curr_combo,remaining_cards,offset,k):
	if k == 0:
		return [curr_combo]
		#result.append(curr_combo)
		#return
	result = []
	for i in range(offset,len(remaining_cards)-k+1):
		curr_combo.append(remaining_cards[i])
		result += find_combo(curr_combo,remaining_cards,i+1,k-1)
		curr_combo.pop()
	return result


def get_combos(list_of_known_cards,k):
	remaining_cards = []
	known_cards_set = set(list_of_known_cards)
	for i in range(36):
		if i not in known_cards_set:
			remaining_cards.append(i)
	#find all combos
	result = []
	#if not enough cards to form k cards combo
	if len(remaining_cards) < k:
		return result
	curr_combo = []
	result = find_combo(curr_combo,remaining_cards,0,k)
	return result

#convert a list of cards to unsigned long long int
def to_bit_string(list_of_cards):
	result = 0
	for card in list_of_cards:
		result += 1 << card
	return result
#given a bitstring of 7 cards, return hand strength int
def get_hand_strength(hand_bit_string):	
	if bin(hand_bit_string).count('1') != 7:
		print('Hand does not have 7 cards')
		return None
	return tableScores[tableMap[hand_bit_string]]
#get hand equity
def get_hand_equity(list_of_players,list_of_board_cards,list_of_dead_cards):
	list_of_known_cards = list_of_dead_cards + list_of_board_cards
	for list_of_player_cards in list_of_players:
		list_of_known_cards += list_of_player_cards
	list_of_all_combos = get_combos(list_of_known_cards,5-len(list_of_board_cards))
	#result is a list of doubles
	result = []
	winning_counts = [0.0] * len(list_of_players)

	known_cards_set = set(list_of_known_cards)
	deck = []
	for i in range(36):
		if i not in known_cards_set:
			deck.append(i)

	#for combo in list_of_all_combos:
	done = False
	for combo in itertools.combinations(deck,5-len(list_of_board_cards)):
		combo = list(combo)
		temp_hand_strengths = []
		for player in list_of_players:
			#print(player,combo,list_of_board_cards)
			#temp_hand_strengths.append(get_hand_strength(to_bit_string(player+combo+list_of_board_cards)))
			temp_hand_strengths.append(get_hand_strength(127))
			#temp_hand_strengths.append(0)
		curr_max = 0
		max_indices = []
		for i in range(len(temp_hand_strengths)):
			if curr_max < temp_hand_strengths[i]:
				curr_max = temp_hand_strengths[i]
				max_indices.clear()
				max_indices.append(i)
			elif curr_max == temp_hand_strengths[i]:
				max_indices.append(i)
			#if curr max is bigger than current value, does nothing
		for index in max_indices:
			winning_counts[index] += (1.0/len(max_indices))
	for winning_count in winning_counts:
		result.append(winning_count/len(list_of_all_combos))
	return result
#testings
def timeCall():
	start = time.time()
	get_hand_equity([[8,17],[7,16]],[0,1,2],[])
	timeTaken = time.time()-start
	print("Took", timeTaken, "seconds")

print(get_hand_equity([[8,17],[7,16]],[],[]))
print(get_hand_equity([[8,9],[7,16]],[],[]))



