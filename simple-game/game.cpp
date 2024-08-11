#include "lodepng.h"
#include "seriefactory.h"
#include "gameScore.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <memory>
#include <time.h>
#include <set>
#include "enemy.h"

////////////////////////////////////////////////////////////////////////////////
/// Forward declarations
////////////////////////////////////////////////////////////////////////////////
bool wallCollision(size_t x, size_t y, SpriteMove moving,SpriteDirection direction);
void setNextDirection(std::stack<SpriteDirection> &possibleDirs, SpriteDirection &spriteDir);

// Global variables to move the object.

size_t initialTime = time(NULL);
size_t finalTime;
size_t frameCount = 0;

float xr = 40, yr = 40;
float sprSpeed = 2;
size_t heroAnimation = 0;
size_t sprBlckX, sprBlckY, sprOffX, sprOffY;
size_t enemy1X = 400, enemy1Y = 400;
SpriteDirection enemy1Dir = SpriteDirection::LEFT;

SpriteDirection currSprtDir = SpriteDirection::LEFT;
SpriteDirection nextDir = currSprtDir;
std::unique_ptr<SerieFactory> upAllBubbles;
std::unique_ptr<GameScore> scorePanel;
std::unique_ptr<Sprite> hero;
std::unique_ptr<Sprite> enemy1;
std::unique_ptr<Enemy> enemy0;
const size_t TEXCOL = 2;
const size_t MAP_SIDE = 27;
const size_t BLOCK_SIDE = 40;
const size_t SPRITE_SIDE = 40;
const size_t BLOCKS_PER_SPRITE = SPRITE_SIDE / BLOCK_SIDE;
const size_t TEXTURES_PER_LINE = 20;
const size_t HERO_MAX_ANIMATION = 6;

const size_t FPS = 60;

std::vector<std::vector<size_t>> gameMap = {{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,0,1,1,1,0,1,1,0,1,0,1,1,0,1,1,1,0,1,1,1,0,1},
    {1,0,1,1,1,0,1,1,1,0,1,1,0,1,0,1,1,0,1,1,1,0,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,0,1,0,1,1,0,1,1,1,1,1,0,1,1,0,1,0,1,1,1,0,1},
    {1,0,1,1,1,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1,1,1,0,1},
    {1,0,0,0,0,0,1,1,1,0,1,1,0,1,0,1,1,0,1,1,1,0,0,0,0,0,1},
    {1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1},
    {0,0,0,0,1,0,1,0,1,1,1,1,0,1,0,1,1,1,1,0,1,0,1,0,0,0,0},
    {1,1,1,1,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1},
    {0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0},
    {1,1,1,1,1,0,1,0,1,1,0,1,1,1,1,1,0,1,1,0,1,0,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,0,1,1,1,0,1},
    {1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1},
    {1,1,1,0,1,0,1,0,1,1,0,1,1,1,1,1,0,1,1,0,1,0,1,0,1,1,1},
    {1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1},
    {1,0,1,1,1,1,1,1,1,0,1,1,0,1,0,1,1,0,1,1,1,1,1,1,1,0,1},
    {1,0,1,1,1,1,1,1,1,0,1,1,0,1,0,1,1,0,1,1,1,1,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
  }};

////////////////////////////////////////////////////////////////////////////////
/// Screen object.
Screen mScreen{gameMap};

std::vector<unsigned char> img;
unsigned w, h;
GLuint texture[0];
auto serieFunct = [](int x)
{
  int rest = 100 % 6;
  int max = 100 / 6;
  if (rest == 0)
  {
    max--;
  }

  int result;

  // To diff next series.
  int rounds = x / max;

  if ((x % max) == 0)
  {
    result = max * 6;
  }
  else
  {
    result = (x % max) * 6;
  }

  result += rounds * 100;
  return result;
};
int serieCurrent = serieFunct(1);

void calculateSpritePos()
{
  sprBlckX = (size_t)xr / BLOCK_SIDE;
  sprBlckY = (size_t)yr / BLOCK_SIDE;
  sprOffX  = (size_t)xr % BLOCK_SIDE;
  sprOffY  = (size_t)yr % BLOCK_SIDE;
}

