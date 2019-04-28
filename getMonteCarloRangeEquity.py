from server import cppProgram

def getMonteCarloRangeEquity(dead, board, players, tripsFlag):
    print("Sending monteCarloRangeEquity...")

    result = '35000000 1.0 0.0 0.0'
    '''
    Requires prompt: '>\n'

    Input:
    montecarlorangeequity numplayers numBoard numDead numP1Hands numP2hands xxxxx

    Notes:
     - All cards are id 0..35
     - Guarunteed no duplicates between board/dead and players, but not guarunteed between individual players
     - Extra space at end of input

    Output:
    <p1Equity> <p2Equity> (<p3Equity> etc)
    '''

    #Commented out for windows
    #print(combos)
    
    #print(players)
    if tripsFlag:
        command = 'montecarlorangeequity_trips '
    else:
        command = 'montecarlorangeequity_straight '
    command += str(len(players)) + ' ' + str(len(board)) + ' ' + str(len(dead)) + ' ' + ' '.join([str(len(p)) for p in players]) + ' ' + ' '.join([' '.join([(str(i[0]) + ' ' + str(i[1])) for i in player]) for player in players]) + ' '
    if board:
        command += ' '.join([str(i) for i in board]) + ' '
    if dead:
        command += ' '.join([str(i) for i in dead]) + ' '
    #print(command)
    cppProgram.sendline(command)

    cppProgram.expect('>\n')

    result = cppProgram.before.decode().strip()

    print("Got result!")
    print(result)

    result = list(map(float, result.split(' ')))

    return result