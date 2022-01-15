/* FILENAME: 'lab.c'
 * PURPOSE: lab formation and draw functions
 * DATE: 15.01.2022
 */

#include <stdio.h>
#include "lab.h"

/* size of lab field */
#define LabW 100
#define LabH 70

/* Global variables */
LAB *Lab; /* main lab tree */
BOOL LWas[LabH][LabW]; /* array to know where you already was */

POINT delta[] =
  {
    {1, 0},
    {0, -1},
    {-1, 0},
    {0, 1}
  }; /* array of delta by x and y */

/* making array of rand num without repite function.
 * ARGUMENTS:
 *   - array.
 *     INT *A;
 *   - size of array.
 *     INT max;
 * RETURNS: None.
 */
VOID RandA( INT *A, INT max )
{
  INT i, j, IsRep;

  if (A == NULL)
    return;

  memset(A, 0, max * sizeof(A[0])); /* clear array */

  for (i = 0; i < max; i++)
  {
    do
    {
      IsRep = 0;
      A[i] = rand() % max;

      for (j = 0; j < i; j++) /* search repite */
        if (A[i] == A[j])
          IsRep = 1;

    } while (IsRep == 1);
  }
  /* bad version but easy and working */

} /* end of 'RandA' function */

/* draw lab by graf function.
 * ARGUMENTS:
 *   - position in lab graf.
 *   LAB *L;
 *   - privios point position.
 *   POINT OldPos;
 * RETURNS: None.
 */
VOID DrawLab( LAB *L, POINT OldPos )
{
  INT i;
  
  /* draw tunnel */
  PutPixel(2 * OldPos.x + 1, 2 * OldPos.y + 1, 255, 255, 255);
  PutPixel(OldPos.x + L->P.x + 1, OldPos.y + L->P.y + 1, 255, 255, 255);
  PutPixel(2 * L->P.x + 1, 2 * L->P.y + 1, 255, 255, 255);
  /* tunnels in the lab are white */

  /* recursion to draw other points in the lab tree */
  for (i = 0; i < 4; i++)
  {
    if (L->N[i] != NULL)
      DrawLab(L->N[i], L->P);
  }
} /* end of 'DrawLab' function */

/* lab fromaion recursion function.
 * ARGUMENTS:
 *   - position in lab graf.
 *   LAB *L;
 *   - point position.
 *   POINT Pos;
 * RETURNS: None.
 */
VOID LabFormGo( LAB *L, POINT Pos )
{
  INT i;
  POINT SPos; /* temp new pos */
  INT RD[4]; /* array of rand diretions */

  if (L == NULL)
    return;

  LWas[Pos.y][Pos.x] = 1; /* say that we was here */

  memset(L->N, 0, sizeof(L->N[0]) * 4); /* clear next points */
  L->P = Pos; /* set our position */

  RandA(RD, 4); /* make rand directions */

  /*printf("X: %03i\tY: %03i\n", Pos.x, Pos.y);*/
  
  for (i = 0; i < 4; i++)
  {
    SPos.x = Pos.x + delta[RD[i]].x;
    SPos.y = Pos.y + delta[RD[i]].y;

    if (SPos.x >= 0 && SPos.x < LabW && SPos.y >= 0 && SPos.y < LabH && LWas[SPos.y][SPos.x] == 0)
    {
      if ((L->N[RD[i]] = malloc(sizeof(LAB *))) == NULL) /* check for no mem */
      {
        printf("ERROR: Stack over flow\n");
        getchar();
        return;
      }
      LabFormGo(L->N[RD[i]], SPos); /* next point */
    }
  }
} /* end of 'LabFormGo' function */

/* lab fromaion start function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID LabFormStart( VOID )
{
  memset(LWas, 0, sizeof(BOOL) * LabW * LabH); /* clear LWas */

  Lab = malloc(sizeof(LAB *)); /* make Lab */

  /* set our first postion (in the future, it can be arguments)*/
  Lab->P.x = 0;
  Lab->P.y = 0;

  LabFormGo(Lab, Lab->P); /* recursion */
} /* end of 'LabFormStart' function */

/* lab draw start function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID LabDrawStart( VOID )
{
  DrawLab(Lab, Lab->P); /* it because i don't want to make Lab like global variable */
} /* end of 'LabDrawStart' function */

/* END OF 'lab.c' FILE */