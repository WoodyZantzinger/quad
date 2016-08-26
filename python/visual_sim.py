import pyglet
from pyglet.gl import *

class Window(pyglet.window.Window):

    roll = 0.0
    pitch = 0.0

    def __init__(self, width, height, title=''):
        super(Window, self).__init__(width, height, title)

        glClearColor(0, 0, 0, 1)
        glEnable(GL_DEPTH_TEST)

    def on_show(self):
        pyglet.gl.glClear(pyglet.gl.GL_COLOR_BUFFER_BIT | pyglet.gl.GL_DEPTH_BUFFER_BIT)
        # Set up projection matrix.
        pyglet.gl.glMatrixMode(pyglet.gl.GL_PROJECTION)
        pyglet.gl.glLoadIdentity()
        pyglet.gl.gluPerspective(45.0, float(self.width)/self.height, 0.1, 360)

    def on_draw(self):

        pyglet.gl.glMatrixMode(pyglet.gl.GL_MODELVIEW)
        pyglet.gl.glLoadIdentity()

        pyglet.gl.glTranslatef(0, 0, -8)

        pyglet.gl.glRotatef(self.roll, 0, 0, 1)
        pyglet.gl.glRotatef(self.pitch * -1, 1, 0, 0)

        self.clear()
        pyglet.gl.glColor4f(1.0,0,0,1.0)

        pyglet.gl.glLineWidth(2)
        pyglet.graphics.draw_indexed(8, pyglet.gl.GL_LINES, [0, 1, 1, 2, 2, 3, 3, 0,# top square
                                                             4, 5, 5, 6, 6, 7, 7, 4,# back square
                                                             0, 4, 1, 5, 2, 6, 3, 7],# connectors
                               ('v3f', (-1, -.3, -1,
                                        1, -.3, -1,
                                        1, .3, -1,
                                        -1, .3, -1,
                                        -1, -.3, 1,
                                        1, -.3, 1,
                                        1, .3, 1,
                                        -1, .3, 1)))
            #label.draw()
