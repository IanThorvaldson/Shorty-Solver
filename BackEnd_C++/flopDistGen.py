import itertools
import pexpect
import pexpect.popen_spawn

print("Initial startup (starting C++)...")
cppProgram = pexpect.popen_spawn.PopenSpawn("./ShortySolver")
cppProgram.expect('>\n', timeout=600)
print("Started up!")

deck = set()
for i in range(36):
     deck.add(i)

data = {}

combos = 0
done = 0
for h1c1, h1c2 in itertools.combinations([i for i in range(36)], 2):
    if h1c1 >= 9 or h1c2 >= 18:
        continue
    deck.remove(h1c1)
    deck.remove(h1c2)

    hand1Str = '6789TJQKA'[h1c1%9] + '6789TJQKA'[h1c2%9]
    if hand1Str[0] != hand1Str[1]:
        if h1c1//9 == h1c2//9:
            hand1Str += 's'
        else:
            hand1Str += 'o'

    remaining = list(deck)
    for h2c1, h2c2 in itertools.combinations(remaining, 2):
        deck.remove(h2c1)
        deck.remove(h2c2)

        hand2Str = '6789TJQKA'[h2c1%9] + '6789TJQKA'[h2c2%9]
        if hand2Str[0] != hand2Str[1]:
            if h2c1//9 == h2c2//9:
                hand2Str += 's'
            else:
                hand2Str += 'o'

        now_remaining = list(deck)

        buckets = [0 for i in range(10)]

        for b1,b2,b3 in itertools.combinations(now_remaining,3):
            combos += 1

            command = 'handequity_trips 2 3 0 {} {} {} {} {} {} {} '.format(h1c1, h1c2, h2c1, h2c2, b1, b2, b3)

            cppProgram.sendline(command)

            cppProgram.expect('>\n', timeout=600)

            result = cppProgram.before.decode().strip()

            value = int(10*float(result.split(' ')[0]))
            if value == 10:
                value = 9

            buckets[value] += 1

        print('Completed {},{} with {}'.format((h1c1, h1c2), (h2c1, h2c2), buckets))

        deck.add(h2c1)
        deck.add(h2c2)

    done += 1
    print('done {}/630'.format(done))

    deck.add(h1c1)
    deck.add(h1c2)

print(combos)
