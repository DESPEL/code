import neat
import numpy as numpy
import pickle
import os
import pygame
pygame.font.init()

BALL_IMAGE = pygame.image.load(os.path.join('images', 'ball.png'))
BAR_IMAGE = pygame.image.load(os.path.join('images', 'bar.png'))
BG_IMAGE = pygame.image.load(os.path.join('images', 'bg.png'))
STAT_FONT = pygame.font.SysFont("comicsans", 50)


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

    def draw(self, win):
        win.blit(BAR_IMAGE, (self.px, self.pyi))

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

    def draw(self, win):
        win.blit(BALL_IMAGE, (self.px, self.py))

def draw_window(win, barl, barr, ball, scorel, scorer, bounces):
    win.blit(BG_IMAGE, (0,0))

    text = STAT_FONT.render("Score: " + str(scorel), 1, (255, 255, 255))
    win.blit(text, (10, 10))
    text = STAT_FONT.render("Score: " + str(scorer), 1, (255, 255, 255))
    win.blit(text, (WIDTH - text.get_width() - 10, 10))
    text = STAT_FONT.render("Rebotes: " + str(bounces), 1, (255, 255, 255))
    win.blit(text, (WIDTH / 2 - (text.get_width() / 2), 10))

    ball.draw(win)
    barl.draw(win)
    barr.draw(win)

    pygame.display.update()

def main(genomel, genomer, config):
    ball = Ball()

    win = pygame.display.set_mode((WIDTH, HEIGHT))
    clock = pygame.time.Clock()

    barr = Bar(PXR, True)
    barl = Bar(PXL, False)

    netr = neat.nn.FeedForwardNetwork.create(genomer, config)
    netl = neat.nn.FeedForwardNetwork.create(genomel, config)
    

    bounces = 0
    pl = 0
    pr = 0
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False          
                pygame.quit()
                quit()
        clock.tick()

        movel = netl.activate((barl.pyi, barl.pyf, ball.vx, ball.vy, ball.px, ball.py))
        mover = netr.activate((barr.pyi, barr.pyf, ball.vx, ball.vy, ball.px, ball.py))
        barl.move(movel[0])
        barr.move(mover[0])

        if ball.px >= barr.px:
            if ball.py <= barr.pyf and ball.py >= barr.pyi:
                ball.vx = -VEL
                bounces += 1
            else:
                pl += 1
                ball = Ball()
        if ball.px <= barl.px:
            if ball.py <= barl.pyf and ball.py >= barl.pyi:
                ball.vx = VEL
                bounces += 1
            else:
                pr += 1
                ball = Ball()
        # print(ball.px, ball.py)
        # print(bounces)
        if pr > 21:
            break
        if pl > 21:
            break
        ball.move()
        draw_window(win, barl, barr, ball, pl, pr, bounces)
    


def run(config_path):
    config = neat.config.Config(neat.DefaultGenome, neat.DefaultReproduction, neat.DefaultSpeciesSet, neat.DefaultStagnation, config_path)

    with open('best-genome.pickle', 'rb') as handle:
        winner1 = pickle.load(handle)
    with open('best-genome1.pickle', 'rb') as handle:
        winner2 = pickle.load(handle)
    main(winner1, winner2, config)

if __name__ == "__main__":
    local_dir = os.path.dirname(__file__)
    config_path = os.path.join(local_dir, "config-feedforward.txt")
    run(config_path)
