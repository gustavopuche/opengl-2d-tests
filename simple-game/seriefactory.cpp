#include "seriefactory.h"
#include <GL/glut.h>
#include <random>
#include <iterator>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <iterator> // std::distance

void SerieFactory::paint()
{
  for (Sprite elem : mListSerie)
  {
    elem.setTexture(0,1).paint().paintValue();
  }
}

// Generate all serie sprites
void SerieFactory::generate ()
{
  // Block initial position.
  blockMapPosition(mSx,mSy);

  // Sprite neighborgs.
  addNeighborgs(mSx,mSy);

  emptyVisit();

  // Debug.
  mScreen.dump();
}

void SerieFactory::generateFluentHoles()
{
  size_t x = mSx;
  size_t y = mSy;

  PositionDirection posDir;

  // Block initial position.
  blockMapPosition(x,y);

  // Get possible directions unsorted.
  possibleDirections(x, y);

  while (!mStackDir.empty());
  {
    // put next serie sprite.
    putSprite(x, y, mFuncSerie);

    posDir = mStackDir.top();
    mStackDir.pop();

    // Update position.
    MoveTo(posDir,x,y);

    // Block initial position.
    blockMapPosition(x,y);

    // Get possible directions unsorted.
    possibleDirections(x, y);
  }
}

void SerieFactory::MoveTo(PositionDirection posd, size_t& x, size_t& y)
{
  // Update position if no way.
  x = posd.position.x;
  y = posd.position.y;

  // Move to new position.
  switch(posd.direction){
   case SerieDirection::LEFT:
     x = x - 1;
    break;
   case SerieDirection::RIGHT:
     x = x + 1;
     break;
   case SerieDirection::UP:
     y = y + 1;
     break;
   case SerieDirection::DOWN:
     y = y - 1;
     break;
  }
}

size_t SerieFactory::possibleDirections(size_t x, size_t y)
{
  size_t result = 0;
  std::list<SerieDirection> directions = {
    SerieDirection::LEFT,
    SerieDirection::RIGHT,
    SerieDirection::UP,
    SerieDirection::DOWN};

  PositionDirection posDir;

  while (directions.size() != 0)
  {
    size_t i = (size_t) rand() % directions.size();
    auto it = directions.begin();
    auto choice = std::next(it,i);

    switch((*choice)){
     case SerieDirection::LEFT:
       posDir.position.x = x - mBlockPerSprite;
       posDir.position.y = y;
       if (mScreen.inLimits(posDir.position.x,posDir.position.y))
       {
         if (!mScreen.getPos(posDir.position.x,posDir.position.y))
         {
           posDir.direction = SerieDirection::LEFT;
           mStackDir.push(posDir);
           result++;
         }
       }
       break;
     case SerieDirection::RIGHT:
       posDir.position.x = x + mBlockPerSprite;
       posDir.position.y = y;
       if (!mScreen.getPos(posDir.position.x,posDir.position.y))
       {
         posDir.direction = SerieDirection::RIGHT;
         mStackDir.push(posDir);
         result++;
       }
       break;
     case SerieDirection::UP:
       posDir.position.x = x;
       posDir.position.y = y + mBlockPerSprite;
       if (!mScreen.getPos(posDir.position.x,posDir.position.y))
       {
         posDir.direction = SerieDirection::UP;
         mStackDir.push(posDir);
         result++;
       }
       break;
     case SerieDirection::DOWN:
       posDir.position.x = x;
       posDir.position.y = y - mBlockPerSprite;
       if (mScreen.inLimits(posDir.position.x,posDir.position.y))
       {
         if (!mScreen.getPos(posDir.position.x,posDir.position.y))
         {
           posDir.direction = SerieDirection::DOWN;
           mStackDir.push(posDir);
           result++;
         }
       }
       break;
    }

    directions.erase(choice);
  }

  return result;
}

// Position2D SerieFactory::getPositionAtDirection(size_t x, size_t y,
//                                                 SerieDirection direction)
// {
//   Position2D position{x,y};

//   switch(direction){
//    case SerieDirection::LEFT:
//      position.x = x - mBlockPerSprite;
//      position.y = y;
//     break;
//    case SerieDirection::RIGHT:
//      position.x = x + mBlockPerSprite;
//      position.y = y;
//      break;
//    case SerieDirection::UP:
//      position.x = x;
//      position.y = y + mBlockPerSprite;
//      break;
//    case SerieDirection::DOWN:
//      position.x = x;
//      position.y = y - mBlockPerSprite;
//      break;
//   }

//   return position;
// }

void SerieFactory::putSpriteHole(size_t x, size_t y, std::function<int(int)> fSerie)
{
  if (mHoleNow)
  {
    blockMapPosition(x,y); // TODO: Put in map walls in elem position.
  }
  else
  {
    putSprite(x, y, mFuncSerie); // put next serie sprite
  }

  mHoleNow = !mHoleNow;
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
  mListSerie.push_back(Sprite(mSpriteSide,x,y,value,mBlockSide));

  // Store value in screen map.
  // Be aware to not use 0 and 1 as part of the serie.
  mScreen.setValue(x,y,value);

  // std::cout << "Add sprite ("<<x<<","<<y<<")serie for current(" << mCurrent - 1 << ") = " << value << std::endl;
  // mScreen.dump();
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
      // // Debug.
      // std::cout << "x:" << x << " y:" << y << " (ix,iy) = (" << ix << "," << iy << ")" << std::endl;
      // mScreen.dump();
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

int SerieFactory::findElem(size_t x, size_t y, size_t offset)
{
  auto IsNear = [=](Sprite spr)
  {
    if ((std::abs((int)spr.getPos().x - (int)x) < offset) && (std::abs((int)spr.getPos().y - (int)y) < offset))
    {
      return true;
    }

    return false;
  };

  std::list<Sprite>::iterator it = std::find_if(mListSerie.begin(), mListSerie.end(), IsNear);

  if (it != mListSerie.end())
  {
    // std::cout << "The elment is:... " << std::distance(mListSerie.begin(),it)  << " ... near x " << x << " y " << y << '\n';
    return std::distance(mListSerie.begin(),it);
  }

  // std::cout << "The is no elment near x " << x << " y " << y << '\n';

  return -1;
}


size_t SerieFactory::getElem(size_t x, size_t y)
{
  return mScreen.getValue(x,y);
}

void SerieFactory::clearElem(size_t x, size_t y)
{
  mScreen.setValue(x,y,0);
}

size_t SerieFactory::getFrontValue()
{
  return mListSerie.front().getValue();
}

Sprite SerieFactory::pop()
{
  Sprite sprite = mListSerie.front();
  mListSerie.pop_front();
  return sprite;
}

Sprite SerieFactory::front()
{
  return mListSerie.front();
}
