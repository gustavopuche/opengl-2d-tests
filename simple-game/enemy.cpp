#include "enemy.h"

/// @brief Changes mBehavior field and sets
///        behavior function.
///
/// @param behavior Index of enemy behavior
void Enemy::setBehaviour(size_t behavior)
{
  mBehavior = behavior;

  std::cout << __FUNCTION__ <<":"<< __LINE__ << std::endl;

  std::function<void()> behaviour0 = [this]()
  {
    PathLimit pathLimit = mPathStack.top();

    SpriteDirection dir = pathLimit.first;

    Position2D offsets = getOffsets();
    if (offsets.x == 0 && offsets.y == 0)
    { // Enter in a new map block
      if (mHeroVisible)
      {
        Position2D pos = getPos();
        if (mScreen.isDirectionPossible(pos,mChaseDirection))
        {
          mPathStack.push(std::pair{mChaseDirection, Limit2D{NO_LIMIT, NO_LIMIT}});
          dir = mChaseDirection;
          std::cout << mName << " dir = mChaseDirection: " << ToString(mChaseDirection)
                    << " x: " << pos.x << " y: " << pos.y << std::endl;
        }
      }
      else if (Collision(dir))
      {
        // TODO: Remove current dir if limit reached
        //       Mark new dir when no limit reached as -1,-1
        //       If limit reached do not calculate posible dirs
        //       just pop current dir. Check that current dir is in possible dirs.
        // BUGGY addNewDir is not good. MODIFY it.
        std::cout << mName << " Enemy collision dir: " << ToString(dir) << std::endl;
        addNewDir(pathLimit);
        return;
      }
    }

    // Advance sprite
    advance(dir);
  };

  std::function<void()> behaviour1 = [this]()
  {
    PathLimit pathLimit = mPathStack.top();

    SpriteDirection dir = pathLimit.first;

    Position2D offsets = getOffsets();
    if (offsets.x == 0 && offsets.y == 0)
    { // Enter in a new map block
      if (mHeroVisible)
      {
        Position2D pos = getPos();
        if (mScreen.isDirectionPossible(pos,mChaseDirection))
        {
          mPathStack.push(std::pair{mChaseDirection, Limit2D{NO_LIMIT, NO_LIMIT}});
          dir = mChaseDirection;
        }
      }

      if (Collision(dir))
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
    advance(dir);
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
     std::cout << __FUNCTION__ <<":"<< __LINE__ << " RESET !!!" << std::endl;
     resetPathStack();
     run = behaviour0;
     break;
   case 1:
     resetPathStack();
     run = behaviour1;
     break;
   case 2:
     resetPathStack();
     run = behaviour2;
     break;
   case 3:
     resetPathStack();
     run = behaviour3;
     break;
  }
}

/// @brief Resets path stack according enemy behavior
///
void Enemy::resetPathStack()
{
  // Clear stack
  while(!mPathStack.empty())
  {
    mPathStack.pop();
  }

  switch(mBehavior)
  {
   case 0:
     std::cout << __FUNCTION__ <<":"<< __LINE__ << " RESET path!!!" << std::endl;
     mPathStack.push(std::pair{SpriteDirection::UP,    Limit2D{NO_LIMIT,22}});
     mPathStack.push(std::pair{SpriteDirection::RIGHT, Limit2D{25,NO_LIMIT}});
     mPathStack.push(std::pair{SpriteDirection::DOWN,  Limit2D{NO_LIMIT, 1}});
     mPathStack.push(std::pair{SpriteDirection::LEFT,  Limit2D{1, NO_LIMIT}});
     break;
   case 1:
     mPathStack.push(std::pair{SpriteDirection::LEFT,  Limit2D{1, NO_LIMIT}});
     mPathStack.push(std::pair{SpriteDirection::DOWN,  Limit2D{NO_LIMIT, 1}});
     mPathStack.push(std::pair{SpriteDirection::RIGHT, Limit2D{25,NO_LIMIT}});
     mPathStack.push(std::pair{SpriteDirection::UP,    Limit2D{NO_LIMIT,22}});
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

  Position2D pos = getPos();

  if (LimitReached(path))
  {
    mPathStack.pop();

    if (mPathStack.empty())
    {
      std::cout << mName << " RESET mPathStack!!!" << std::endl;
      resetPathStack();
    }
  }
  else
  {
    possibleDirs = mScreen.possibleDirections(pos.x, pos.y);

    // Push in mPathstack next dir different from current.
    while (possibleDirs.size() > 0)
    {
      if (InverseDir(path.first) == possibleDirs.top())
      {
        std::cout << mName << " pop dir: " << ToString(path.first) << std::endl;
        possibleDirs.pop();
      }
      else
      {
        std::cout << mName << " add dir: " << ToString(possibleDirs.top()) << std::endl;
        mPathStack.push(std::pair{possibleDirs.top(), Limit2D{NO_LIMIT, NO_LIMIT}});
        return;
      }
    }
  }
}

Enemy &Enemy::setHeroData(Sprite hero)
{
  mHeroVisible = isHeroVisible(hero.getPos());
  mHeroPos = hero.getPos();
  mHeroDirection = hero.getDirection();
  return *this;
}

bool Enemy::isHeroVisible(Position2D heroPos)
{
  bool visible = false;
  Position2D pos = getPos();

  std::optional<SpriteDirection> dir = mScreen.positionVisibleDirection(pos,heroPos);
  if (dir)
  {
    visible = true;
    mChaseDirection = dir.value();
  }

  return visible;
}