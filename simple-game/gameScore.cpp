#include "gameScore.h"

void GameScore::paint()
{
  for (auto& list : mPanel)
  {
    size_t numElems = list.size();
    if (numElems > mColumns)
    {
      size_t xcoordOffset = 0;
      for (size_t i = (numElems - mColumns); i < numElems; i++)
      {
        size_t x = mBegin.x + xcoordOffset++;
        size_t y = mEnd.y;
        list[i].setPos(x, y);
        list[i].paint().paintValue();
      }
    }
    else
    {
      for (auto& elem : list)
      {
        elem.paint().paintValue();
      }
    }
  }
}

void GameScore::add(Sprite sprite)
{
  size_t x = mBegin.x + mPanel[1].size();
  size_t y = mEnd.y;
  sprite.setPos(x,y);
  mPanel[1].push_back(sprite);
}
