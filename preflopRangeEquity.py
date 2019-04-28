from server import cppProgram

def preflopRangeEquity(playerHands, opponentStrength, numPlayers):
    print("Sending rangeEquity...")

    result = '1.0 0.0'

    '''
    Input: prefloprangeequity <numPlayers> <opponentRange (100%, 50%, 20%, 10% or 5%)> <numCombos> <h1c1> <h1c2> (<h2c1> <h2c22> etc) 

    First card is always from 0..8
    Second card is either from 0..8 (suited) or 9..17 (offsuit)

    Expects: <p1equity> <p2equity> etc
    '''

    command = 'prefloprangeequity ' + str(numPlayers) + ' ' + opponentStrength + str(len(playerHands)) + ' ' + ' '.join([str(hand[0] + ' ' + str(hand[1])) for hand in playerHands]) + ' '

    cppProgram.sendline(command)

    cppProgram.expect('>\n')

    result = cppProgram.before.decode().strip()

    print("Got result!")
    print(result)

    result = list(map(float, result.split(' ')))

    return result