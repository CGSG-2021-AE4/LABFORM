/* FILENAME: 'main.c'
 * PURPOSE: main file
 * DATE: 15.01.2022
 */

#include <glut.h>

#include "lab.h"

#define FRAME_W 2048
#define FRAME_H 2048
#define PZOOM 3

/* main pixels array */
UCHAR Frame[FRAME_H][FRAME_W][3];

/* put pixel in screen pixels array.
 * ARGUMENTS:
 *   - coords of point.
 *     INT x, y;
 *   - color in rgb.
 *     INT r, g, b;
 * RETURN: None.
 */
VOID PutPixel( INT x, INT y, INT r, INT g, INT b )
{
  if (x > 0 && x < FRAME_W && y > 0 && y < FRAME_H)
  {
    Frame[y][x][0] = b;
    Frame[y][x][1] = g;
    Frame[y][x][2] = r;
  }
} /* end of 'Display' function */

/* draw all on screen.
 * ARGUMENTS: None.
 * RETURN: None.
 */
VOID Display( VOID )
{
  glClearColor(0.0, 0.0, 0.1, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  
  /*PutPixel(100, 100, 255, 255, 255);*/
  LabDrawStart();


  glPixelZoom(PZOOM, -1 * PZOOM);
  glRasterPos2d(-1, 1);
  glDrawPixels(FRAME_W, FRAME_H, GL_BGR_EXT, GL_UNSIGNED_BYTE, Frame);

  glFinish();
  glutSwapBuffers();
  glutPostRedisplay();
} /* end of 'Display' function */


/* calls with keyboard message.
 * ARGUMENTS:
 *   - code of pressing key.
 *     UCHAR Key;
 *   - coords of cursor on the screen.
 *     INT X, Y;
 * RETURN: None.
 */
VOID Keyboard( UCHAR Key, INT X, INT Y )
{
  if (Key == 27)
    exit(0);
  else if (Key == 'f')
    glutFullScreen();
} /* end of 'Keyboard' function */

/* main function of proggram.
 * ARGUMENTS:
 *   - count of strings in argv.
 *     INT argc;
 *   - array of strings.
 *     CHAR **argv;
 * RETURN: None.
 */
VOID main( INT argc, CHAR **argv )
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  glutInitWindowPosition(0, 0);
  glutInitWindowSize(FRAME_W * PZOOM, FRAME_H * PZOOM);
  glutCreateWindow("T20MANDL");
  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);

  LabFormStart();

  glutMainLoop();
} /*end of 'main' function */


/* END OF 'main.c' FILE */