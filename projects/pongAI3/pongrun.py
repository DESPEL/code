import neat
import numpy as numpy
import pickle
import os
import pygame
import math
import random
pygame.font.init()

BALL_IMAGE = pygame.image.load(os.path.join('images', 'ball.png'))
BAR_IMAGE = pygame.image.load(os.path.join('images', 'bar.png'))
BG_IMAGE = pygame.image.load(os.path.join('images', 'bg.png'))
STAT_FONT = pygame.font.SysFont("comicsans", 50)
STAT_FONT_S = pygame.font.SysFont("comicsans", 30)

WIDTH = 800
HEIGHT = 600

red = (200, 0, 0)
green = (0, 200, 0)

bright_red = (255, 0, 0)
bright_green = (0, 255, 0)

block_color = (53, 115, 255)


WIN_HEIGHT = HEIGHT + 50
MAX_BOUNCES = 100

BAR_WIDTH = HEIGHT / 10
PXL = 20
PXR = WIDTH - 20

VEL = 10

MAX_VEL_BAR = 10


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
            self.pyi -= MAX_VEL_BAR  # * direction
            self.pyf -= MAX_VEL_BAR  # * direction
        else:
            if self.pyf >= HEIGHT:
                return
            self.pyi += MAX_VEL_BAR  # * direction
            self.pyf += MAX_VEL_BAR  # * direction

    def draw(self, win):
        win.blit(BAR_IMAGE, (self.px, self.pyi))


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
        self.px += self.vx
        self.py += self.vy
        if (self.px <= 20):
            self.px = 20
        if (self.px >= WIDTH - 20):
            self.px = WIDTH - 20

    def draw(self, win):
        win.blit(BALL_IMAGE, (self.px, self.py))


def draw_window(win, barl, barr, ball, scorel, scorer, bounces):
    win.blit(BG_IMAGE, (0, 0))

    text = STAT_FONT.render("Score: " + str(scorel), 1, (255, 255, 255))
    win.blit(text, (10, 10))
    text = STAT_FONT.render("Score: " + str(scorer), 1, (255, 255, 255))
    win.blit(text, (WIDTH - text.get_width() - 10, 10))
    text = STAT_FONT.render("Rebotes: " + str(bounces), 1, (255, 255, 255))
    win.blit(text, (WIDTH / 2 - (text.get_width() / 2), 10))
    test = STAT_FONT_S.render(
        "Proyecto: Pong IA (NEAT), Autores: Marcos Moroyoqui, David Espina", 1, (255, 255, 255))
    win.blit(test, (10, WIN_HEIGHT - (test.get_height() * 2)))
    test = STAT_FONT_S.render(
        "Observaciones: La IA se entrena por separado", 1, (255, 255, 255))
    win.blit(test, (10, WIN_HEIGHT - (test.get_height())))
    ball.draw(win)
    barl.draw(win)
    barr.draw(win)

    pygame.display.update()


def main(genomel, genomer, config):
    
    win = pygame.display.set_mode((WIDTH, WIN_HEIGHT))
    clock = pygame.time.Clock()
    def text_objects(text, font):
        textSurface = font.render(text, True, (0, 0, 0))
        return textSurface, textSurface.get_rect()

    def quitgame():
        pygame.quit()
        quit()

    def button(msg, x, y, w, h, ic, ac, action=None):
        mouse = pygame.mouse.get_pos()
        click = pygame.mouse.get_pressed()

        if x+w > mouse[0] > x and y+h > mouse[1] > y:
            pygame.draw.rect(win, ac, (x, y, w, h))
            if click[0] == 1 and action != None:
                action()
        else:
            pygame.draw.rect(win, ic, (x, y, w, h))
            smallText = pygame.font.SysFont("comicsansms", 20)
            textSurf, textRect = text_objects(msg, smallText)
            textRect.center = ((x+(w/2)), (y+(h/2)))
            win.blit(textSurf, textRect)

    def crash(mensaje):
        largeText = pygame.font.SysFont("comicsansms", 80)
        TextSurf, TextRect = text_objects(mensaje , largeText)
        TextRect.center = ((WIDTH/2), (HEIGHT/2))
        win.blit(TextSurf, TextRect)
        while True:
            for event in pygame.event.get():
                # print(event)
                if event.type == pygame.QUIT:
                    pygame.quit()
                    quit()

            # gameDisplay.fill(white)

            button("Play Again", 150, 450, 100, 50,
                   green, bright_green, game_loop)
            button("Quit", 550, 450, 100, 50, red, bright_red, quitgame)

            pygame.display.update()
            clock.tick(15)

    def game_loop():
        def sign(x): return (1, -1)[x < 0]
        ball = Ball()


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

            movel = netl.activate(
                (barl.pyi, barl.pyf, ball.vx, ball.vy, ball.px, ball.py))
            mover = netr.activate(
                (barr.pyi, barr.pyf, ball.vx, ball.vy, ball.px, ball.py))
            # mover = [-1]
            barl.move(movel[0])
            barr.move(mover[0])
            if ball.px >= barr.px:
                if ball.py <= barr.pyf and ball.py >= barr.pyi:
                    # ball.vy *= math.sin(((ball.py - (barr.pyi + barr.pyf) / 2) / 60) * math.pi)
                    ball.vx = -(abs(ball.vx) + VEL) * abs(math.cos(((ball.py -
                                                                    ((barr.pyi + barr.pyf) / 2)) / 60) * (math.pi / 2)))
                    print("v1:", math.cos(
                        ((ball.py - ((barr.pyi + barr.pyf) / 2)) / 60) * (math.pi / 2)))
                    if (ball.vx > -5):
                        ball.vx = -5
                    bounces += 1
                else:
                    pl += 1
                    ball = Ball()
            if ball.px <= barl.px:
                if ball.py <= barl.pyf and ball.py >= barl.pyi:
                    # ball.vy *= math.sin(((ball.py - (barr.pyi + barr.pyf) / 2) / 60) * math.pi)
                    ball.vx = (abs(ball.vx) + VEL) * abs(math.cos(((ball.py -
                                                                    (barr.pyi + barr.pyf) / 2) / 60) * (math.pi / 2)))
                    print("v2:", math.cos(
                        ((ball.py - ((barl.pyi + barl.pyf) / 2)) / 60) * (math.pi / 2)))
                    if (ball.vx < 5):
                        ball.vx = 5
                    bounces += 1
                else:
                    pr += 1
                    ball = Ball()
            #print (ball.vx)
            #print (barr.pyf + barr.pyi / 2)
            if ball.vx == 0:
                print("zero vx")

            ball.move()
            # print(ball.px, ball.py)
            # print(bounces)
            if pr > 21:
                break
            if pl > 21:
                break
            draw_window(win, barl, barr, ball, pl, pr, bounces)
            if (bounces >= MAX_BOUNCES):
                crash("EMPATE")
        crash("You WIN: derecha" if pl <= pr else "You WIN: izquierda")
    
    game_loop()

def run(config_path):
    config = neat.config.Config(neat.DefaultGenome, neat.DefaultReproduction,
                                neat.DefaultSpeciesSet, neat.DefaultStagnation, config_path)

    with open('best-genomeFalse.pickle', 'rb') as handle:
        winner1 = pickle.load(handle)
    with open('best-genomeTrue.pickle', 'rb') as handle:
        winner2 = pickle.load(handle)
    main(winner1, winner2, config)


if __name__ == "__main__":
    local_dir = os.path.dirname(__file__)
    config_path = os.path.join(local_dir, "config-feedforward.txt")
    run(config_path)
