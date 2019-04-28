from flask import Flask, redirect, render_template, request, url_for
from server import app, users
#from loadData import tableScores, tableMap
from convertToInts import convertToInts, FormatError, noDupes, correctLengths
from handEquity import getHandEquity
from unpackRange import unpackRange, combinations, COMBOLIMIT
from rangeEquity import getRangeEquity
import time
from math import factorial as fac
from verifyMonteCarlo import verifyMonteCarlo
from getMonteCarloRangeEquity import getMonteCarloRangeEquity
from flopDistribution import getFlopDistribution
'''
print("TESTING")
handEquity([], [], [[8,17], [1,2]])
handEquity([], [], [[8,17], [1,2]])
handEquity([], [], [[8,17], [1,2]])
handEquity([], [], [[8,17], [1,2]])
handEquity([], [], [[8,17], [1,2]])
handEquity([], [], [[8,17], [1,2]])
handEquity([], [], [[8,17], [1,2]])
handEquity([], [], [[8,17], [1,2]])
handEquity([], [], [[8,17], [1,2]])
handEquity([], [], [[8,17], [1,2]])
print("Test complete!")
'''

@app.route('/')
def index():
    return redirect('/straight/hand')

@app.route('/trips/<sitepath>', methods = ["GET", "POST"])
def tripsRedirect(sitepath):
    if sitepath == 'hand':
        return handEquity(req = request, tripsFlag = True)
    if sitepath == 'range':
        return rangeEquity(req = request, tripsFlag = True)
    if sitepath == 'rangeConstruction':
        return rangeConstruction(req = request, tripsFlag = True)
    if sitepath == 'intro':
        return intro(req = request, tripsFlag = True)
    if sitepath == 'ranks':
        return ranksPage(req = request, tripsFlag = True)
    if sitepath == 'tutorial':
        return tutorial(req = request, tripsFlag = True)
    if sitepath == 'flopDistribution':
        return flopDistribution(req = request, tripsFlag = True)
    return redirect('/straight/'+sitepath)

@app.route('/straight/hand', methods=["GET", "POST"])
def handEquity(tripsFlag = False, req = None):
    pageName = 'hand'
    if req == None:
        req = request
    language = request.args.get('lang')
    if req.method == "POST":
        dead = ''
        board = ''
        players = []
        numPlayers = 0
        error = ''
        try:
            dead = req.form.get('dead')
            if dead == None:
                dead = ''
            board = req.form.get('board')
            if board == None:
                board = ''
            numPlayers = int(req.form.get('players'))
            assert numPlayers > 1 and numPlayers < 7
            for i in range(numPlayers):
                players.append(req.form.get('p'+str(i+1)))
                if players[-1] == None:
                    players[-1] = ''
        except:
            if language == 'chinese':
                error = "HTML出现异常情况。此情况不应该发生，请联系我们解决问题。（shortysolver@outlook.com）"
            else:
                error = "Something went wrong with HTML form submission format... This shouldn't happen. Please contact us quickly to fix this bug. (shortysolver@outlook.com)"
            print("HTML form wrong format")

        try:
            if error == '':
                deadInts = convertToInts(dead, language)
                boardInts = convertToInts(board, language)
                playersInts = [convertToInts(i, language) for i in players]
                #print(playersInts)

                noDupes(deadInts, boardInts, playersInts, language)
                correctLengths(deadInts, boardInts, playersInts, language)
        except FormatError as errorInstance:
            error = errorInstance.args[0]
            print("Bad format")
        except Exception as err:
            if language == 'chinese':
                error = '出现了错误，请再次尝试，如果同样的问题持续出现请邮件联系我们并说明问题出现的场景如下\"{}\"。（shortysolver@outlook.com）'.format(err.args)
            else:
                error = 'Something went wrong. Please try again soon, or if the problem persists, please contact us at shortysolver@outlook.com. If you contact us, please mention the following: \"{}\"'.format(err.args)

        #print(playersInts)
        try:
            if error == '':
                equities = getHandEquity(deadInts, boardInts, playersInts, tripsFlag)
        except Exception as err:
            if language == 'chinese':
                error = '出现了错误，请再次尝试，如果同样的问题持续出现请邮件联系我们并说明问题出现的场景如下\"{}\"。（shortysolver@outlook.com）'.format(err.args)
            else:
                error = 'Something went wrong. Please try again soon, or if the problem persists, please contact us at shortysolver@outlook.com. If you contact us, please mention the following: \"{}\"'.format(err.args)

        if error:
            return render_template('hand.html', tripsFlag = tripsFlag, pageName = pageName, language = language, error=error, dead=dead, board=board, numPlayers=numPlayers, players=players)

        return render_template('hand.html', tripsFlag = tripsFlag, pageName = pageName, language = language, equities=equities, dead=dead, board=board, numPlayers=numPlayers, players=players)


    return render_template('hand.html', tripsFlag = tripsFlag, pageName = pageName, language = language)


