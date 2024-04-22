import sys
import pygame
from pygame.locals import *
from OpenGL.GLU import *
from OpenGL.GL import *
sys.path.append('..')
from res.Cube import wireCube

pygame.init()

# Project settings
screen_width = 900
screen_height = 600
background_color = (0, 0, 0, 1)
drawing_color = (1, 1, 1, 1)

screen = pygame.display.set_mode(
    (screen_width, screen_height), DOUBLEBUF | OPENGL)

clock = pygame.time.Clock()


def initialise():
    glClearColor(background_color[0], background_color[1],
                 background_color[2], background_color[3])
    glColor(drawing_color)

    # Projection
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(60, (screen_width / screen_height), 0.1, 100.0)

    # Model View
    glMatrixMode(GL_MODELVIEW)
    glTranslate(0, 0, -5)
    glLoadIdentity()
    glViewport(0, 0, screen.get_width(), screen.get_height())
    glEnable(GL_DEPTH_TEST)
    glTranslate(0, 0, -2)


def display():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glRotatef(1, 10, 0, 1)
    glPushMatrix()
    wireCube()
    glPopMatrix()


done = False
initialise()
while not done:
    clock.tick(60) / 1000
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            done = True
    display()
    pygame.display.flip()
    pygame.display.set_caption(f"{clock.get_fps():.0f} fps")
pygame.quit()