from server import cppProgram
import time

def getHandEquity(dead, board, players, tripsFlag):
    print("Sending handEquity...")

    result = '1.0 0.0'
    '''
    Requires prompt: '>\n'

    Input:
    <numPlayers> <numBoard> <numDead> <p1c1> <p1c2> <p2c1> <p2c2> (<p3c1> etc) (<b1> etc) (<d1> etc) 

    Notes:
     - All cards are id 0..35
     - Guarunteed no duplicates
     - Extra space at end of input

    Output:
    <p1Equity> <p2Equity> (<p3Equity> etc)
    '''

    #Commented out for windows
    
    if tripsFlag:
        command = 'handequity_trips '
    else:
        command = 'handequity_straight '
    command += str(len(players)) + ' ' + str(len(board)) + ' ' + str(len(dead)) + ' ' + ' '.join([(str(i[0]) + ' ' + str(i[1])) for i in players]) + ' '
    if board:
        command += ' '.join([str(i) for i in board]) + ' '
    if dead:
        command += ' '.join([str(i) for i in dead]) + ' '
    cppProgram.sendline(command)

    cppProgram.expect('>\n', timeout=600)

    result = cppProgram.before.decode().strip()
    

    print("Got result!")
    print(result)

    result = list(map(float, result.split(' ')))

    return result