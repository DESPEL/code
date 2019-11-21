import neat
import numpy as numpy
import pickle
import os
import math
import random

WIDTH = 800
HEIGHT = 600

MAX_BOUNCES = 500

BAR_WIDTH = HEIGHT / 10
PXL = 20
PXR = WIDTH - 20

VEL = 10

class Bar:
    def __init__(self, px, right):
        self.px = px
        self.pyi = HEIGHT / 2 - BAR_WIDTH / 2
        self.pyf = HEIGHT / 2 + BAR_WIDTH / 2
        self.right = right

    def move(self, direction):
        if direction < 0:
            if self.pyi <= 0:
                return
            self.pyi -= VEL
            self.pyf -= VEL
        else:
            if self.pyf >= HEIGHT:
                return
            self.pyi += VEL
            self.pyf += VEL

class Ball:
    def __init__(self):
        self.vx = 20
        self.vy = 10
        self.px = WIDTH / 2
        self.py = HEIGHT / 2
    
    def move(self):
        if self.py >= HEIGHT:
            self.vy = -self.vy
        if self.py <= 0:
            self.vy = -self.vy
        #if self.py >= HEIGHT:
        #    self.vy = -VEL
        #if self.py <= 0:
        #    self.vy = VEL
        self.px += self.vx
        self.py += self.vy

der = False
#der = True
def main(genomes, config):
    global der
    balls = []

    nets = []
    ge = []
    bars = []
    for _, g in genomes:
        balls.append(Ball())
        net = neat.nn.FeedForwardNetwork.create(g, config)
        nets.append(net)
        if der:
            bars.append(Bar(PXR ,der))
        else:
            bars.append(Bar(PXL ,der))
        g.fitness = 0
        ge.append(g)
    bounces = 1
    while True:
        for x, bar in enumerate(bars):
            balls[x].move()
            ge[x].fitness += 0.1
            move = nets[x].activate((bar.pyi, bar.pyf, balls[x].vx, balls[x].vy, balls[x].px, balls[x].py))
            bar.move(move[0])
            
            if (bar.right) :
                if balls[x].px >= bar.px:
                    if balls[x].py <= bar.pyf and balls[x].py >= bar.pyi:
                        bounces += 1
                        ge[x].fitness += (abs(balls[x].vx) - 5) * math.log10(bounces)
                    else:
                        ge[x].fitness -= abs(balls[x].vx)
                        bars.pop(x)
                        nets.pop(x)
                        ge.pop(x)
            else:
                if balls[x].px <= bar.px:
                    if balls[x].py <= bar.pyf and balls[x].py >= bar.pyi:
                        bounces += 1
                        ge[x].fitness += (abs(balls[x].vx) - 5) * math.log10(bounces)
                    else:
                        ge[x].fitness -= abs(balls[x].vx)
                        bars.pop(x)
                        nets.pop(x)
                        ge.pop(x)

            if balls[x].px >= PXR and bar.right:
                #balls[x].vx = VEL * math.sin(((balls[x].py - (bar.pyi + bar.pyf) / 2) / 60) * math.pi) + 0.5
                balls[x].vx = -(abs(balls[x].vx) + VEL) * abs(math.cos(((balls[x].py - (bar.pyi + bar.pyf) / 2) / 60) * (math.pi / 2)))
                if (balls[x].vx > -5):
                    balls[x].vx = -5
            if balls[x].px <= PXL and bar.right:
                balls[x].vx = -(abs(balls[x].vx) + VEL) * abs(math.cos(((random.randrange(1 ,60)) / 60) * (math.pi / 2)))
                if (balls[x].vx < 5):
                    balls[x].vx = 5
            if balls[x].px >= PXR and not bar.right:
                balls[x].vx = -(abs(balls[x].vx) + VEL) * abs(math.cos(((random.randrange(1 ,60)) / 60) * (math.pi / 2)))
                if (balls[x].vx > -5):
                    balls[x].vx = -5
            if balls[x].px <= PXL and not bar.right:
                #balls[x].vx = -VEL * math.sin(((balls[x].py - (bar.pyi + bar.pyf) / 2) / 60) * math.pi) + 0.5
                balls[x].vx = -(abs(balls[x].vx) + VEL) * abs(math.cos(((balls[x].py - (bar.pyi + bar.pyf) / 2) / 60) * (math.pi / 2)))
                if (balls[x].vx < 5):
                    balls[x].vx = 5
        
        if len(bars) == 0 or bounces > MAX_BOUNCES:
            break
        # print(ball.px, ball.py)
        # print(bounces)
    print(bounces)


def run(config_path):
    config = neat.config.Config(neat.DefaultGenome, neat.DefaultReproduction, neat.DefaultSpeciesSet, neat.DefaultStagnation, config_path)

    p = neat.Population(config)

    p.add_reporter(neat.StdOutReporter(True))
    stats = neat.StatisticsReporter()
    p.add_reporter(stats)
    global der
    # fitness function, generations
    winner = p.run(main)
    with open('best-genome' + str(der) + '.pickle', 'wb') as handle:
        pickle.dump(winner, handle)
    """
    global der 
    der = True

    q = neat.Population(config)

    q.add_reporter(neat.StdOutReporter(True))
    stats = neat.StatisticsReporter()
    q.add_reporter(stats)
    winner = q.run(main, 50)
    with open('best-genome1.pickle', 'wb') as handle:
        pickle.dump(winner, handle)
    """

if __name__ == "__main__":
    local_dir = os.path.dirname(__file__)
    config_path = os.path.join(local_dir, "config-feedforward.txt")
    run(config_path)