void decodeOneStep(const char* filename)
{
  std::vector<unsigned char> image;
  unsigned width, height;

  glBindTexture(GL_TEXTURE_2D, texture[0]);
  //decode
  unsigned error = lodepng::decode(image, width, height, filename);
  std::cout << "w: " << width << " " << "h: " << height << std::endl;

  //if there's an error, display it
  if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
  else
  {
	  img = image;
    w = width;
    h = height;
    std::cout << "Success" << std::endl;
  }

  // glGenTextures(1,&texture[0]);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, &img[0]);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  // glEnable(GL_TEXTURE_2D);
  glShadeModel(GL_FLAT);
}

void paintBlock(void)
{
  glBegin(GL_QUADS);
  glColor3f(1.0 ,0.5 ,0.0);
  glVertex2f(0,0);
  glVertex2f(BLOCK_SIDE,0);
  glVertex2f(BLOCK_SIDE,BLOCK_SIDE);
  glVertex2f(0,BLOCK_SIDE);
  glEnd();
}

// Paint borders
void paintMap(void)
{
  for (size_t y=0; y < MAP_SIDE; y++)
    for (size_t x=0; x < MAP_SIDE; x++)
    {
      if (gameMap[MAP_SIDE - 1 - y][x] == 1)
      {
        glPushMatrix();
        glTranslatef(BLOCK_SIDE * x,BLOCK_SIDE * y, 0);
        paintBlock();
        glPopMatrix();
      }
    }
}

bool getWallAt(size_t x, size_t y)
{
  if(gameMap[MAP_SIDE - 1 - y][x] == 1)
  {
    return true;
  }
  else
  {
    return false;
  }
}

std::string printDir(SpriteDirection dir)
{
  switch(dir)
  {
   case SpriteDirection::LEFT:
     return std::string("Left <-");
   case SpriteDirection::UP:
     return std::string("Up ^");
   case SpriteDirection::RIGHT:
     return std::string("Right ->");
   case SpriteDirection::DOWN:
     return std::string("Down \\/");
  }

  return "None";
}

/// Move Enemy
///
///
void moveEnemy()
{
  size_t enemy1BlckX = (size_t)enemy1X / BLOCK_SIDE;
  size_t enemy1BlckY = (size_t)enemy1Y / BLOCK_SIDE;
  size_t enemy1OffX  = (size_t)enemy1X % BLOCK_SIDE;
  size_t enemy1OffY  = (size_t)enemy1Y % BLOCK_SIDE;

  std::stack<SpriteDirection> possibleDirs;

  // If offsets are 0 means we are in a new block.
  // If we are in a new block then.
  //    Check possible directions
  //    If new directions random choose one
  //
  if (enemy1OffX == 0 && enemy1OffY == 0)
  {
    possibleDirs = mScreen.possibleDirections(enemy1BlckX, enemy1BlckY);
    setNextDirection(possibleDirs, enemy1Dir);
  }

  // Debug. Remove later
  // std::cout << "Enemy direction: " << printDir(enemy1Dir) << std::endl;
  //////////////////////////////////////////////////////////////////////

  enemy1->setDirection(enemy1Dir).
    advance().
    getPixelPos(enemy1X, enemy1Y).
    setFame(frameCount).
    paintAnimationFrame();

  enemy0->moveEnemy().setDirection(currSprtDir).setFame(frameCount).paintAnimationFrame();
}

/// Choose next sprite direction when in a crossroad.
///
/// @param posibleDirs Stack with posible directions to choose
/// @param spriteDir   Current sprite direction
void setNextDirection(std::stack<SpriteDirection> &possibleDirs, SpriteDirection &spriteDir)
{
  std::vector<SpriteDirection> tangentDirs;
  SpriteDirection reverse;
  bool thereIsReverse = false;
  bool blocked = true; // Indicates that the road is blocked.
  std::set<SpriteDirection> horizontal = {SpriteDirection::LEFT,SpriteDirection::RIGHT};
  std::set<SpriteDirection> vertical = {SpriteDirection::UP, SpriteDirection::DOWN};

  std::set<SpriteDirection> tangent, same;

  // Current dir is horizontal.
  if (horizontal.count(spriteDir) > 0)
  {
    tangent = vertical;
    same = horizontal;
  }
  else
  {
    tangent = horizontal;
    same = vertical;
  }

  while (possibleDirs.size() > 0)
  {
    if (tangent.count(possibleDirs.top()) > 0)
    {
      tangentDirs.push_back(possibleDirs.top());
    }
    else
    {
      if (spriteDir == possibleDirs.top())
      {
        blocked = false;
      }
      else
      {
        thereIsReverse = true;
        reverse = possibleDirs.top();
      }
    }
    possibleDirs.pop();
  }

  // Choose tangent dir if exists.
  if (tangentDirs.size() > 0)
  {
    size_t i = (size_t) rand() % tangent.size();
    spriteDir = tangentDirs[i];
  }
  // If blocked then reverse
  else if (blocked)
  {
    spriteDir = reverse;
  }
  // Otherwise continue in current direction.

}

