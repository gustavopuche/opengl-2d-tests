#include "screens.h"
#include "sprites.h"
#include <vector>
#include <list>
#include <functional>

class GameScore
{
 public:
  GameScore(Position2D begin,
            Position2D end,
            size_t blockside = 40,
            size_t spriteside = 40) :
    mBlockSide{blockside},
    mSpriteSide{spriteside},
    mBegin{begin},
    mEnd{end},
    mLives{INIT_LIVES}
  {
    mBlockPerSprite = mSpriteSide / mBlockSide;
    mRows           = mBegin.y - (mEnd.y - 1);
    mColumns        = mEnd.x + 1 - mBegin.x;

    std::cout << "GameScore rows = " << mRows << std::endl;

    for (auto i = 0; i < mRows; i++)
    {
      std::vector<Sprite> v{};
      mPanel.push_back(v);
    }
  }

  void paint();
  void add(Sprite sprite);
  void addLives(Sprite sprite, size_t lives = INIT_LIVES);
  void addNext(Sprite sprite);
 private:
  void overflow();
  std::vector<std::vector<Sprite>> mPanel;
  std::vector<Sprite>              mLivesPanel;
  Position2D                       mBegin;
  Position2D                       mEnd;
  size_t                           mLives;
  size_t                           mRows;
  size_t                           mColumns;
  size_t                           mSpriteSide;
  size_t                           mBlockSide;
  size_t                           mBlockPerSprite;

  constexpr static size_t LAST_POSITION = 25;
  constexpr static size_t INIT_LIVES = 2;
};
