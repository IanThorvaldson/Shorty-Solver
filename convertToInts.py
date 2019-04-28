class FormatError(Exception):
    pass

def convertToInts(string, language):
    string = string.replace('t', 'T')
    string = string.replace('j', 'J')
    string = string.replace('q', 'Q')
    string = string.replace('k', 'K')
    string = string.replace('a', 'A')
    if language == 'chinese':
        message = '手牌使用的错误的格式，请使用标准的手牌格式，如”AcAh”'
    else:
        message = 'Hand was in the wrong format, please use the form "AcAh" as per usual poker convention.'

    if len(string) % 2 == 1:
        raise FormatError(message)

    cards = []
    for i in range(len(string)//2):
        value = '6789TJQKA'.find(string[i*2])
        if value == -1:
            if language == 'chinese':
                raise FormatError('请用\"AKQJT9876\"来表示牌')
            else:
                raise FormatError("Please use cards from \"AKQJT9876\"")

        suit = 'cdhs'.find(string[i*2+1])
        if suit == -1:
            if language == 'chinese':
                raise FormatError('请使用 \"cdhs\"来表示花色')
            else:
                raise FormatError("Please use suits from \"cdhs\"")

        intVal = suit*9+value
        cards.append(intVal)
    return cards

def noDupes(deads, board, players, language):
    if language == 'chinese':
        message = '发现重复的卡牌，每张牌只可以出现一次'
    else:
        message = 'Duplicate values were found. Every card you specify should be unique!'
    #print(deads, board, players)

    s = set()

    for i in deads:
        if i in s:
            raise FormatError(message)
        s.add(i)

    for i in board:
        if i in s:
            raise FormatError(message)
        s.add(i)

    for player in players:
        for i in player:
            if i in s:
                raise FormatError(message)
            #print(s)
            s.add(i)
    return True


def correctLengths(deads, board, players, language):
    if len(board) > 5:
        if language == 'chinese':
            raise FormatError('公共牌面最多包含5张牌')
        else:
            raise FormatError("Board can have at most 5 cards.")

    for i in players:
        if len(i) != 2:
            #print('E',i)
            if language == 'chinese':
                raise FormatError('手牌需要包含2张牌')
            else:
                raise FormatError("Hands need 2 cards exactly!")

    if len(deads) > 36 - (5-len(board)) - 2*len(players):
        if language == 'chinese':
            raise FormatError('您设置了太多已知的死牌')
        else:
            raise FormatError("You have too many dead cards")

'''
def convertHand(hand):
    if hand[0] == hand[1] and hand[0] in '6789TJQKA':
        cardNum = '6789TJQKA'.find(hand[0])
        return  [cardNum, cardNum+9]

    elif hand[0] in '6789TJQKA' and hand[1] in '6789TJQKA':
        if hand[2] == 'o':
            cardNum1 = '6789TJQKA'.find(hand[0])
            cardNum2 = '6789TJQKA'.find(hand[0]) + 9
            return  [cardNum1, cardNum2]
        elif hand[2] == 's':
            cardNum1 = '6789TJQKA'.find(hand[0])
            cardNum2 = '6789TJQKA'.find(hand[0]) + 9
            return  [cardNum1, cardNum2]
        else:
            raise FormatError("Hand was somehow in an incorrect format - don't mess with my HTML.")
    else:
        raise FormatError("Hand was somehow in an incorrect format - don't mess with my HTML.")
'''