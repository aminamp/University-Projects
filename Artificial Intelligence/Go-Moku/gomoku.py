# CSCI 561 - HW1
# By Amin Amiripour (amiripou@usc.edu)


import sys
import copy
import string


class Gomoku:
    def __init__(self):
        self.task = 0
        self.player = 0
        self.cutoff = 0
        self.size = 0
        self.initialBoard = Board()

class Board:
    def __init__(self):
        self.board = []
        self.size = 0

class Move:
    def __init__(self, row, col, moveString):
        self.row = row
        self.col = col
        self.intersection = moveString



def Minimax(game):

	#Always start with Maximizer ( in this HW! )
    output = open("traverse_log.txt", 'w')
    output.write("Move,Depth,Value\n")
    output.write("root,0,-Infinity\n")
    moves = validMoves(game.initialBoard)
    value = float("-inf")
    optPosition = float("-inf")

    for move in range( len(moves) ):
        score = getMin( placeStone(game.initialBoard, moves[move], game.player), moves[move], 1, game.cutoff, game.player, evalStone(game.initialBoard, moves[move], game.player, game.player), output )
        if score > value:
            value = score
            optPosition = move
        output.write("root,0,")
        if value == float("-inf"):
        	output.write("-Infinity")
        	output.write('\n')
    	elif value == float("inf"):
        	output.write("Infinity")
        	output.write('\n')
    	else:
        	output.write(("%d") %(value))
        	output.write('\n')

    output.close()

    row = moves[optPosition].row
    col = moves[optPosition].col 

    if game.player == 1:	#black
    	char = 'b'
    if game.player == 2:	#white
    	char = 'w'

    game.initialBoard.board[row][col] = char	

    out = open("next_state.txt", "w")

    for row in range(game.size):
		out.write(''.join(game.initialBoard.board[row][0:game.size]))
		out.write('\n')



def getMin(board, parentMove, depth, cutoff, turn, pathval, output):
    
    if winCase(board) == True:
    	output.write( ("%s,%d,%d\n") % (parentMove.intersection,depth,pathval) )
        return pathval

    value = float("inf")
    output.write( ("%s,%d,") % (parentMove.intersection,depth) )
    output.write("Infinity\n")

    if depth + 1 == cutoff:				#reach leaf node
        for move in validMoves(board):
            score = evalStone(board, move, enemy(turn), turn) + pathval
            
            output.write( ("%s,%d,%d") % (move.intersection,cutoff,score) )
            output.write('\n')
            
            if score < value:
                value = score

            output.write( ("%s,%d,%d") % (parentMove.intersection,depth,value) )
            output.write('\n')

    else:										#reach non-leaf node
        for move in validMoves(board):
            score = getMax(placeStone(board, move, enemy(turn)), move, depth+1, cutoff, turn, evalStone(board, move, enemy(turn), turn) + pathval, output)
            if score < value:
                value = score

            output.write( ("%s,%d,%d") % (parentMove.intersection,depth,value) )
            output.write('\n')    

    return value


def getMax(board, parentMove, depth, cutoff, turn, pathval, output):
    if winCase(board) == True:
        output.write( ("%s,%d,%d\n") % (parentMove.intersection,depth,pathval) )
        return pathval

    value = float("-inf")
    output.write( ("%s,%d,") % (parentMove.intersection,depth) )
    output.write("-Infinity\n")

    if depth + 1 == cutoff :		#reach leaf node
        for move in validMoves(board):
            score = evalStone(board, move, turn, turn) + pathval

            output.write( ("%s,%d,%d") % (move.intersection,cutoff,score) )
            output.write('\n')
            
            if score > value:
                value = score

            output.write( ("%s,%d,%d") % (parentMove.intersection,depth,value) )
            output.write('\n')    
            
    else:								#reach non-leaf node
        for move in validMoves(board):
            score = getMin(placeStone(board, move, turn), move, depth+1, cutoff, turn, evalStone(board, move, turn, turn) + pathval, output)
            if score > value:
                value = score
            
            output.write( ("%s,%d,%d") % (parentMove.intersection,depth,value) )
            output.write('\n') 
            
    return value    