@app.route('/straight/range', methods = ["GET", "POST"])
def rangeEquity(tripsFlag = False, req = None):
    pageName = 'range'
    if req == None:
        req = request
    language = request.args.get('lang')
    if req.method == "POST":
        dead = ''
        board = ''
        players = []
        numPlayers = 0
        error = ''
        try:
            dead = req.form.get('dead')
            if dead == None:
                dead = ''
            board = req.form.get('board')
            if board == None:
                board = ''
            numPlayers = int(req.form.get('players'))
            assert numPlayers > 1 and numPlayers < 7
            for i in range(numPlayers):
                players.append(req.form.get('p'+str(i+1)))
                if players[-1] == None:
                    players[-1] = ''
        except:
            if language == 'chinese':
                error = "HTML出现异常情况。此情况不应该发生，请联系我们解决问题。（shortysolver@outlook.com）"
            else:
                error = "Something went wrong with HTML form submission format... This shouldn't happen. Please contact us quickly to fix this bug. (shortysolver@outlook.com)"
            print("HTML form wrong format")

        try:
            if error == '':
                deadInts = convertToInts(dead, language)
                boardInts = convertToInts(board, language)
                playersUnpacked = [unpackRange(p, tripsFlag, language) for p in players]
                playersInts = [[convertToInts(i, language) for i in player] for player in playersUnpacked]

                numInDeck = 36 - len(deadInts) - len(boardInts) - 2 * numPlayers
                toChoose = 5 - len(boardInts)
                simsPerCombo = int(fac(numInDeck) / (fac(toChoose) * fac(numInDeck - toChoose)))

                pre = time.clock()
                combos = combinations(deadInts, boardInts, playersInts, simsPerCombo, language)
                post = time.clock()
                print(post-pre)
                print(len(combos))

                sims = simsPerCombo * len(combos)

                if len(combos) == 0:
                    if language == 'chinese':
                        raise FormatError("没有合适的手牌组合被找到")
                    else:
                        raise FormatError("No valid hand combinations were found.")
                
                if sims <= COMBOLIMIT:
                    for combo in combos:
                        correctLengths(deadInts, boardInts, combo, language)
                else:
                    playersInts = verifyMonteCarlo(deadInts, boardInts, playersInts, language)
                    for player in playersInts:
                        if len(player) == 0:
                            if language == 'chinese':
                                raise FormatError("没有合适的手牌组合被找到")
                            else:
                                raise FormatError("No valid hand combinations were found.")

            #print(combos)
        except FormatError as errorInstance:
            error = errorInstance.args[0]
            print("Bad format")

        except Exception as err:
            if language == 'chinese':
                error = '出现了错误，请再次尝试，如果同样的问题持续出现请邮件联系我们并说明问题出现的场景如下\"{}\"。（shortysolver@outlook.com）'.format(err.args)
            else:
                error = 'Something went wrong. Please try again soon, or if the problem persists, please contact us at shortysolver@outlook.com. If you contact us, please mention the following: \"{}\"'.format(err.args)

        try:
            if error == '':
                if sims > COMBOLIMIT:

                    pre = time.clock()
                    equities = getMonteCarloRangeEquity(deadInts, boardInts, playersInts, tripsFlag)
                    post = time.clock()

                    run = int(equities[0])

                    equities = equities[1:]

                    if run == 0:
                        if language == 'chinese':
                            error = "蒙提卡罗模拟没有发现任何有效的手牌组合。请确认有效的手牌组合被输入，或者尝试减少被模拟的玩家数量。"
                        else:
                            error = 'Monte Carlo simulation did not find any valid hand combinations. Make sure that there are valid hand combinations possible between the players, and try decreasing the number of players involved.'
                        return render_template('range.html', tripsFlag = tripsFlag, pageName = pageName, language = language, error=error, dead=dead, board=board, numPlayers=numPlayers, players=players)

                    if language == 'chinese':
                        calcStats = '蒙提卡罗模拟计算完成。 {:,} 模拟在 {}s 完成.'.format(run, round(post-pre,6))
                    else:
                        calcStats = "Monte Carlo simulation complete. {:,} rounds run in {}s.".format(run, round(post-pre,6))

                else:
                    pre = time.clock()
                    equities = getRangeEquity(deadInts, boardInts, combos, tripsFlag)
                    post = time.clock()
                    if language == 'chinese':
                        calcStats = '完整的模拟计算完成。 {:,} 模拟在 {}s 完成.'.format(sims, round(post-pre,6))
                    else:
                        calcStats = "Full simulation complete. {:,} rounds run in {}s.".format(sims, round(post-pre,6))

        except Exception as err:
            if language == 'chinese':
                error = '出现了错误，请再次尝试，如果同样的问题持续出现请邮件联系我们并说明问题出现的场景如下\"{}\"。（shortysolver@outlook.com）'.format(err.args)
            else:
                error = 'Something went wrong. Please try again soon, or if the problem persists, please contact us at shortysolver@outlook.com. If you contact us, please mention the following: \"{}\"'.format(err.args)


        if error:
            return render_template('range.html', tripsFlag = tripsFlag, pageName = pageName, language = language, error=error, dead=dead, board=board, numPlayers=numPlayers, players=players)
        

        return render_template('range.html', tripsFlag = tripsFlag, pageName = pageName, language = language, equities=equities, dead=dead, board=board, numPlayers=numPlayers, players=players, calcStats = calcStats)

    return render_template('range.html', tripsFlag = tripsFlag, pageName = pageName, language = language)

