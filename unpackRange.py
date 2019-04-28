from convertToInts import FormatError, noDupes, correctLengths

COMBOLIMIT = 3500000
MAXFAILS = 1000000

#handRankings_trips_old = [['AA', 0.0095], ['KK', 0.019], ['KAs', 0.0254], ['QQ', 0.0349], ['KAo', 0.054000000000000006], ['JJ', 0.0635], ['TT', 0.073], ['QAs', 0.0794], ['QAo', 0.0984], ['JAs', 0.1048], ['JAo', 0.12380000000000001], ['QKs', 0.13019999999999998], ['TAs', 0.1365], ['QKo', 0.15560000000000002], ['TAo', 0.1746], ['JKs', 0.18100000000000002], ['TKs', 0.1873], ['JKo', 0.20629999999999998], ['JQs', 0.2127], ['99', 0.22219999999999998], ['TQs', 0.2286], ['TKo', 0.24760000000000001], ['9As', 0.254], ['JQo', 0.273], ['TJs', 0.27940000000000004], ['TQo', 0.2984], ['TJo', 0.3175], ['9Ao', 0.33649999999999997], ['8As', 0.3429], ['9Ks', 0.3492], ['9Ts', 0.3556], ['88', 0.3651], ['7As', 0.3714], ['9Qs', 0.3778], ['8Ao', 0.3968], ['9Ko', 0.41590000000000005], ['9Js', 0.42219999999999996], ['6As', 0.4286], ['8Ts', 0.4349], ['9To', 0.45399999999999996], ['8Ks', 0.4603], ['9Qo', 0.4794], ['9Jo', 0.4984], ['8Qs', 0.5047999999999999], ['7Ao', 0.5238], ['7Ks', 0.5302], ['8Js', 0.5365], ['8Ko', 0.5556], ['8To', 0.5746], ['8Qo', 0.5937], ['77', 0.6032], ['6Ao', 0.6222], ['8Jo', 0.6413], ['6Ks', 0.6476000000000001], ['7Ko', 0.6667000000000001], ['89s', 0.6729999999999999], ['7Ts', 0.6794], ['7Qs', 0.6857], ['7Js', 0.6920999999999999], ['6Qs', 0.6984], ['6Ko', 0.7175], ['7To', 0.7365], ['89o', 0.7556], ['7Qo', 0.7746], ['7Jo', 0.7937000000000001], ['79s', 0.8], ['6Ts', 0.8062999999999999], ['6Qo', 0.8254], ['6Js', 0.8317], ['79o', 0.8508], ['66', 0.8603000000000001], ['78s', 0.8667], ['6To', 0.8856999999999999], ['69s', 0.8920999999999999], ['6Jo', 0.9111], ['78o', 0.9301999999999999], ['68s', 0.9365000000000001], ['69o', 0.9556], ['67s', 0.9619], ['68o', 0.981], ['67o', 1.0]]
#handRankings_straight_old = [['AA', 0.0095], ['KK', 0.019], ['AKs', 0.0254], ['AKo', 0.0444], ['QQ', 0.054000000000000006], ['AQs', 0.0603], ['AQo', 0.0794], ['JJ', 0.0889], ['AJs', 0.09519999999999999], ['AJo', 0.1143], ['KQs', 0.1206], ['ATs', 0.127], ['KQo', 0.146], ['ATo', 0.16510000000000002], ['KJs', 0.1714], ['KTs', 0.1778], ['QJs', 0.1841], ['KJo', 0.2032], ['TT', 0.2127], ['QTs', 0.21899999999999997], ['KTo', 0.23809999999999998], ['QJo', 0.2571], ['JTs', 0.2635], ['A9s', 0.2698], ['QTo', 0.2889], ['JTo', 0.3079], ['A9o', 0.327], ['99', 0.33649999999999997], ['K9s', 0.3429], ['A8s', 0.3492], ['T9s', 0.3556], ['Q9s', 0.3619], ['J9s', 0.36829999999999996], ['A7s', 0.3746], ['K9o', 0.3937], ['T9o', 0.4127], ['A8o', 0.43170000000000003], ['T8s', 0.43810000000000004], ['Q9o', 0.4571], ['K8s', 0.4635], ['J9o', 0.4825], ['88', 0.4921], ['Q8s', 0.4984], ['J8s', 0.5047999999999999], ['A7o', 0.5238], ['A6s', 0.5302], ['K7s', 0.5365], ['T8o', 0.5556], ['K8o', 0.5746], ['Q8o', 0.5937], ['J8o', 0.6127], ['98s', 0.619], ['T7s', 0.6254], ['K6s', 0.6317], ['A6o', 0.6507999999999999], ['K7o', 0.6698000000000001], ['Q7s', 0.6762], ['J7s', 0.6825], ['98o', 0.7016], ['77', 0.7111], ['T7o', 0.7302], ['Q6s', 0.7365], ['K6o', 0.7556], ['97s', 0.7619], ['Q7o', 0.7809999999999999], ['J7o', 0.8], ['T6s', 0.8062999999999999], ['Q6o', 0.8254], ['J6s', 0.8317], ['97o', 0.8508], ['87s', 0.8571], ['T6o', 0.8762000000000001], ['96s', 0.8825], ['J6o', 0.9016], ['66', 0.9111], ['87o', 0.9301999999999999], ['86s', 0.9365000000000001], ['96o', 0.9556], ['76s', 0.9619], ['86o', 0.981], ['76o', 1.0]]

