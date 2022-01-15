/* FILENAME: 'lab.h'
 * PURPOSE: lab h-file
 * DATE: 15.01.2022
 */

#ifndef __LAB_H_
#define __LAB_H_

/* includes */
#include <commondf.h>

/* lab struct */
typedef struct tagLAB LAB;
struct tagLAB
{
  /* point coords */
  POINT P;
  LAB *N[4];
};


/* function prototipes */
VOID PutPixel( INT x, INT y, INT r, INT g, INT b );

/* lab functions prototipes */
VOID LabFormStart( VOID );
VOID LabDrawStart( VOID );

#endif /* __LAB_H_ */

/* END OF 'lab.h' FILE */