// Paint hero sprite
void paintHero()
{
  // float u0,u1,v0,v1;
  // size_t column = 0;
  // size_t row = 0;
  // size_t maxTextures = TEXTURES_PER_LINE;
  // u0 = 0.0 + column * 1.0 / maxTextures;
  // u1 = u0 + 1.0 / maxTextures;
  // v0 = 0.0 + row * 1.0 / maxTextures;
  // v1 = v0 + 1.0 / maxTextures;

  // glEnable(GL_TEXTURE_2D);
  // glBegin(GL_QUADS);
  // glColor4f(1.0f, 1.0f, 0.0f, 1.0f);

  // switch(currSprtDir){
  // case SpriteDirection::LEFT:
  //   glTexCoord2f(u1, v1); glVertex2f(0+xr,0+yr);
  //   glTexCoord2f(u0, v1); glVertex2f(SPRITE_SIDE+xr,0+yr);
  //   glTexCoord2f(u0, v0); glVertex2f(SPRITE_SIDE+xr,SPRITE_SIDE+yr);
  //   glTexCoord2f(u1, v0); glVertex2f(0+xr,SPRITE_SIDE+yr);
  //   break;
  // case SpriteDirection::RIGHT:
  //   glTexCoord2f(u0, v1); glVertex2f(0+xr,0+yr);
  //   glTexCoord2f(u1, v1); glVertex2f(SPRITE_SIDE+xr,0+yr);
  //   glTexCoord2f(u1, v0); glVertex2f(SPRITE_SIDE+xr,SPRITE_SIDE+yr);
  //   glTexCoord2f(u0, v0); glVertex2f(0+xr,SPRITE_SIDE+yr);
  //   break;
  // case SpriteDirection::UP:
  //   glTexCoord2f(u0, v0); glVertex2f(0+xr,0+yr);
  //   glTexCoord2f(u0, v1); glVertex2f(SPRITE_SIDE+xr,0+yr);
  //   glTexCoord2f(u1, v1); glVertex2f(SPRITE_SIDE+xr,SPRITE_SIDE+yr);
  //   glTexCoord2f(u1, v0); glVertex2f(0+xr,SPRITE_SIDE+yr);
  //   break;
  // case SpriteDirection::DOWN:
  //   glTexCoord2f(u1, v0); glVertex2f(0+xr,0+yr);
  //   glTexCoord2f(u1, v1); glVertex2f(SPRITE_SIDE+xr,0+yr);
  //   glTexCoord2f(u0, v1); glVertex2f(SPRITE_SIDE+xr,SPRITE_SIDE+yr);
  //   glTexCoord2f(u0, v0); glVertex2f(0+xr,SPRITE_SIDE+yr);
  //   break;
  // }
  // glEnd();
  // glDisable(GL_TEXTURE_2D);

  hero->setPixelPos(xr, yr).setDirection(currSprtDir).setFame(frameCount).paintAnimationFrame();
}

void createHero()
{
  hero = std::make_unique<Sprite>(mScreen);
  hero->setTexture(0, 0).setFPS(FPS).setColor(1.0,1.0,0.0);
  hero->setMaxAnimation(6);
}

void createEnemy()
{
  enemy1 = std::make_unique<Sprite>(mScreen);
  enemy1->setTexture(7, 0).setFPS(FPS);
  enemy1->setPixelPos(enemy1X, enemy1Y);

  enemy0 = std::make_unique<Enemy>(mScreen);
  enemy0->setTexture(7, 0).setFPS(FPS);
  enemy0->setPixelPos(1000, 880);
  enemy0->setBehaviour(0);
}

