#include "physics.h"
#include "math.h"
#include "stdlib.h"










/*
  The space is almost always *mostly* sorted, and tends to get unsorted in very
  predictable ways. As a result, I think a heavily optimized, practically O(1)
  approach should be possible, or at least O(Δn)

  For now, bubble sort will suffice, as it actually has good performance on
  mostly-sorted arrays.
*/
void sortSpace(PHYSICSBUFFER* buff){
  if(!buff->hasMoved) return;




}










void cellCollide(CELLOBJ* a, CELLOBJ* b, CELLOBJ* qa, CELLOBJ* qb){

  int abdistsq = ((a-> x-b-> x)*(a-> x-b-> x)) + ((a-> y-b-> y)*(a-> y-b-> y)) + ((a-> z-b-> z)*(a-> z-b-> z));
  int abmovesq = ((a->dx-b->dx)*(a->dx-b->dx)) + ((a->dy-b->dy)*(a->dy-b->dy)) + ((a->dz-b->dz)*(a->dz-b->dz));

  float abdist = sqrt((float)abdistsq);
  float abmove = sqrt((float)abmovesq);

  if(abdist-(a->size+b->size) > abmove) return;   // No collision possible


  float ax  = (float)a-> x, ay  = (float)a-> y, az  = (float)a-> z;
  float bx  = (float)b-> x, by  = (float)b-> y, bz  = (float)b-> z;

  float adx = (float)a->dx, ady = (float)a->dy, adz = (float)a->dz;
  float bdx = (float)b->dx, bdy = (float)b->dy, bdz = (float)b->dz;



}










inline void moveCell(CELLOBJ* c){
  int x = c->x + c->dx;
  int y = c->y + c->dy;
  int z = c->z + c->dz;

  x = (x < -32767)? -32767 : (x > 32767)? 32767 : x;
  y = (y < -32767)? -32767 : (y > 32767)? 32767 : y;
  z = (z < -32767)? -32767 : (z > 32767)? 32767 : z;

  c->x = x;
  c->y = y;
  c->z = z;
}










/*
  This function should eventually do the following:
    * Move cells
    * Collision detection
    * Glue physics

  If performance is an issue:
    * Improve cache patterning (9x bandwidth required right now?)
*/
void moveCells(PHYSICSBUFFER* buff){

  // Simple for now
  for(int i = 0; i < buff->size; i++){
    buff->newcellsobjs[i] = buff->oldcellsobjs[i];
    buff->newcellsobjs[i].dy += (buff->newcellsobjs[i].dy > 126)? 0 : 1;

    moveCell(&buff->newcellsobjs[i]);
  }


  CELLOBJ* tmp = buff->oldcellsobjs;
  buff->oldcellsobjs = buff->newcellsobjs;
  buff->newcellsobjs = tmp;
}










PHYSICSBUFFER* randomBuffer(int size){
  PHYSICSBUFFER* ret = malloc(sizeof(PHYSICSBUFFER));
  ret->oldcellsobjs  = malloc(sizeof(CELLOBJ) * size);
  ret->newcellsobjs  = malloc(sizeof(CELLOBJ) * size);

  uint64_t rstate = 16578936171;
  for(int i = 0; i < size; i++){
    rstate = (37567891 * rstate) + 719865781;
    ret->oldcellsobjs[i].x = (rstate >> 16);
    rstate = (37567891 * rstate) + 719865781;
    ret->oldcellsobjs[i].y = (rstate >> 16);
    rstate = (37567891 * rstate) + 719865781;
    ret->oldcellsobjs[i].z = (rstate >> 16);

    ret->oldcellsobjs[i].dx = 0;
    ret->oldcellsobjs[i].dy = 0;
    ret->oldcellsobjs[i].dz = 0;

    ret->newcellsobjs[i] = ret->oldcellsobjs[i];
  }

  ret->size = size;
  return ret;
}