handRankings_trips = [['AA', 0.78021], ['KK', 0.522884], ['KAs', 0.450198], ['QQ', 0.402906], ['KAo', 0.401942], ['JJ', 0.466294], ['QAs', 0.435922], ['TT', 0.431171], ['QAo', 0.402164], ['JAs', 0.391355], ['JAo', 0.460043], ['TAs', 0.448313], ['QKs', 0.445895], ['99', 0.434689], ['9As', 0.429447], ['JKs', 0.421897], ['TAo', 0.421752], ['QKo', 0.419154], ['TKs', 0.415443], ['JKo', 0.44698], ['JQs', 0.444429], ['8As', 0.443422], ['TJs', 0.438323], ['9Ao', 0.437056], ['TQs', 0.435075], ['TKo', 0.424793], ['JQo', 0.419743], ['TQo', 0.471478], ['TJo', 0.464626], ['7As', 0.459246], ['88', 0.458004], ['9Ks', 0.456802], ['8Ao', 0.454475], ['6As', 0.445427], ['9Ts', 0.445181], ['9Qs', 0.443811], ['9Js', 0.438234], ['7Ao', 0.435008], ['9Ko', 0.43323], ['9To', 0.422308], ['9Qo', 0.420013], ['9Jo', 0.414563], ['8Ks', 0.500285], ['8Qs', 0.492043], ['8Js', 0.487262], ['7Ks', 0.486919], ['8Ts', 0.486796], ['89s', 0.483897], ['6Ao', 0.481445], ['8Ko', 0.479212], ['77', 0.475477], ['8Qo', 0.471048], ['8Jo', 0.466492], ['8To', 0.466466], ['6Ks', 0.465799], ['7Ko', 0.464828], ['89o', 0.463561], ['7Qs', 0.459736], ['7Js', 0.454856], ['7Ts', 0.4543], ['79s', 0.454061], ['6Qs', 0.445846], ['6Ko', 0.442226], ['7Qo', 0.436651], ['7Jo', 0.431998], ['7To', 0.431882], ['79o', 0.431833], ['78s', 0.430138], ['6Qo', 0.421753], ['69s', 0.420936], ['6Js', 0.420306], ['6Ts', 0.419722], ['66', 0.41503], ['78o', 0.406301], ['68s', 0.398008], ['69o', 0.396622], ['6Jo', 0.395234], ['6To', 0.395094], ['67s', 0.375729], ['68o', 0.372161], ['67o', 0.348447]]
handRankings_straight = [['AA', 0.778004], ['KK', 0.519886], ['KAs', 0.462042], ['KAo', 0.418028], ['QQ', 0.385462], ['QAs', 0.480537], ['QAo', 0.454315], ['JJ', 0.426262], ['JAs', 0.40681], ['JAo', 0.370349], ['QKs', 0.4556], ['TT', 0.454146], ['TAs', 0.453513], ['9As', 0.435192], ['JKs', 0.431357], ['QKo', 0.4299], ['TAo', 0.427587], ['JQs', 0.426046], ['TKs', 0.423634], ['JKo', 0.458767], ['TJs', 0.442548], ['TQs', 0.442242], ['TKo', 0.439107], ['9Ao', 0.438517], ['JQo', 0.435987], ['TQo', 0.417984], ['8As', 0.477675], ['TJo', 0.477381], ['99', 0.464973], ['7As', 0.45987], ['9Ks', 0.4578], ['8Ao', 0.455239], ['9Ts', 0.455036], ['9Qs', 0.448036], ['6As', 0.445442], ['9Js', 0.445429], ['7Ao', 0.435979], ['9Ko', 0.434626], ['9To', 0.43311], ['88', 0.426169], ['9Qo', 0.424831], ['9Jo', 0.422539], ['8Ks', 0.497743], ['89s', 0.493403], ['8Ts', 0.493032], ['8Qs', 0.492423], ['8Js', 0.490571], ['7Ks', 0.484923], ['6Ao', 0.481194], ['8Ko', 0.476869], ['89o', 0.473858], ['8To', 0.473355], ['8Qo', 0.471775], ['8Jo', 0.4703], ['6Ks', 0.463366], ['7Ko', 0.463026], ['79s', 0.460912], ['7Ts', 0.457771], ['7Qs', 0.457272], ['7Js', 0.455385], ['77', 0.447521], ['6Qs', 0.443928], ['6Ko', 0.439929], ['79o', 0.439339], ['78s', 0.436586], ['7To', 0.43586], ['7Qo', 0.43439], ['7Jo', 0.432881], ['69s', 0.424968], ['6Ts', 0.420348], ['6Qo', 0.420032], ['6Js', 0.417927], ['78o', 0.413345], ['68s', 0.401762], ['69o', 0.401161], ['6To', 0.396079], ['6Jo', 0.393062], ['66', 0.389517], ['67s', 0.379074], ['68o', 0.376374], ['67o', 0.352192]]

