#include "seriefactory.h"
#include <GL/glut.h>
#include <random>
#include <iterator>
#include <iostream>

void SerieFactory::paint()
{
  for (Sprite elem : mVectorSerie)
  {
    elem.setTexture(0,1,20);
    elem.paint();
  }
}

void SerieFactory::generate ()
{
  // Block initial position.
  blockMapPosition(mSx,mSy);

  // Sprite neighborgs.
  addNeighborgs(mSx,mSy);

  emptyVisit();
}
void SerieFactory::emptyVisit ()
{
  if (mVisit.size() != 0) // Final condition.
  {
    size_t i = (size_t) rand() % mVisit.size();
    auto it = mVisit.begin();
    auto choice = std::next(it,i);
    size_t rx = (*choice).x;
    size_t ry = (*choice).y;
    putSprite(rx, ry, mFuncSerie); // put next serie sprite
    mVisit.erase(choice); // remove element
    addNeighborgs(rx,ry);// calculate neighborgs

    emptyVisit(); // Recursive call.
  }
}
void SerieFactory::putSprite(size_t x, size_t y, std::function<int(int)> fSerie)
{
  int value = fSerie(mCurrent++);
  mVectorSerie.push_back(Sprite(mSpriteSide,x,y,value,mBlockSide));

  std::cout << "Add sprite ("<<x<<","<<y<<")serie for x(" << mCurrent - 1 << ") = " << value << std::endl;
}

void SerieFactory::addElem(size_t x, size_t y) {
  if (!mScreen.getPos(x,y))
  {
    mVisit.push_back(Position2D(x,y));
    blockMapPosition(x,y); // TODO: Put in map walls in elem position.
  }
}

// fullfill a sprite position with "1" (WALL).
void SerieFactory::blockMapPosition(size_t x, size_t y)
{
  for (size_t ix = 0; ix < mBlockPerSprite; ix++)
  {
    for (size_t iy = 0; iy < mBlockPerSprite; iy++)
    {
      mScreen.setWall(x + ix, y + iy);
    }
  }
}

void SerieFactory::addNeighborgs(size_t x, size_t y)
{
  size_t rx;
  size_t ry;
  // Up
  rx = x;
  ry = y + mBlockPerSprite;
  addElem(rx,ry);
  // Right
  rx = x + mBlockPerSprite;
  ry = y;
  addElem(rx,ry);
  // Down
  rx = x;
  ry = y - mBlockPerSprite;
  if (mScreen.inLimits(rx,ry))
    addElem(rx,ry);
  // Left
  rx = x - mBlockPerSprite;
  ry = y;
  if (mScreen.inLimits(rx,ry))
    addElem(rx,ry);
}