@app.route('/straight/rangeConstruction', methods = ['GET', 'POST'])
def rangeConstruction(tripsFlag = False, req = None):
    pageName = 'rangeConstruction'
    if req == None:
        req = request
    language = request.args.get('lang')
    if req.method == 'POST':
        error = ''
        keys = list(req.form.keys())
        keys.remove('rangeConstructButton')

        try:
            strings = []
            for key in keys:
                if not key.endswith('_button'):
                    if language == 'chinese':
                        raise FormatError("HTML按钮损坏，请邮件联系我们，我们会尽快解决问题。(shortysolver@outlook.com)")
                    else:
                        raise FormatError('HTML button format broke. Please contact us as soon as possible to resolve this issue. (shortysolver@outlook.com)')
                strings.append(key[:-7])

            if strings == []:
                if language == 'chinese':
                    raise FormatError('请至少从表格里选择一个手牌')
                else:
                    raise FormatError('Please select at least one hand from the grid.')

            numHands = 0
            for i in strings:
                if len(i) == 2:
                    numHands += 6
                elif i[2] == 'o':
                    numHands += 12
                else:
                    numHands += 4

            percentage = 100*numHands / 630

            p1Range = ','.join(strings)

            pre = time.clock()
            equities = []
            for p2Range in ['5%', '10%', '20%', '50%', '100%']:
                playersUnpacked = [unpackRange(p, tripsFlag, language) for p in [p1Range, p2Range]]
                playersInts = [[convertToInts(i, language) for i in player] for player in playersUnpacked]

                numInDeck = 32
                toChoose = 5
                simsPerCombo = int(fac(numInDeck) / (fac(toChoose) * fac(numInDeck - toChoose)))

                combos = combinations([], [], playersInts, simsPerCombo, language)
                print(len(combos))

                sims = simsPerCombo * len(combos)

                if len(combos) == 0:
                    if language == 'chinese':
                        raise FormatError('没有合适的组合被发现，此情况属于异常，请尽快联系我们(shortysolver@outlook.com)')
                    else:
                        raise FormatError("No valid hand combinations were found. This shouldn't happen, please contact us ASAP. (shortysolver@outlook.com)")
                
                #print(combos[0])
                if sims <= COMBOLIMIT:
                    for combo in combos:
                        correctLengths([], [], combo, language)
                else:
                    #print('Errm')
                    playersInts = verifyMonteCarlo([], [], playersInts, language)
                    for player in playersInts:
                        if len(player) == 0:
                            if language == 'chinese':
                                raise FormatError('没有合适的组合被发现，此情况属于异常，请尽快联系我们(shortysolver@outlook.com)')
                            else:
                                raise FormatError("No valid hand combinations were found. This shouldn't happen, please contact us ASAP. (shortysolver@outlook.com)")

                if sims > COMBOLIMIT:
                    result = getMonteCarloRangeEquity([], [], playersInts, tripsFlag)
                    run = result[0]
                    equities.append(result[1:])
                else:
                    equities.append(getRangeEquity([], [], combos, tripsFlag))
            post = time.clock()

            if language == 'chinese':
                calcStats = '模拟完成。你选择的范围占总范围的{}%。耗时 {}s.'.format(round(percentage,2),round(post-pre,6))
            else:
                calcStats = "Simulation complete, your range was {}% of all hands. Completed in {}s.".format(round(percentage,2),round(post-pre,6))

        except FormatError as err:
            error = err.args[0]

        except Exception as err:
            if language == 'chinese':
                error = '出现了错误，请再次尝试，如果同样的问题持续出现请邮件联系我们并说明问题出现的场景如下\"{}\"。（shortysolver@outlook.com）'.format(err.args)
            else:
                error = 'Something went wrong. Please try again soon, or if the problem persists, please contact us at shortysolver@outlook.com. If you contact us, please mention the following: \"{}\"'.format(err.args)

        if error:
            return render_template('rangeConstruction.html', tripsFlag = tripsFlag, pageName = pageName, language = language, error=error, keys = keys)

        return render_template('rangeConstruction.html', tripsFlag = tripsFlag, pageName = pageName, language = language, equities=equities, calcStats = calcStats, keys = keys)



    return render_template('rangeConstruction.html', tripsFlag = tripsFlag, pageName = pageName, language = language, keys = [])

