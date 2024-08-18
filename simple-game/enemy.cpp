#include "enemy.h"

/// @brief Changes mBehavior field and sets
///        behavior function.
///
/// @param behavior Index of enemy behavior
void Enemy::setBehaviour(size_t behavior)
{
  mBehavior = behavior;

  std::function<void()> behaviour0 = [this]()
  {
    PathLimit pathLimit = mPathStack.top();

    // Sets sprite direction.
    setDirection(pathLimit.first);

    Position2D offsets = getOffsets();
    if (offsets.x == 0 && offsets.y == 0)
    { // Enter in a new map block
      if (Collision(pathLimit.first))
      {
        // TODO: Remove current dir if limit reached
        //       Mark new dir when no limit reached as -1,-1
        //       If limit reached do not calculate posible dirs
        //       just pop current dir. Check that current dir is in possible dirs.
        addNewDir(pathLimit);
        return;
      }
    }

    // Advance sprite
    advance();
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

  switch(mBehavior)
  {
   case 0:
     run = behaviour0;
     resetPathStack();
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

/// @brief Resets path stack according enemy behavior
///
void Enemy::resetPathStack()
{
  switch(mBehavior)
  {
   case 0:
     mPathStack.push(std::pair{SpriteDirection::UP,    Limit2D{NO_LIMIT,22}});
     mPathStack.push(std::pair{SpriteDirection::RIGHT, Limit2D{25,NO_LIMIT}});
     mPathStack.push(std::pair{SpriteDirection::DOWN,  Limit2D{NO_LIMIT, 1}});
     mPathStack.push(std::pair{SpriteDirection::LEFT,  Limit2D{1, NO_LIMIT}});
     break;
   case 1:
     break;
   case 2:
     break;
   case 3:
     break;
  }

}

/// @brief Inform if limit is reached according to path limit
///
/// @param  path Pair Sprite <direction, limit>
/// @return true if limit is reached or is NO_LIMIT
bool Enemy::LimitReached(PathLimit path)
{
  Position2D pos = getPos();

  SpriteDirection dir   = path.first;
  Limit2D         limit = path.second;

  bool reached = false;

  switch(dir)
  {
   case SpriteDirection::LEFT:
     if (limit.x == NO_LIMIT || pos.x <= limit.x)
     {
       reached = true;
     }
     break;

   case SpriteDirection::RIGHT:
     if (limit.x == NO_LIMIT || pos.x >= limit.x)
     {
       reached = true;
     }
     break;
   case SpriteDirection::UP:
     if (limit.y == NO_LIMIT || pos.y >= limit.y)
     {
       reached = true;
     }
     break;
   case SpriteDirection::DOWN:
     if (limit.y == NO_LIMIT || pos.y <= limit.y)
     {
       reached = true;
     }
     break;
  }

  return reached;
}

/// @brief How to behave when arrives to a wall
///
/// @param path Pair Sprite <direction, limit>
void Enemy::addNewDir(PathLimit path)
{
  std::stack<SpriteDirection> possibleDirs;

  if (LimitReached(path))
  {
    mPathStack.pop();
    if (mPathStack.empty())
    {
      resetPathStack();
    }
  }
  else
  {
    Position2D pos = getPos();

    possibleDirs = mScreen.possibleDirections(pos.x, pos.y);

    // Push in mPathstack next dir different from current.
    while (possibleDirs.size() > 0)
    {
      if (InverseDir(path.first) == possibleDirs.top())
      {
        possibleDirs.pop();
      }
      else
      {
        mPathStack.push(std::pair{possibleDirs.top(), Limit2D{NO_LIMIT, NO_LIMIT}});
        return;
      }
    }
  }
}