void createScorePanel()
{
  scorePanel = std::make_unique<GameScore>(Position2D(1,25),Position2D(25,24));
}

void createBubbles()
{
  calculateSpritePos();
  upAllBubbles = std::make_unique<SerieFactory>(gameMap,serieFunct,sprBlckX,sprBlckY);
}

void printSpritePos()
{
  std::cout << "(" << xr << "," << yr << ") " ;
  std::cout << "Block:[" << (size_t)xr / BLOCK_SIDE << " " << (size_t)yr / BLOCK_SIDE << "] ";
  std::cout << "Offset:< "<< (size_t)xr % BLOCK_SIDE << " " << (size_t)yr % BLOCK_SIDE << "> " << std::endl;
}

bool heroCollision(size_t x, size_t y, SpriteMove moving,SpriteDirection direction)
{
  size_t bx, by;

  bx = x;
  by = y;

  switch(direction)
  {
   case SpriteDirection::LEFT:
     bx = x + 1;
     break;
   case SpriteDirection::DOWN:
     by = y + 1;
     break;
  }

  size_t mapValue = upAllBubbles->getElem(bx,by);
  if (mapValue > 1)
  {
    if (mapValue == upAllBubbles->getFrontValue())
    {
      scorePanel->add(upAllBubbles->pop());
      scorePanel->addNext(upAllBubbles->front());
      upAllBubbles->clearElem(bx,by);
    }
    // else
    // {
    //   if (moving == SpriteMove::HORIZONTAL)
    //   {
    //     if(sprOffX == 0)
    //     {
    //       std::cout << "Detected bubble horizontal colision at (" << x << "," << y << ") with value = " << mapValue << std::endl;
    //       std::cout << "Expected bubble value =" << upAllBubbles->getFrontValue() << std::endl;
    //       return true;
    //     }
    //   }
    //   else
    //   {// Vertical.
    //     if(sprOffY == 0)
    //     {
    //       std::cout << "Detected bubble vertical colision at (" << x << "," << y << ") with value = " << mapValue << std::endl;
    //       std::cout << "Expected bubble value =" << upAllBubbles->getFrontValue() << std::endl;
    //       return true;
    //     }
    //   }
    // }
  }

  return  wallCollision(x, y, moving, direction);
}

bool wallCollision(size_t x, size_t y, SpriteMove moving,SpriteDirection direction)
{
  size_t numChecks = BLOCKS_PER_SPRITE;
  if (moving == SpriteMove::HORIZONTAL)
  {
    if(sprOffX == 0)
    {
      if(sprOffY != 0)
      {
        numChecks++;
      }

      for(size_t i = 0; i < numChecks; i++)
      {
        if(getWallAt(x,y + i))
        {
          return true;
        }
      }
    }
  }
  else
  {// Vertical.
    if(sprOffY == 0)
    {
      if(sprOffX != 0)
      {
        numChecks++;
      }

      for(size_t i = 0; i < numChecks; i++)
      {
        if(getWallAt(x + i,y))
        {
          return true;
        }
      }
    }
  }

  return false;
}

bool canMoveSpriteTo(SpriteDirection direction)
{
  calculateSpritePos();

  switch(direction){
   case SpriteDirection::LEFT:
     if(heroCollision(sprBlckX - 1,sprBlckY,SpriteMove::HORIZONTAL,direction))
     {
       return false;
     }
     break;
   case SpriteDirection::RIGHT:
     if(heroCollision(sprBlckX + BLOCKS_PER_SPRITE,sprBlckY,SpriteMove::HORIZONTAL,direction))
     {
       return false;
     }
     break;
   case SpriteDirection::UP:
     if(heroCollision(sprBlckX,sprBlckY + BLOCKS_PER_SPRITE,SpriteMove::VERTICAL,direction))
     {
       return false;
     }
     break;
   case SpriteDirection::DOWN:
     if(heroCollision(sprBlckX,sprBlckY - 1,SpriteMove::VERTICAL,direction))
     {
       return false;
     }
     break;
  }

  return true;
}