def greedy(game):
    
    moves = validMoves(game.initialBoard)
    
    value = float("-inf")
    optPosition = float("-inf")
    
    for move in range( len(moves) ):
        score = evalStone(game.initialBoard, moves[move], game.player, game.player)
        if score > value:
            value = score
            optPosition = move

    row = moves[optPosition].row
    col = moves[optPosition].col 

    if game.player == 1:	#black
    	char = 'b'
    if game.player == 2:	#white
    	char = 'w'

    game.initialBoard.board[row][col] = char	

    out = open("next_state.txt", "w")

    for row in range(game.size):
		out.write(''.join(game.initialBoard.board[row][0:game.size]))
		out.write('\n')


def enemy(player):
    
    if player == 1:
        return 2
    
    if player == 2:
        return 1


def winCase(board):
    for row in range(board.size):
        for col in range(board.size):
            if board.board[row][col] != '.':
                player = board.board[row][col]
                   #check horizontal
                if col - 4 < 0:
                   lowrange = 0
                else:
                   lowrange = col - 4

                if col + 4 > board.size-1:
                   uprange = board.size-1
                else:
                   uprange = col + 4

                if player+player+player+player+player in ''.join(board.board[row][lowrange:uprange+1]):
                   return True	

                   #check Vertical
                if row - 4 < 0:
                   lowrange = 0
                else:
                   lowrange = row - 4

                if row + 4 > board.size-1:
                   uprange = board.size-1
                else:
                   uprange = row + 4

                if player+player+player+player+player in ''.join(trow[col] for trow in board.board[lowrange:uprange+1]):
                   return True	

                   #check diagonal
                if row - 4 < 0:
                   rowlowrange = 0
                else:
                   rowlowrange = row - 4

                if row + 4 > board.size-1:
                   rowuprange = board.size-1
                else:
                   rowuprange = row + 4

                if col - 4 < 0:
                   collowrange = 0
                else:
                   collowrange = col - 4

                if col + 4 > board.size-1:
                   coluprange = board.size-1
                else:
                   coluprange = col + 4

                if player+player+player+player+player in ''.join( sum([[board.board[i][j] for i in range(rowlowrange,rowuprange+1,1) if (i-j) == (row-col) ] for j in range(collowrange,coluprange+1,1)], []) ):
                   return True

                if player+player+player+player+player in ''.join( sum([[board.board[i][j] for i in range(rowuprange,rowlowrange-1,-1) if (i+j) == (row+col) ] for j in range(collowrange,coluprange+1,1)], []) ):
                   return True	

    return False


def haveNeighbor(initialBoard, r, c):
	lowR = r - 1
	upR = r + 1
	lowC = c - 1
	upC = c + 1

	if r - 1 < 0:
		lowR = 0
	if r + 1 > initialBoard.size-1:
		upR = initialBoard.size-1
	if c - 1 < 0:
		lowC = 0
	if c + 1 > initialBoard.size-1:
		upC = initialBoard.size-1

	if initialBoard.board[lowR][lowC] != '.' or initialBoard.board[lowR][upC] != '.' or initialBoard.board[lowR][c] != '.' or initialBoard.board[r][lowC] != '.' or initialBoard.board[r][upC] != '.' or initialBoard.board[upR][lowC] != '.' or initialBoard.board[upR][c] != '.' or initialBoard.board[upR][upC] != '.':
		return True
	else:
		return False    


def validMoves(board):
    temp = []
    for col in range(board.size):
        for row in range(board.size-1, -1, -1):
            if board.board[row][col] == '.':
            	if haveNeighbor(board, row, col) == True:
            		s = chr(col+ord('A')) + str(board.size - row)
            		temp.append(Move(row, col, s))

    return temp


def placeStone(board, move, player):
    
    copy = Board()
    copy.size = board.size
    copy.board = [eachRow[:] for eachRow in board.board]
    
    if player == 1:
        copy.board[move.row][move.col] = 'b'

    if player == 2:
        copy.board[move.row][move.col] = 'w'
    
    return copy


