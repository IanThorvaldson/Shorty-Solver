from convertToInts import FormatError

def verifyMonteCarlo(deads, board, players, language):
    #correctLengths
    if len(board) > 5:
        if language == 'chinese':
            raise FormatError('公共牌面最多包含5张牌')
        else:
            raise FormatError("Board can have at most 5 cards.")

    for i in players:
        for j in i:
            if len(j) != 2:
                if language == 'chinese':
                    raise FormatError('手牌需要包含2张牌')
                else:
                    raise FormatError("Hands need 2 cards exactly!")

    if len(deads) > 36 - (5-len(board)) - 2*len(players):
        raise FormatError("You have too many dead cards")

    #noDupes
    if language == 'chinese':
        message = '发现重复的卡牌，每张牌只可以出现一次'
    else:
        message = 'Duplicate values were found. Every card you specify should be unique!'

    s = set()

    for i in deads:
        if i in s:
            raise FormatError(message)
        s.add(i)

    for i in board:
        if i in s:
            raise FormatError(message)
        s.add(i)

    newPlayers = []
    for player in players:
        newPlayer = []
        for i in player:
            if i[0] not in s and i[1] not in s:
                newPlayer.append([i[0], i[1]])
        newPlayers.append(newPlayer)
    return newPlayers