bool moveSpriteTo(SpriteDirection direction)
{
  bool result = false;

  switch(direction){
   case SpriteDirection::LEFT:
     if(canMoveSpriteTo(SpriteDirection::LEFT))
     {
       xr -= sprSpeed;
       result = true;
     }
     break;
   case SpriteDirection::RIGHT:
     if(canMoveSpriteTo(SpriteDirection::RIGHT))
     {
       xr += sprSpeed;
       result = true;
     }
     break;
   case SpriteDirection::UP:
     if(canMoveSpriteTo(SpriteDirection::UP))
     {
       yr += sprSpeed;
       result = true;
     }
     break;
   case SpriteDirection::DOWN:
     if(canMoveSpriteTo(SpriteDirection::DOWN))
     {
       yr -= sprSpeed;
       result = true;
     }
     break;
  }

  return result;
}

void collision()
{
  // std::cout << "Wall collision!!!" << std::endl;
}

void specialKey(int key, int x, int y)
{
  switch(key){
   case GLUT_KEY_UP: // when the up key is pressed.
     if(canMoveSpriteTo(SpriteDirection::UP))
     {
       currSprtDir = SpriteDirection::UP;
       nextDir = currSprtDir;
     }
     else
     {
       nextDir = SpriteDirection::UP;
     }
     // printSpritePos();
     // glutPostRedisplay();
     break;
   case GLUT_KEY_DOWN: // when the down key is pressed.
     if(canMoveSpriteTo(SpriteDirection::DOWN))
     {
       currSprtDir = SpriteDirection::DOWN;
       nextDir = currSprtDir;
     }
     else
     {
       nextDir = SpriteDirection::DOWN;
     }
     // printSpritePos();
     // glutPostRedisplay();
     break;
   case GLUT_KEY_LEFT: // when the left key is pressed.
     if(canMoveSpriteTo(SpriteDirection::LEFT))
     {
       currSprtDir = SpriteDirection::LEFT;
       nextDir = currSprtDir;
     }
     else
     {
       nextDir = SpriteDirection::LEFT;
     }
     // printSpritePos();
     // glutPostRedisplay();
     break;
   case GLUT_KEY_RIGHT: // when the right key is pressed.
     if(canMoveSpriteTo(SpriteDirection::RIGHT))
     {
       currSprtDir = SpriteDirection::RIGHT;
       nextDir = currSprtDir;
     }
     else
     {
       nextDir = SpriteDirection::RIGHT;
     }
     // printSpritePos();
     break;
  }
}

// To navigate with only one touch.
void checkNextDirection()
{
  if(canMoveSpriteTo(nextDir))
  {
    currSprtDir = nextDir;
  }
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  // glMatrixMode(GL_MODELVIEW);      // To operate on Model-View matrix
  // glLoadIdentity();                // Reset the model-view matrix

  paintMap();

  // Paint score
  scorePanel->paint();

  // Paint bubbles generated by the SerieFactory.
  upAllBubbles->paint();

  // Allow ease change direction
  checkNextDirection();

  moveSpriteTo(currSprtDir);
  paintHero();
  moveEnemy();

  glFlush();
  glutSwapBuffers();

  frameCount++;
  finalTime = time(NULL);
  if (finalTime - initialTime > 0)
  {
    // std::cout << "FPS: " << frameCount << std::endl;
    frameCount = 0;
    initialTime = finalTime;
  }
}

void timer_callback(int)
{
  glutPostRedisplay();
  glutTimerFunc(1000 / FPS, timer_callback, 0);
}

int main(int argc, char** argv)
{
  std::cout << "Use arrow keys..." << std::endl;

  dump(gameMap);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(1080,1080);
  glutInitWindowPosition(50, 50);
  glutCreateWindow("sIMPle gAMe!");

  // Create hero caracter
  createHero();

  // Create enemy caracter
  createEnemy();

  // Create score panel. Only logic behaviour.
  createScorePanel();

  // Create bubbles sprites.
  createBubbles();

  decodeOneStep("pacmat-bubble.png");
  glutDisplayFunc(display); // display callback function.

  glClearColor(0.0f,0.0f,0.0f,0.0f);
  gluOrtho2D(0.0,1080,0.0,1080);
  glutSpecialFunc(specialKey); // kayboard callback function.

  glutTimerFunc(0, timer_callback, 0);

  glutMainLoop();
  return 0;
}
