#include "screens.h"
#include "sprites.h"
#include <vector>
#include <list>
#include <functional>

class SerieFactory
{
 public:
  SerieFactory(std::vector<std::vector<size_t>> map,
               std::function<int(int)> fSerie,
               size_t x = 0,
               size_t y = 0,
               size_t blockside = 40,
               size_t spriteside = 40) :
    mScreen{map},
    mBlockSide{blockside},
    mSpriteSide{spriteside},
    mSx{x},
    mSy{y},
    mFuncSerie{fSerie},
    mHoleNow{false}
  {
    mR = 1.0;
    mG = 1.0;
    mB = 1.0;

    mCurrent = 1;

    mBlockPerSprite = mSpriteSide / mBlockSide;
    generate();
  }
  // Returns index in Sprite vector (aka mVectorSerie)
  // Returns -1 if no element in found in position +/- offset

  enum class SerieDirection {LEFT,RIGHT,UP,DOWN};

  void paint();

  size_t getElem(size_t x, size_t y);
  void clearElem(size_t x, size_t y);
  int findElem(size_t x, size_t y, size_t offset);

  size_t getFrontValue();
  Sprite pop();
  Sprite front();

 private:
  std::list<Sprite>       mListSerie;
  Screen                  mScreen;
  std::list<Position2D>   mVisit;
  size_t                  mSpriteSide;
  size_t                  mBlockSide;
  size_t                  mBlockPerSprite;
  size_t                  mSx,mSy;  // Sprite  initial position.
  float                   mR,mG,mB;
  int                     mCurrent; // Current x       value to calculate fSerie(x)
  std::function<int(int)> mFuncSerie;
  bool                    mHoleNow;

  void generateFluentHoles();
  void addFluentHoles(size_t x, size_t y);
  bool followFluentHoles(size_t x, size_t y, SerieDirection direction);
  std::vector<SerieDirection> possibleDirections(size_t x, size_t y);
  Position2D getPositionAtDirection(size_t x, size_t y, SerieDirection direction);

  void generate();
  void addNeighborgs(size_t x, size_t y);
  void addElem(size_t x, size_t y);
  void emptyVisit();

  void blockMapPosition(size_t x,size_t y);
  void putSprite(size_t x, size_t y, std::function<int(int)> fSerie);
  void putSpriteHole(size_t x, size_t y, std::function<int(int)> fSerie);
};
