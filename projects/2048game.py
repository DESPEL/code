import numpy as np
import neat
import pygame
import pickle
import random

class Game:

    def __init__(self):
        self.game = np.zeros((4,4), dtype=int)
        self.score = 0
        self.add()

    def available(self):
        for row in self.game:
            for val in row:
                if val == 0:
                    return True
        return False

    def add(self):
        if (self.available()):
            pr = random.randrange(0, 4)
            pc = random.randrange(0, 4)
            while self.game[pr][pc] != 0:
                pr = random.randrange(0, 4)
                pc = random.randrange(0, 4)
            self.game[pr][pc] = 2

    def compact(self, board):
        self.movedc = False
        for row in board:
            i = 0
            j = 0
            while i < 4:
                if (row[i] != 0):
                    row[j] = row[i]
                    j += 1
                i += 1
            while j < 4:
                self.movedc = True
                row[j] = 0
                j += 1
        return board

    def merge(self, board, add = True):
        self.movedm = False
        for row in board:
            i = 0
            while i < 3:
                if row[i] != 0 and row[i] == row[i + 1]:
                    row[i] += row[i + 1]
                    if add:
                        self.score += row[i]
                        self.movedm = True
                    j = i + 1
                    while j < 3:
                        # merge
                        row[j] = row[j + 1]
                        j += 1
                    row[3] = 0
                    break
                i += 1
        return board

    def move(self, direction):
        board = np.copy(self.game)
        if (direction == 'u'):
            self.game = np.rot90(self.merge(self.compact(np.rot90(board))), 3)
        elif (direction == 'd'):
            self.game = np.rot90(self.merge(self.compact(np.rot90(board, 3))))
        elif (direction == 'l'):
            self.game = self.merge(self.compact(board))
        elif (direction == 'r'):
            self.game = np.rot90(self.merge(self.compact(np.rot90(board, 2))), 2)
        self.game.add()

test = Game()
test.add()
test.add()
test.add()
test.add()
test.add()
test.add()
test.add()
test.add()

print(test.game)
test.move('l')
print(test.game)
