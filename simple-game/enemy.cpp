#include "enemy.h"

void Enemy::setBehaviour(size_t behavior)
{
  std::function<void()> behaviour0 = [this]()
  {
    SpriteDirection pathDir = mPathStack.top();

    // Sets sprite direction.
    setDirection(pathDir);

    Position2D offsets = getOffsets();
    if (offsets.x == 0 && offsets.y == 0)
    { // Enter in a new map block
      if (Collision(pathDir))
      {
        addNewDir(pathDir);
        return;
      }
    }

    // Advance sprite
    advance();

    // size_t screenX, screenY;
    // getPixelPos(screenX, screenY);
    // if ( screenX > 200)
    // {
    //   setPixelPos(screenX - 1, screenY);

    //   // Debug. Remove later.
    //   Position2D pos = getPos();
    //   std::cout << "Enemy sceen x = " << screenX
    //             << " pos.x = " << pos.x << std::endl;
    // }
  };

  std::function<void()> behaviour1 = [this]()
  {

  };

  std::function<void()> behaviour2 = [this]()
  {

  };

  std::function<void()> behaviour3 = [this]()
  {

  };

  switch(behavior)
  {
   case 0:
     run = behaviour0;
     mPathStack.push(SpriteDirection::UP);
     mPathStack.push(SpriteDirection::RIGHT);
     mPathStack.push(SpriteDirection::DOWN);
     mPathStack.push(SpriteDirection::LEFT);
     break;
   case 1:
     run = behaviour1;
     break;
   case 2:
     run = behaviour2;
     break;
   case 3:
     run = behaviour3;
     break;
  }
}

void Enemy::addNewDir(SpriteDirection dir)
{
  std::stack<SpriteDirection> possibleDirs;

  // If offsets are 0 means we are in a new block.
  // If we are in a new block then.
  //    Check possible directions
  //    If new directions random choose one
  //
  Position2D pos = getPos();

  possibleDirs = mScreen.possibleDirections(pos.x, pos.y);

  // Push in mPathstack next dir different from current.
  while (possibleDirs.size() > 0)
  {
    if (dir == possibleDirs.top())
    {
      possibleDirs.pop();
    }
    else
    {
      mPathStack.push(possibleDirs.top());
      return;
    }
  }
}
