#include "seriefactory.h"
#include <GL/glut.h>

void SerieFactory::paint()
{
  for (Sprite elem : mVectorSerie)
  {
    elem.paint();
  }
}

void SerieFactory::generate ()
{
  // TODO: use 2 lists.
  // One to push the nodes to visit
  // The other to insert the random choice
  // When a position is choosed then insert in One
  // the adjacent positions to this one.
}
