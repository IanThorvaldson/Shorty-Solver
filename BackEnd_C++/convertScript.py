import itertools

data = {}

for line in open('flop_distribution_trips_beats_straight.txt', 'r'):
    line = line.strip()
    if line != '':
        splitted = line.split(' ')
        key = ' '.join(splitted[:4])
        data[key] = splitted[4:]

for h1c1, h1c2 in itertools.combinations([i for i in range(36)],2):
    deck = [i for i in range(36)]
    deck.remove(h1c1)
    deck.remove(h1c2)

    #print(deck)

    for h2c1, h2c2 in itertools.combinations(deck, 2):
        firstInt = 2**h1c1 + 2**h1c2
        secondInt = 2**h2c1 + 2**h2c2

        suits = [h1c1//9, h1c2//9, h2c1//9, h2c2//9]
        values = [h1c1%9, h1c2%9, h2c1%9, h2c2%9]
        #print(h1c1, h1c2, h2c1, h2c2)

        if values[0] > values[1]:
            tmp = values[1]
            tmp2 = suits[1]
            values[1] = values[0]
            values[0] = tmp
            suits[1] = suits[0]
            suits[0] = tmp2

        if suits[0] != 0:
            s1 = 0
            s2 = suits[0]
            for i in range(4):
                if suits[i] == s1:
                    suits[i] = s2
                elif suits[i] == s2:
                    suits[i] = s1

        if suits[1] != 0 and suits[1] != 1:
            s1 = 1
            s2 = suits[1]
            for i in range(4):
                if suits[i] == s1:
                    suits[i] = s2
                elif suits[i] == s2:
                    suits[i] = s1

        h1c1cpy = suits[0]*9+values[0]
        h1c2cpy = suits[1]*9+values[1]

        if h1c1cpy > h1c2cpy:
            tmp = h1c2cpy
            h1c2cpy = h1c1cpy
            h1c1cpy = tmp

        h2c1cpy = suits[2]*9+values[2]
        h2c2cpy = suits[3]*9+values[3]

        if h2c1cpy > h2c2cpy:
            tmp = h2c2cpy
            h2c2cpy = h2c1cpy
            h2c1cpy = tmp

        scores = data[str(h1c1cpy) + ' ' + str(h1c2cpy) + ' ' + str(h2c1cpy) + ' ' + str(h2c2cpy)]

        print(firstInt, secondInt, ' '.join([str(i) for i in scores]))