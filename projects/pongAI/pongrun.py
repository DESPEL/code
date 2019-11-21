import neat
import numpy as np
import os
import pygame
import random
import pickle
pygame.font.init()

WIDTH = 800
HEIGHT = 600

BALL_IMAGE = pygame.image.load(os.path.join('images', 'ball.png'))
BAR_IMAGE = pygame.image.load(os.path.join('images', 'bar.png'))
BG_IMAGE = pygame.image.load(os.path.join('images', 'bg.png'))
STAT_FONT = pygame.font.SysFont("comicsans", 50)

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
    
    def draw(self, win):
        win.blit(BALL_IMAGE, (self.px, self.py))

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
    
    def draw(self, win):
        win.blit(BAR_IMAGE, (self.pxi, BAR_YPOS))

def draw_window(win, bar, ball, score):
    win.blit(BG_IMAGE, (0,0))

    text = STAT_FONT.render("Score: " + str(score), 1, (255, 255, 255))
    win.blit(text, (10, text.get_height() + 10))

    ball.draw(win)
    bar.draw(win)

    pygame.display.update()

def main(genome, config):
    score = 0
    ball = Ball()

    win = pygame.display.set_mode((WIDTH, HEIGHT))
    clock = pygame.time.Clock()

    net = neat.nn.FeedForwardNetwork.create(genome, config)
    bar = Bar()

    run = True
    while run:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False          
                pygame.quit()
                quit()
        clock.tick(30)
        ball.move()
        move = net.activate((bar.pxi, bar.pxf, ball.vx, ball.vy, ball.px, ball.py))
        bar.move(move[0])

        if ball.py >= BAR_YPOS:
            if not ball.px >= bar.pxi and ball.px <= bar.pxf:
                break
            else:
                ball.vy = -10
                score += 1
        print("e")
        draw_window(win, bar, ball, score)
        print("f")

def run(config_path):
    config = neat.config.Config(neat.DefaultGenome, neat.DefaultReproduction, neat.DefaultSpeciesSet, neat.DefaultStagnation, config_path)

    with open('best-genome.pickle', 'rb') as handle:
        winner = pickle.load(handle)
    main(winner, config)


if __name__ == "__main__":
    local_dir = os.path.dirname(__file__)
    config_path = os.path.join(local_dir, "config-feedforward.txt")
    run(config_path)