@app.route('/straight/intro')
def intro(tripsFlag = False, req = None):
    pageName = 'intro'
    if req == None:
        req = request
    language = request.args.get('lang')
    return render_template('intro.html', tripsFlag = tripsFlag, pageName = pageName, language = language)

@app.route('/straight/ranks')
def ranksPage(tripsFlag = False, req = None):
    pageName = 'ranks'
    if req == None:
        req = request
    language = request.args.get('lang')
    return render_template('ranks.html', tripsFlag = tripsFlag, pageName = pageName, language = language)

@app.route('/straight/tutorial')
def tutorial(tripsFlag = False, req = None):
    pageName = 'tutorial'
    if req == None:
        req = request
    language = request.args.get('lang')
    return render_template('tutorial.html', tripsFlag = tripsFlag, pageName = pageName, language = language)

@app.route('/straight/flopDistribution', methods = ["POST", "GET"])
def flopDistribution(tripsFlag = False, req = None):
    pageName = 'flopDistribution'
    if req == None:
        req = request
    language = request.args.get('lang')
    if req.method == 'POST':

        error = ''

        try:
            hand = req.form.get('p1')
            opponent = req.form.get('p2')
            if hand == None or opponent == None:
                if language == 'chinese':
                    raise FormatError('有一栏没有被填写')
                else:
                    raise FormatError('One of the fields was not filled out.')

            opponentUnpacked = unpackRange(opponent, tripsFlag, language)

            handInt = convertToInts(hand, language)
            opponentInts = [convertToInts(i, language) for i in opponentUnpacked]

            opponentIntsWithoutDupes = []
            for opp1,opp2 in opponentInts:
                if not (opp1 in handInt or opp2 in handInt):
                    opponentIntsWithoutDupes.append([opp1, opp2])

            opponentInts = opponentIntsWithoutDupes

            if handInt[0] == handInt[1]:
                if language == 'chinese':
                    raise FormatError('被模拟的手牌包含两张相同的卡牌')
                else:
                    raise FormatError('The simulated hand had two of the same card.')

            for h in opponentInts:
                if h[0] == h[1]:
                    if language == 'chinese':
                        raise FormatError('对手手牌范围里有一手包含两张相同卡牌的手牌')
                    else:
                        raise FormatError('An opponent hand had two of the same card.')


            if len(opponentInts) == 0:
                if language == 'chinese':
                    raise FormatError('对手的范围与已知牌有冲突，没有合适的组合被找到，无法进行模拟。')
                else:
                    raise FormatError('The opponent range has conflicts with the simulated hand cards. No opponent hands were found which do not contain cards in the simulated hand.')

        except FormatError as err:
            error = err.args[0]

        except Exception as err:
            if language == 'chinese':
                error = '出现了错误，请再次尝试，如果同样的问题持续出现请邮件联系我们并说明问题出现的场景如下\"{}\"。（shortysolver@outlook.com）'.format(err.args)
            else:
                error = 'Something went wrong. Please try again soon, or if the problem persists, please contact us at shortysolver@outlook.com. If you contact us, please mention the following: \"{}\"'.format(err.args)


        try:
            if error == '':
                pre = time.clock()
                result = getFlopDistribution(handInt, opponentInts, tripsFlag)
                post = time.clock()

        except Exception as err:
            if language == 'chinese':
                error = '出现了错误，请再次尝试，如果同样的问题持续出现请邮件联系我们并说明问题出现的场景如下\"{}\"。（shortysolver@outlook.com）'.format(err.args)
            else:
                error = 'Something went wrong. Please try again soon, or if the problem persists, please contact us at shortysolver@outlook.com. If you contact us, please mention the following: \"{}\"'.format(err.args)

        if error:
            return render_template('flopDist.html', tripsFlag = tripsFlag, pageName = pageName, language = language, error = error, players = [hand,opponent])

        maximumValIndex = 0
        base = 0
        values = [1,1.2,1.4,1.5,2,4,6,8,10]
        while values[maximumValIndex] * 10**base < max(result)*1.1:
            maximumValIndex += 1
            if values[maximumValIndex] == 10:
                base += 1
                maximumValIndex = 0

        return render_template('flopDist.html', tripsFlag = tripsFlag, pageName = pageName, language = language, results = result, maximum = values[maximumValIndex]*10**base, players = [hand,opponent])
    return render_template('flopDist.html', tripsFlag = tripsFlag, pageName = pageName, language = language)