def AlphaBeta(game):
    output = open("traverse_log.txt", 'w')
    output.write("Move,Depth,Value,Alpha,Beta\n")
    value, alpha, optPosition = float("-inf"), float("-inf"), float("-inf")
    beta = float("inf")

    output.write("root,0,")
    if value == float("-inf"):
        output.write("-Infinity,")
    elif value == float("inf"):
        output.write("Infinity,")
    else:
        output.write(("%d,") %(value))

    if alpha == float("-inf"):
        output.write("-Infinity,")
    elif alpha == float("inf"):
        output.write("Infinity,")
    else:
        output.write(("%d,") %(alpha))

    if beta == float("-inf"):
        output.write("-Infinity\n")
    elif beta == float("inf"):
        output.write("Infinity\n")
    else:
        output.write(("%d\n") %(beta))	

    moves = validMoves(game.initialBoard)
    for move in range(len(moves)):
        score = getMinAB(placeStone(game.initialBoard, moves[move], game.player), moves[move], 1, game.cutoff, game.player, evalStone(game.initialBoard, moves[move], game.player, game.player), alpha, beta, output)
        if score > value:
            value = score
            optPosition = move
        if score > alpha:
            alpha = score

        output.write("root,0,")
        if value == float("-inf"):
        	output.write("-Infinity,")
    	elif value == float("inf"):
        	output.write("Infinity,")
    	else:
        	output.write(("%d,") %(value))

        if alpha == float("-inf"):
        	output.write("-Infinity,")
    	elif alpha == float("inf"):
        	output.write("Infinity,")
    	else:
        	output.write(("%d,") %(alpha))

        if beta == float("-inf"):
        	output.write("-Infinity\n")
    	elif beta == float("inf"):
        	output.write("Infinity\n")
    	else:
        	output.write(("%d\n") %(beta))	

        
        if alpha >= beta:
            break
    
    output.close()

    row = moves[optPosition].row
    col = moves[optPosition].col 

    if game.player == 1:	#black
    	char = 'b'
    if game.player == 2:	#white
    	char = 'w'

    game.initialBoard.board[row][col] = char	

    out = open("next_state.txt", "w")

    for row in range(game.size):
		out.write(''.join(game.initialBoard.board[row][0:game.size]))
		out.write('\n')


def printLog(output, move, depth, value, alpha, beta):
    if depth == 0:
        output.write("root")
    else:
        output.write(move.intersection)
    output.write(",")

    output.write(("%d,") %(depth))

    if value == float("-inf"):
        output.write("-Infinity,")
    elif value == float("inf"):
        output.write("Infinity,")
    else:
        output.write(("%d,") %(value))

    if alpha == float("-inf"):
        output.write("-Infinity,")
    elif alpha == float("inf"):
        output.write("Infinity,")
    else:
        output.write(("%d,") %(alpha))

    if beta == float("-inf"):
        output.write("-Infinity\n")
    elif beta == float("inf"):
        output.write("Infinity\n")
    else:
        output.write(("%d\n") %(beta))


def getMaxAB(board, parentMove, depth, cutoff, turn, pathval, alpha, beta, output):
    if winCase(board):
        printLog(output, parentMove, depth, pathval, alpha, beta)
        return pathval

    highValue = float("-inf")
    printLog(output, parentMove, depth, highValue, alpha, beta)
    if depth == cutoff - 1:
        for move in validMoves(board):
            value = evalStone(board, move, turn, turn) + pathval
            printLog(output, move, cutoff, value, alpha, beta)
            
            lastalpha = alpha
            if value > alpha:
                alpha = value
            if value > highValue:
                highValue = value
            if alpha >= beta:
                printLog(output, parentMove, depth, highValue, lastalpha, beta)
                break
            else:
                printLog(output, parentMove, depth, highValue, alpha, beta)
    else:
        for move in validMoves(board):
            value = getMinAB(placeStone(board, move, turn), move, depth+1, cutoff, turn, evalStone(board, move, turn, turn) + pathval, alpha, beta, output)
            lastalpha = alpha
            if value > highValue:
                highValue = value
            if highValue >= alpha:
                alpha = highValue
            if alpha >= beta:
                printLog(output, parentMove, depth, highValue, lastalpha, beta)
                break
            else:
                printLog(output, parentMove, depth, highValue, alpha, beta)

    return highValue

