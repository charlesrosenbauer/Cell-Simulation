#ifndef __PHYSICS_HEADER__
#define __PHYSICS_HEADER__


#include "math.h"
#include "stdint.h"













typedef struct{
  int32_t id, stk[4], sector;
  int16_t x, y, z;
  int8_t  flex, stick, dx, dy, dz, size, pressure;
}CELLOBJ;










typedef struct{
  CELLOBJ* oldcellsobjs;
  CELLOBJ* newcellsobjs;
  int size;
  int hasMoved;
  uint32_t posIndices[64][64][64];
}PHYSICSBUFFER;










void moveCells(PHYSICSBUFFER*);
void sortSpace(PHYSICSBUFFER*);
PHYSICSBUFFER* randomBuffer(int);



#endif