'''
@app.route('/buttons', methods=["POST", "GET"])
def buttons():
    if request.method == "POST":
        print(request.form)
    return render_template('testButton.html')


@app.route('/preflopRange', methods=["POST", "GET"])
def preflopRange(tripsFlag = False):
    if request.method == "POST":
        keys = []
        for key in request.form.keys():
            keys.append(key)
        print(keys)
        print(request.form.get('opponentRange'))
        try:
            hands = list(map(convertHand, keys))
            if (request.form.get('opponentRange') not in ['100%', '50%', '20%', '10%', '5%']):
                raise FormatError('Percentage was somehow not correct. Try again.')
        except FormatError as errorInstance:
            error = errorInstance.args[0]
            print("Bad format")

        if error:
            return render_template('preflopRange.html', keys = keys, error = error)

        equities = preflopRangeEquity(hands, request.form.get('opponentRange'), 2)
        return render_template('preflopRange.html', keys = keys)

    return render_template('preflopRange.html')
@app.route('/rangeNoLimit', methods=['GET', 'POST'])
def rangeNoLimit():
    if request.method == "POST":
        dead = ''
        board = ''
        players = []
        numPlayers = 0
        error = ''
        try:
            dead = request.form.get('dead')
            if dead == None:
                dead = ''
            board = request.form.get('board')
            if board == None:
                board = ''
            numPlayers = int(request.form.get('players'))
            assert numPlayers > 1 and numPlayers < 7
            for i in range(numPlayers):
                players.append(request.form.get('p'+str(i+1)))
                if players[-1] == None:
                    players[-1] = ''
        except:
            error = "Something went wrong with HTML form submission format... This shouldn't happen. Please contact us quickly to fix this bug"
            print("HTML form wrong format")

        print('Im here')
        try:
            deadInts = convertToInts(dead)
            boardInts = convertToInts(board)
            #if len(boardInts) < 3:
            #    raise FormatError("This calculator only works for post-flop boards at the moment.")
            #print('Preunpack')
            playersUnpacked = list(map(unpackRange, players))
            #print('Postpack')
            playersInts = [[convertToInts(i) for i in player] for player in playersUnpacked]
            #print(playersInts)

            combos = combinations(deadInts, boardInts, playersInts)
            print(len(combos))
            #print(combos)
            if len(combos) == 0:
                raise FormatError("No valid hand combinations were found.")
            #if len(combos) > 5000:
            #    raise FormatError("The number of hand combinations was over 5000, doing more combinations than this is not available in this version of the software.")
        except FormatError as errorInstance:
            error = errorInstance.args[0]
            print("Bad format")

        if error:
            return render_template('range.html', error=error, dead=dead, board=board, numPlayers=numPlayers, players=players)

        print(combos)
        pre = time.clock()
        equities = getRangeEquity(deadInts, boardInts, combos)
        post = time.clock()
        message = 'DEBUG: ' + str(len(combos)) + ' hand combos done in ' + str(post - pre) + 's'
        return render_template('range.html', equities=equities, dead=dead, board=board, numPlayers=numPlayers, players=players, error = message)

    return render_template('range.html')
'''
