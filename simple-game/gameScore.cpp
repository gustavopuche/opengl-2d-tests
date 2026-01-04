#include "gameScore.h"

GameScore& GameScore::paint()
{
  ////////////////////////////////////////////////////////////
  // Panel line 1.
  for (auto& elem : mBubblesPanel[0])
  {
    elem.setTexture(5,0).paint().paintValue();
  }

  // Paint score.
  for (auto& elem : mScorePanel)
  {
    elem.paint();
  }

  // Paint lives.
  for (auto& elem : mLivesPanel)
  {
    elem.paint();
  }
  ////////////////////////////////////////////////////////////
  // Panel line 2.
  size_t numElems = mBubblesPanel[1].size();
  if (numElems > mColumns)
  {
    size_t xcoordOffset = 0;
    for (size_t i = (numElems - mColumns); i < numElems; i++)
    {
      size_t x = mBegin.x + xcoordOffset++;
      size_t y = mEnd.y;
      mBubblesPanel[1][i].setPos(x, y);
      mBubblesPanel[1][i].paint().paintValue();
    }
  }
  else
  {
    for (auto& elem : mBubblesPanel[1])
    {
      elem.paint().paintValue();
    }
  }

  return *this;
}

GameScore& GameScore::setLives(size_t lives)
{
  // Reset.
  mLivesPanel.clear();

  Sprite sprite = Sprite(mScreen);
  sprite.setTexture(0, 0).setColor(1.0,1.0,0.0);

  size_t x = LAST_POSITION;
  size_t y = mBegin.y;
  for (size_t i=0;i<lives;i++)
  {
    sprite.setPos(x,y);
    mLivesPanel.push_back(sprite);
    x--;
  }

  return *this;
}

GameScore& GameScore::add(Sprite sprite)
{
  size_t x = mBegin.x + mBubblesPanel[1].size();
  size_t y = mEnd.y;
  sprite.setPos(x,y);
  mBubblesPanel[1].push_back(sprite);

  return *this;
}

GameScore& GameScore::addNext(Sprite sprite)
{
  size_t x = mBegin.x;
  size_t y = mBegin.y;
  sprite.setPos(x,y);

  if (mBubblesPanel[0].size() == 0)
  {
    mBubblesPanel[0].push_back(sprite);
  }
  else
  {
    mBubblesPanel[0][0] = sprite;
  }

  return *this;
}

GameScore& GameScore::addPoints(size_t points)
{
  mScore += points;
  size_t partialScore = mScore;
  size_t digitMultiple = SCORE_DIVISOR;
  size_t digitPos = 0;
  while (digitMultiple > 1)
  {
    size_t textureNumber = partialScore / digitMultiple;
    partialScore -= textureNumber * digitMultiple;
    mScorePanel[digitPos++].setTexture(1,textureNumber);
    digitMultiple /= 10;
  }

  return *this;
}