def getMinAB(board, parentMove, depth, cutoff, turn, pathval, alpha, beta, output):

    if winCase(board) == True:
    	output.write( ("%s,%d,%d,%d,%d\n") % (parentMove.intersection,depth,pathval, alpha, beta) )
        return pathval

    value = float("inf")
    if depth == 0:
        output.write("root")
    else:
        output.write(parentMove.intersection)
    output.write(",")

    output.write(("%d") %(depth))
    output.write(",")

    if value == float("-inf"):
        output.write("-Infinity")
    elif value == float("inf"):
        output.write("Infinity")
    else:
        output.write(("%d") %(value))
    output.write(",")

    if alpha == float("-inf"):
        output.write("-Infinity")
    elif alpha == float("inf"):
        output.write("Infinity")
    else:
        output.write(("%d") %(alpha))
    output.write(",")

    if beta == float("-inf"):
        output.write("-Infinity")
    elif beta == float("inf"):
        output.write("Infinity")
    else:
        output.write(("%d") %(beta))

    output.write('\n')

    if depth + 1 == cutoff:		#leaf node
        for move in validMoves(board):
            score = evalStone(board, move, enemy(turn), turn) + pathval
            printLog(output, move, cutoff, score, alpha, beta)
            lastBeta = beta
            if score < beta:
                beta = score
            if score < value:
                value = score
            if alpha >= beta:
                printLog(output, parentMove, depth, value, alpha, lastBeta)
                break
            else:
                printLog(output, parentMove, depth, value, alpha, beta)
    else:
        for move in validMoves(board):
            score = getMaxAB(placeStone(board, move, enemy(turn)), move, depth+1, cutoff, turn, evalStone(board, move, enemy(turn), turn) + pathval, alpha, beta, output)
            
            lastBeta = beta
            if score < value:
                value = score
            
            if value < beta:
                beta = value
            
            if alpha >= beta:
                printLog(output, parentMove, depth, value, alpha, lastBeta)
                break
            else:
                printLog(output, parentMove, depth, value, alpha, beta)
    return value


# Note : I Got some help for Evaluation Function 
def getscore(inputList, currentPlayer ):

    value, moveIndex, length = 0, 0, len(inputList)
    movePiece, player, opponent= '.', '.', '.'

    if currentPlayer == 1:
        movePiece = 'B'
        player = 'b'
        opponent = 'w'

    if currentPlayer == 2:
        movePiece = 'W'
        player = 'w'
        opponent = 'b'

    for i in range(len(inputList)):
        if inputList[i] == movePiece:
            moveIndex = i
            break

    CREATE_OPEN = {0: 0, 1: 0, 2: 5, 3: 50, 4: 5000}
    CREATE_CLOSED = {0: 0, 1: 0, 2: 1, 3: 10, 4: 1000}
    BLOCK_OPEN = {0: 0, 1: 0, 2: 0, 3: 500, 4: 0}
    BLOCK_CLOSED = {0: 0, 1: 0, 2: 0, 3: 100, 4: 10000}        

    if (moveIndex > 0 and inputList[moveIndex-1] == player) or (moveIndex < length-1 and inputList[moveIndex+1] == player):
    	runLength, left, right = 1, '.', '.'
        currentIndex = moveIndex-1
        while currentIndex >= -1:
            if currentIndex == -1:
                left = opponent
                break
            elif inputList[currentIndex] == player:
                runLength += 1
                currentIndex -= 1
            elif inputList[currentIndex] == opponent:
                left = opponent
                break
            else:
                break

        currentIndex = moveIndex+1
        while currentIndex <= length:
            if currentIndex == length:
                right = opponent
                break
            elif inputList[currentIndex] == player:
                runLength += 1
                currentIndex += 1
            elif inputList[currentIndex] == opponent:
                right = opponent
                break
            else:
                break        

        if runLength >= 5:
            value = value + 50000
        else:    
          if left == '.' and right == '.':
            value = value + CREATE_OPEN[runLength]
          if left == '.' and right == opponent:
            value = value + CREATE_CLOSED[runLength]
          if left == opponent and right == '.':
            value = value + CREATE_CLOSED[runLength]

    if moveIndex > 0 and inputList[moveIndex-1] == opponent:
        runLength, left, right = 0, '.', player
        currentIndex = moveIndex-1
        while currentIndex >= -1:
            if currentIndex == -1:
                left = player
                break
            elif inputList[currentIndex] == opponent:
                runLength += 1
                currentIndex -= 1
            elif inputList[currentIndex] == player:
                left = player
                break
            else:
                break

        if runLength > 2:
            if left == '.':
                value = value  + BLOCK_OPEN[runLength]
            if left != '.':
                value = value + BLOCK_CLOSED[runLength]

    if moveIndex < length-1 and inputList[moveIndex+1] == opponent:
        runLength, left, right = 0, player, '.'
        currentIndex = moveIndex+1
        while currentIndex <= length:
            if currentIndex == length:
                right = player
                break
            elif inputList[currentIndex] == opponent:
                runLength += 1
                currentIndex += 1
            elif inputList[currentIndex] == player:
                right = player
                break
            else:
                break

        if runLength > 2:
            if right == '.':
                value = value + BLOCK_OPEN[runLength]
            if right != '.':
                value = value + BLOCK_CLOSED[runLength]

    return value

