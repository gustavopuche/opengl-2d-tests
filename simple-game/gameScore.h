#include "screens.h"
#include "sprites.h"
#include <vector>
#include <list>
#include <functional>

class GameScore
{
 public:
  GameScore(Screen screen,
            Position2D begin,
            Position2D end,
            size_t blockside = 40,
            size_t spriteside = 40) :
    mBlockSide{blockside},
    mSpriteSide{spriteside},
    mScreen{screen},
    mBegin{begin},
    mEnd{end},
    mLives{INIT_LIVES},
    mScore{0}
  {
    mBlockPerSprite = mSpriteSide / mBlockSide;
    mRows           = mBegin.y - (mEnd.y - 1);
    mColumns        = mEnd.x + 1 - mBegin.x;

    std::cout << "GameScore rows = " << mRows << std::endl;

    for (auto i = 0; i < mRows; i++)
    {
      std::vector<Sprite> v{};
      mBubblesPanel.push_back(v);
    }

    // Score points.
    Sprite sprite = Sprite(mScreen);
    sprite.setTexture(1, 0).setColor(0.2, 1.0, 0.5);
    size_t x = SCORE_POSITION;
    size_t y = mBegin.y;

    for (auto i = 0; i < SCORE_DIGITS; i++)
    {
      sprite.setPos(x, y);
      mScorePanel.push_back(sprite);
      x++;
    }
  }

  GameScore& paint();
  GameScore& add(Sprite sprite);
  GameScore& setLives(size_t lives = INIT_LIVES);
  GameScore& addNext(Sprite sprite);
  GameScore& addPoints(size_t points);
  size_t getScore(){return mScore;}
  size_t getLives(){return mLives;}
 private:
  void overflow();
  std::vector<std::vector<Sprite>> mBubblesPanel;
  std::vector<Sprite>              mLivesPanel;
  std::vector<Sprite>              mScorePanel;
  Position2D                       mBegin;
  Position2D                       mEnd;
  Screen                           mScreen;
  size_t                           mLives;
  size_t                           mRows;
  size_t                           mColumns;
  size_t                           mSpriteSide;
  size_t                           mBlockSide;
  size_t                           mBlockPerSprite;
  size_t                           mScore;

  constexpr static size_t LAST_POSITION = 25;
  constexpr static size_t INIT_LIVES = 2;
  constexpr static size_t SCORE_DIGITS = 7;
  constexpr static size_t SCORE_POSITION = 10;
  constexpr static size_t SCORE_DIVISOR = 1000000;
};
