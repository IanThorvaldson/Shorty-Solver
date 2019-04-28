from server import cppProgram

def getRangeEquity(dead, board, combos, tripsFlag):
    print("Sending rangeEquity...")

    result = '1.0 0.0'
    '''
    Requires prompt: '>\n'

    Input:
    rangeequity <numPlayers> <numCombos> <numBoard> <numDead> (combo1 <p1c1> <p1c2> <p2c1> <p2c2> (<p3c1> etc) etc) (<b1> etc) (<d1> etc) 

    Notes:
     - All cards are id 0..35
     - Guarunteed no duplicates
     - Extra space at end of input

    Output:
    <p1Equity> <p2Equity> (<p3Equity> etc)
    '''

    #Commented out for windows
    #print(combos)
    
    if tripsFlag:
        command = 'rangeequity_trips '
    else:
        command = 'rangeequity_straight '
    command += str(len(combos[0])) + ' ' + str(len(combos)) + ' ' + str(len(board)) + ' ' + str(len(dead)) + ' ' + ' '.join([' '.join([(str(i[0]) + ' ' + str(i[1])) for i in players]) for players in combos]) + ' '
    if board:
        command += ' '.join([str(i) for i in board]) + ' '
    if dead:
        command += ' '.join([str(i) for i in dead]) + ' '
    print(command)
    
    cppProgram.sendline(command)

    cppProgram.expect('>\n')

    result = cppProgram.before.decode().strip()
    

    print("Got result!")
    print(result)

    result = list(map(float, result.split(' ')))

    return result