def evalStone(board, move, currentPlayer, turn):

    horizontal = []
    if currentPlayer == 1:
        horizontal.append('B')
    else:
        horizontal.append('W')
    if move.col > 0:
        currentCol = move.col - 1
        currentRow = move.row
        while currentCol >= 0:
            piece = board.board[currentRow][currentCol]
            horizontal.insert(0, piece)
            if piece == '.':
                break
            currentCol -= 1
    if move.col < board.size - 1:
        currentCol = move.col + 1
        currentRow = move.row
        while currentCol < board.size:
            piece = board.board[currentRow][currentCol]
            horizontal.append(piece)
            if piece == '.':
                break
            currentCol += 1

    vertical = []
    if currentPlayer == 1:
        vertical.append('B')
    else:
        vertical.append('W')
    if move.row > 0:
        currentCol = move.col
        currentRow = move.row - 1
        while currentRow >= 0:
            piece = board.board[currentRow][currentCol]
            vertical.insert(0, piece)
            if piece == '.':
                break
            currentRow -= 1
    if move.row < board.size - 1:
        currentCol = move.col
        currentRow = move.row + 1
        while currentRow < board.size:
            piece = board.board[currentRow][currentCol]
            vertical.append(piece)
            if piece == '.':
                break
            currentRow += 1

    lowToHigh = []
    if currentPlayer == 1:
        lowToHigh.append('B')
    else:
        lowToHigh.append('W')
    if move.row < board.size - 1 and move.col > 0:
        currentCol = move.col - 1
        currentRow = move.row + 1
        while currentCol >= 0 and currentRow < board.size:
            piece = board.board[currentRow][currentCol]
            lowToHigh.insert(0, piece)
            if piece == '.':
                break
            currentCol -= 1
            currentRow += 1
    if move.row > 0 and move.col < board.size - 1:
        currentCol = move.col + 1
        currentRow = move.row - 1
        while currentCol < board.size and currentRow >= 0:
            piece = board.board[currentRow][currentCol]
            lowToHigh.append(piece)
            if piece == '.':
                break
            currentCol += 1
            currentRow -= 1

    highToLow = []
    if currentPlayer == 1:
        highToLow.append('B')
    else:
        highToLow.append('W')
    if move.row > 0 and move.col > 0:
        currentCol = move.col - 1
        currentRow = move.row - 1
        while currentCol >= 0 and currentRow >= 0:
            piece = board.board[currentRow][currentCol]
            highToLow.insert(0, piece)
            if piece == '.':
                break
            currentCol -= 1
            currentRow -= 1
    if move.row < board.size - 1 and move.col < board.size - 1:
        currentCol = move.col + 1
        currentRow = move.row + 1
        while currentCol < board.size and currentRow < board.size:
            piece = board.board[currentRow][currentCol]
            highToLow.append(piece)
            if piece == '.':
                break
            currentCol += 1
            currentRow += 1

    value = 0
    value += getscore(horizontal, currentPlayer) + getscore(vertical, currentPlayer) + getscore(lowToHigh, currentPlayer) + getscore(highToLow, currentPlayer)

    if currentPlayer != turn:
        value *= -1

    return value



def Main():
    game = Gomoku();
    inputfile = open(sys.argv[1], "r")
    game.task = int(inputfile.readline())
    game.player = int(inputfile.readline())
    game.cutoff = int(inputfile.readline())
    game.size = int(inputfile.readline())
    game.initialBoard.size = game.size
    for row in range(game.size):
        temp = inputfile.readline()
        game.initialBoard.board.append( list(temp.strip()) )
    inputfile.close()
    moves = validMoves(game.initialBoard)

    if game.task == 1:
    	greedy(game)
    
    if game.task == 2:
        Minimax(game)
    
    if game.task == 3:
        AlphaBeta(game)



if __name__ == "__main__":
	Main()