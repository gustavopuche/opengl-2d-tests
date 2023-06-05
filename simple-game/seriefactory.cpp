#include "seriefactory.h"
#include <GL/glut.h>
#include <random>

void SerieFactory::paint()
{
  for (Sprite elem : mVectorSerie)
  {
    elem.paint();
  }
}

void SerieFactory::generate ()
{
  // Sprite neighborgs.
  addNeighborgs(x,y);

  emptyVisit();
}
void SerieFactory::emptyVisit ()
{
  if (mVisit.size() != 0)
  {
    size_t i = (size_t) rand() % mVisit.size();
    // remove element
    // put next serie sprite
    // calculate neighborgs
  }
}

void SerieFactory::addElem(size_t x, size_t y) {
  if (mMap[y][x] == 0)
  {
    mVisit.push_back(Position2D(x,y));
    blockMapPosition(x,y); // TODO: Put in map walls in elem position.
  }
}

void SerieFactory::addNeighborgs(size_t x, size_t y)
{
  size_t rx;
  size_t ry;
  // Up
  rx = x;
  ry = mMapSide - 1 - y - mBlockPerSprite;
  addElem(rx,ry);
  // Right
  rx = x + mBlockPerSprite;
  ry = ry;
  addElem(rx,ry);
  // Down
  rx = x;
  ry = mMapSide - 1 - y + 1;
  addElem(rx,ry);
  // Left
  rx = x - 1;
  ry = ry;
  addElem(rx,ry);
}
