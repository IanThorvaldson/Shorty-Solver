from server import cppProgram

def getFlopDistribution(hand, opponent, tripsFlag):
    print("Sending flop distribution...")

    result = '0 100 200 400 1000 900 300 200 100 0'
    '''
    Requires prompt: '>\n'

    Input:
    flopdistribution(_trips, _straight) <numOpponentHands> <p1c1> <p1c2> <p2c1> <p2c2> etc

    Notes:
     - All cards are id 0..35
     - Guarunteed no duplicates
     - Extra space at end of input

    Output:
    <0-10%> <10-20%> etc <90-100%>
    '''

    #Commented out for windows
    
    if tripsFlag:
        command = 'flopdistribution_trips '
    else:
        command = 'flopdistribution_straight '
    command += str(len(opponent)) + ' ' + str(hand[0]) + ' ' + str(hand[1]) + ' ' + ' '.join([(str(i[0]) + ' ' + str(i[1])) for i in opponent]) + ' '

    print(command)
    
    cppProgram.sendline(command)

    cppProgram.expect('>\n', timeout=600)

    result = cppProgram.before.decode().strip()
    

    print("Got result!")
    print(result)

    result = list(map(int, result.split(' ')))

    return result