def unpackRange(string, tripsFlag, language):
    string = string.replace('t', 'T')
    string = string.replace('j', 'J')
    string = string.replace('q', 'Q')
    string = string.replace('k', 'K')
    string = string.replace('a', 'A')
    if tripsFlag:
        handRankings = handRankings_trips
    else:
        handRankings = handRankings_straight


    items = set(string.split(','))
    originals = [i for i in items]
    print(originals)

    #Percentage expansion
    for i in originals:
        if i.endswith('%'):
            items.remove(i)
            try:
                score = float(i[:-1])/100
            except ValueError:
                if language == 'chinese':
                    raise FormatError('胜率不是一个0到100的数字')
                else:
                    raise FormatError('Percentage was not a number between 0 and 100.')
            if score > 1 or score < 0:
                if language == 'chinese':
                    raise FormatError('胜率不是一个0到100的数字')
                else:
                    raise FormatError('Percentage was not a number between 0 and 100.')
            index = 0
            while handRankings[index][1] < score:
                items.add(handRankings[index][0])
                index += 1
            items.add(handRankings[index][0])


    #Initial length checking and splitting of 2-card combos
    originals = [i for i in items]
    #print(originals)
    for i in originals:
        if len(i) < 2 or len(i) > 4:
            if language == 'chinese':
                raise FormatError('你输入的其中一个手牌是不正确的格式')
            else:
                raise FormatError("One of the hands you entered is in an invalid format")
        if (len(i) == 2):
            if i[0] == i[1] and i[0] in 'AKQJT9876':
                items.remove(i)
                items.add(i[0]+'c'+i[0]+'d')
                items.add(i[0]+'c'+i[0]+'h')
                items.add(i[0]+'c'+i[0]+'s')
                items.add(i[0]+'d'+i[0]+'h')
                items.add(i[0]+'d'+i[0]+'s')
                items.add(i[0]+'h'+i[0]+'s')
            elif i[0] in 'AKQJT9876' and i[1] in 'AKQJT9876':
                items.remove(i)
                items.add(i+'o')
                items.add(i+'s')
            else:
                if language == 'chinese':
                    raise FormatError('请用\"AKQJT9876\"来表示牌')
                else:
                    raise FormatError("Please use cards from \"AKQJT9876\"")

    #Splitting of offsuit and suited pairs
    originals = [i for i in items]
    for i in originals:
        if len(i) == 3:
            if i[0] in 'AKQJT9876' and i[1] in 'AKQJT9876' and i[0] != i[1]:
                if i[2] == 'o':
                    items.remove(i)
                    items.add(i[0]+'c'+i[1]+'d')
                    items.add(i[0]+'c'+i[1]+'h')
                    items.add(i[0]+'c'+i[1]+'s')
                    items.add(i[0]+'d'+i[1]+'h')
                    items.add(i[0]+'d'+i[1]+'s')
                    items.add(i[0]+'h'+i[1]+'s')

                    items.add(i[1]+'c'+i[0]+'d')
                    items.add(i[1]+'c'+i[0]+'h')
                    items.add(i[1]+'c'+i[0]+'s')
                    items.add(i[1]+'d'+i[0]+'h')
                    items.add(i[1]+'d'+i[0]+'s')
                    items.add(i[1]+'h'+i[0]+'s')
                elif i[2] == 's':
                    items.remove(i)
                    items.add(i[0]+'c'+i[1]+'c')
                    items.add(i[0]+'d'+i[1]+'d')
                    items.add(i[0]+'h'+i[1]+'h')
                    items.add(i[0]+'s'+i[1]+'s')
                else:
                    if language == 'chinese':
                        raise FormatError('请用 \"o\" 来表示不同色的手牌， \"s\" 来表示同色的手牌 ')
                    else:
                        raise FormatError("Please use \"o\" for offsuit hands and \"s\" for suited hands")
            else:
                if language == 'chinese':
                    raise FormatError('请用\"AKQJT9876\"来表示牌，对于同色以及非同色的手牌，你必须提供两张不一样的牌')
                else:
                    raise FormatError("Please use cards from \"AKQJT9876\", and for offsuit/suited hands you must have two different cards.")
    return list(items)

def combinations(dead, board, players, simsPerCombo, language):
    combos = []

    indices = [0 for i in range(len(players))]
    fails = 0
    while indices[0] < len(players[0]):
        combo = [players[i][indices[i]] for i in range(len(players))]
        #print("Testing", combo)
        try:
            noDupes(dead, board, combo, language)
            correctLengths(dead, board, combo, language)
        except:
            fails += 1
        else:
            combos.append(combo)
            if len(combos)*simsPerCombo > COMBOLIMIT:
                return combos
        if fails > MAXFAILS:
            print('LARGEFAIL', len(combos))
            return [i for i in range(int(COMBOLIMIT/simsPerCombo) + 1)]

        #Increment
        indices[-1] += 1
        i = len(indices) - 1
        while (indices[i] == len(players[i])):
            if i == 0:
                break
            indices[i] = 0
            indices[i-1] += 1
            i -= 1
    return combos