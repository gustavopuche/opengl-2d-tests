#include "gameScore.h"

void GameScore::paint()
{
  ////////////////////////////////////////////////////////////
  // Panel line 1.
  for (auto& elem : mPanel[0])
  {
    elem.setTexture(5,0).paint().paintValue();
  }

  // Paint lives
  for (auto& elem : mLivesPanel)
  {
    elem.paint();
  }
  ////////////////////////////////////////////////////////////
  // Panel line 2.
  size_t numElems = mPanel[1].size();
  if (numElems > mColumns)
  {
    size_t xcoordOffset = 0;
    for (size_t i = (numElems - mColumns); i < numElems; i++)
    {
      size_t x = mBegin.x + xcoordOffset++;
      size_t y = mEnd.y;
      mPanel[1][i].setPos(x, y);
      mPanel[1][i].paint().paintValue();
    }
  }
  else
  {
    for (auto& elem : mPanel[1])
    {
      elem.paint().paintValue();
    }
  }
}

void GameScore::addLives(Sprite sprite, size_t lives)
{
  size_t x = LAST_POSITION;
  size_t y = mBegin.y;
  for (size_t i=0;i<lives;i++)
  {
    sprite.setPos(x,y);
    mLivesPanel.push_back(sprite);
    x--;
  }
}

void GameScore::add(Sprite sprite)
{
  size_t x = mBegin.x + mPanel[1].size();
  size_t y = mEnd.y;
  sprite.setPos(x,y);
  mPanel[1].push_back(sprite);
}

void GameScore::addNext(Sprite sprite)
{
  size_t x = mBegin.x;
  size_t y = mBegin.y;
  sprite.setPos(x,y);

  if (mPanel[0].size() == 0)
  {
    mPanel[0].push_back(sprite);
  }
  else
  {
    mPanel[0][0] = sprite;
  }
}
