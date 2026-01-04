#include "screens.h"
#include <GL/glut.h>

// Debug. remove later.
#include <iostream>
//////////////////////////////////////////////////////////////////////

void Screen::paint()
{
}

void Screen::setColor(float r, float g, float b)
{
  this->r = r;
  this->g = g;
  this->b = b;
}

// Todo calcualte this using an Interface.
void Screen::setTexture (int row,int column,int maxTextures)
{
  u0 = 0.0 + column * 1.0 / maxTextures;
  u1 = u0 + 1.0 / maxTextures;
  v0 = 0.0 + row * 1.0 / maxTextures;
  v1 = v0 + 1.0 / maxTextures;

  // Debug. Remove later.
  std::cout << "(" << u0 << "," << u1 << "," << v0 << "," << v1 << ")"<< std::endl;
  //////////////////////////////////////////////////////////////////////
}

bool Screen::getPos(size_t x, size_t y)
{
  Position2D pos = transformPos(x, y,mMapSide);

  return mMap[pos.y][pos.x] > 0 ? true : false;
}

std::stack<SpriteDirection> Screen::possibleDirections(size_t x, size_t y)
{
  std::stack<SpriteDirection> possibleDirs;

  size_t rx, ry;

  // Check LEFT.
  rx = x - mBlockPerSprite;
  ry = y;
  if (inLimits(rx,ry))
  {
    if (!getPos(rx,ry))
    {
      possibleDirs.push(SpriteDirection::LEFT);
    }
  }
  // Check UP.
  rx = x;
  ry = y + mBlockPerSprite;
  if (!getPos(rx,ry))
  {
    possibleDirs.push(SpriteDirection::UP);
  }
  // Check RIGHT.
  rx = x + mBlockPerSprite;
  ry = y;
  if (!getPos(rx,ry))
  {
    possibleDirs.push(SpriteDirection::RIGHT);
  }
  // Check DOWN.
  rx = x;
  ry = y - mBlockPerSprite;
  if (inLimits(rx,ry))
  {
    if (!getPos(rx,ry))
    {
      possibleDirs.push(SpriteDirection::DOWN);
    }
  }

  return possibleDirs;
}

bool Screen::isDirectionPossible(Position2D pos, SpriteDirection dir)
{
  bool possible = false;
  std::stack<SpriteDirection> possibleDirs = possibleDirections(pos.x, pos.y);

  while (possibleDirs.size() > 0)
  {
    if (possibleDirs.top() == dir)
    {
      possible = true;
    }

    possibleDirs.pop();
  }

  return possible;
}


void Screen::setWall(size_t x, size_t y)
{
  Position2D pos = transformPos(x, y,mMapSide);

  mMap[pos.y][pos.x] = 1;
}

bool Screen::inLimits(size_t x, size_t y)
{
  return (y < mMap.size()) && (x < mMap[0].size()) ? true : false;
}

size_t Screen::getValue(size_t x, size_t y)
{
  Position2D pos = transformPos(x, y,mMapSide);

  return mMap[pos.y][pos.x];
}
void Screen::setValue(size_t x, size_t y, size_t value)
{
  Position2D pos = transformPos(x, y,mMapSide);

  mMap[pos.y][pos.x] = value;
}
// Transform from OpenGL coords to vector<vector> coords.
// Position2D Screen::transformPos(size_t x, size_t y)
// {
//   return Position2D(x,mMapSide - 1 - y);
// }

void Screen::dump()
{
  ::dump(mMap);
}
