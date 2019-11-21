import neat
import numpy as numpy
import pickle
import os

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
            self.pyi -= VEL
            self.pyf -= VEL
        else:
            self.pyi += VEL
            self.pyf += VEL

class Ball:
    def __init__(self):
        self.vx = 10
        self.vy = 10
        self.px = WIDTH / 2
        self.py = HEIGHT / 2
    
    def move(self):
        if self.py >= HEIGHT:
            self.vy = -VEL
        if self.py <= 0:
            self.vy = VEL
        self.px += self.vx
        self.py += self.vy

def main(genomes, config):
    ball = Ball()

    nets = []
    ge = []
    bars = []
    i = 0
    for _, g in genomes:
        net = neat.nn.FeedForwardNetwork.create(g, config)
        nets.append(net)
        if i % 2 == 0:
            bars.append(Bar(PXR, True))
        else:
            bars.append(Bar(PXL, False))
        g.fitness = 0
        ge.append(g)
    bounces = 0
    while True:
        ball.move()
        for x, bar in enumerate(bars):
            ge[x].fitness += 0.1
            move = nets[x].activate((bar.pyi, bar.pyf, ball.vx, ball.vy, ball.px, ball.py))
            bar.move(move[0])
            
            if (bar.right) :
                if ball.px >= bar.px:
                    if ball.py <= bar.pyf and ball.py >= bar.pyi:
                        bounces += 1
                        ge[x].fitness += 1
                    else:
                        bars.pop(x)
                        nets.pop(x)
                        ge.pop(x)
            else:
                if ball.px <= bar.px:
                    if ball.py <= bar.pyf and ball.py >= bar.pyi:
                        bounces += 1
                        ge[x].fitness += 1
                    else:
                        bars.pop(x)
                        nets.pop(x)
                        ge.pop(x)

        if ball.px >= PXR:
            ball.vx = -VEL
        if ball.px <= PXL:
            ball.vx = VEL
        if len(bars) == 0 or bounces > MAX_BOUNCES:
            break
        # print(ball.px, ball.py)
        # print(bounces)


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

    q = neat.Population(config)

    q.add_reporter(neat.StdOutReporter(True))
    stats = neat.StatisticsReporter()
    q.add_reporter(stats)
    winner = q.run(main, 50)
    with open('best-genome1.pickle', 'wb') as handle:
        pickle.dump(winner, handle)

if __name__ == "__main__":
    local_dir = os.path.dirname(__file__)
    config_path = os.path.join(local_dir, "config-feedforward.txt")
    run(config_path)
