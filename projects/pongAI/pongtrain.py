import neat
import numpy as np
import os
import pygame
import random
import pickle

WIDTH = 800
HEIGHT = 600



BAR_WIDTH = 80
BAR_YPOS = HEIGHT - 20
MAX_SCORE = 300

class Ball:
    def __init__(self):
        self.vx = 10
        self.vy = -10
        self.px = WIDTH/2
        self.py = HEIGHT - 5

    def move(self):
        if self.px <= 0:
            self.vx = 10
        if self.px >= WIDTH:
            self.vx = -10
        if self.py <= 0:
            self.vy = 10
        self.px += self.vx
        self.py += self.vy

class Bar:
    def __init__(self):
        self.WIDTH = BAR_WIDTH
        self.pxi = WIDTH / 2 - self.WIDTH / 2
        self.pxf = WIDTH / 2 + self.WIDTH / 2
        self.py = 780
    
    def move(self, direction):
        if (direction < 0):
            self.pxi -= 10
            self.pxf -= 10
        else:
            self.pxi += 10
            self.pxf += 10

def main(genomes, config):
    score = 0
    ball = Ball()

    nets = []
    ge = []
    bars = []
    
    for _, g in genomes:
        net = neat.nn.FeedForwardNetwork.create(g, config)
        nets.append(net)
        bars.append(Bar())
        g.fitness = 0
        ge.append(g)

    run = True
    while run:
        ball.move()
        for x, bar in enumerate(bars):
            ge[x].fitness += 0.1
            move = nets[x].activate((bar.pxi, bar.pxf, ball.vx, ball.vy, ball.px, ball.py))
            bar.move(move[0])

            if ball.py >= BAR_YPOS:
                ball.vy = -10
                if ball.px >= bar.pxi and ball.px <= bar.pxf:
                    ge[x].fitness += 1
                else:
                    bars.pop(x)
                    nets.pop(x)
                    ge.pop(x)
        if ball.py >= BAR_YPOS:
            score += 1
        if len(bars) == 0 or score >= MAX_SCORE:
            break





def run(config_path):
    config = neat.config.Config(neat.DefaultGenome, neat.DefaultReproduction, neat.DefaultSpeciesSet, neat.DefaultStagnation, config_path)

    p = neat.Population(config)

    p.add_reporter(neat.StdOutReporter(True))
    stats = neat.StatisticsReporter()
    p.add_reporter(stats)

    # fitness function, generations
    winner = p.run(main, 50)

    with open('best-genome.pickle', 'wb') as handle:
        pickle.dump(winner, handle)

if __name__ == "__main__":
    local_dir = os.path.dirname(__file__)
    config_path = os.path.join(local_dir, "config-feedforward.txt")
    run(config_path)
