#include "lodepng.h"
#include "seriefactory.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <memory>

// Global variables to move the object.

float xr = 40, yr = 40;
size_t sprBlckX,sprBlckY,sprOffX,sprOffY;

enum class SpriteDirection {LEFT,RIGHT,UP,DOWN};
enum class SpriteMove {HORIZONTAL,VERTICAL};

SpriteDirection currSprtDir = SpriteDirection::LEFT;
std::unique_ptr<SerieFactory> upAllBubbles;
const size_t TEXCOL = 2;
const size_t MAP_SIDE = 27;
const size_t BLOCK_SIDE = 40;
const size_t SPRITE_SIDE = 40;
const size_t BLOCKS_PER_SPRITE = SPRITE_SIDE / BLOCK_SIDE;
const size_t TEXTURES_PER_LINE = 20;

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

std::vector<unsigned char> img;
unsigned w, h;
GLuint texture[0];
auto serieFunct = [](int x){return x * 4;};
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

// Paint hero sprite
void paintSprite()
{
  float u0,u1,v0,v1;
  size_t column = 0;
  size_t row = 0;
  size_t maxTextures = TEXTURES_PER_LINE;
  u0 = 0.0 + column * 1.0 / maxTextures;
  u1 = u0 + 1.0 / maxTextures;
  v0 = 0.0 + row * 1.0 / maxTextures;
  v1 = v0 + 1.0 / maxTextures;

  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
  glColor4f(1.0f, 1.0f, 0.0f, 1.0f);

  switch(currSprtDir){
  case SpriteDirection::LEFT:
    glTexCoord2f(u1, v1); glVertex2f(0+xr,0+yr);
    glTexCoord2f(u0, v1); glVertex2f(SPRITE_SIDE+xr,0+yr);
    glTexCoord2f(u0, v0); glVertex2f(SPRITE_SIDE+xr,SPRITE_SIDE+yr);
    glTexCoord2f(u1, v0); glVertex2f(0+xr,SPRITE_SIDE+yr);
    break;
  case SpriteDirection::RIGHT:
    glTexCoord2f(u0, v1); glVertex2f(0+xr,0+yr);
    glTexCoord2f(u1, v1); glVertex2f(SPRITE_SIDE+xr,0+yr);
    glTexCoord2f(u1, v0); glVertex2f(SPRITE_SIDE+xr,SPRITE_SIDE+yr);
    glTexCoord2f(u0, v0); glVertex2f(0+xr,SPRITE_SIDE+yr);
    break;
  case SpriteDirection::UP:
    glTexCoord2f(u0, v0); glVertex2f(0+xr,0+yr);
    glTexCoord2f(u0, v1); glVertex2f(SPRITE_SIDE+xr,0+yr);
    glTexCoord2f(u1, v1); glVertex2f(SPRITE_SIDE+xr,SPRITE_SIDE+yr);
    glTexCoord2f(u1, v0); glVertex2f(0+xr,SPRITE_SIDE+yr);
    break;
  case SpriteDirection::DOWN:
    glTexCoord2f(u1, v0); glVertex2f(0+xr,0+yr);
    glTexCoord2f(u1, v1); glVertex2f(SPRITE_SIDE+xr,0+yr);
    glTexCoord2f(u0, v1); glVertex2f(SPRITE_SIDE+xr,SPRITE_SIDE+yr);
    glTexCoord2f(u0, v0); glVertex2f(0+xr,SPRITE_SIDE+yr);
    break;
  }
  glEnd();
  glDisable(GL_TEXTURE_2D);
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

bool wallCollision(size_t x, size_t y, SpriteMove moving)
{
  upAllBubbles->findElem(x,y,10);

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
    if(wallCollision(sprBlckX - 1,sprBlckY,SpriteMove::HORIZONTAL))
    {
      return false;
    }
    break;
  case SpriteDirection::RIGHT:
    if(wallCollision(sprBlckX + BLOCKS_PER_SPRITE,sprBlckY,SpriteMove::HORIZONTAL))
    {
      return false;
    }
    break;
  case SpriteDirection::UP:
    if(wallCollision(sprBlckX,sprBlckY + BLOCKS_PER_SPRITE,SpriteMove::VERTICAL))
    {
      return false;
    }
    break;
  case SpriteDirection::DOWN:
    if(wallCollision(sprBlckX,sprBlckY - 1,SpriteMove::VERTICAL))
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
      xr--;
      result = true;
    }
    break;
  case SpriteDirection::RIGHT:
    if(canMoveSpriteTo(SpriteDirection::RIGHT))
    {
      xr++;
      result = true;
    }
    break;
  case SpriteDirection::UP:
    if(canMoveSpriteTo(SpriteDirection::UP))
    {
      yr++;
      result = true;
    }
    break;
  case SpriteDirection::DOWN:
    if(canMoveSpriteTo(SpriteDirection::DOWN))
    {
      yr--;
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
     }
     // printSpritePos();
     glutPostRedisplay();
     break;
   case GLUT_KEY_DOWN: // when the down key is pressed.
     if(canMoveSpriteTo(SpriteDirection::DOWN))
     {
       currSprtDir = SpriteDirection::DOWN;
     }
     // printSpritePos();
     glutPostRedisplay();
     break;
   case GLUT_KEY_LEFT: // when the left key is pressed.
     if(canMoveSpriteTo(SpriteDirection::LEFT))
     {
       currSprtDir = SpriteDirection::LEFT;
     }
     else
     {
       collision();
     }
     // printSpritePos();
     glutPostRedisplay();
     break;
   case GLUT_KEY_RIGHT: // when the right key is pressed.
     if(canMoveSpriteTo(SpriteDirection::RIGHT))
     {
       currSprtDir = SpriteDirection::RIGHT;
     }
     else
     {
       collision();
     }
     // printSpritePos();
     break;
  }
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  // glMatrixMode(GL_MODELVIEW);      // To operate on Model-View matrix
  // glLoadIdentity();                // Reset the model-view matrix

  paintMap();

  // Paint bubbles generated by the SerieFactory.
  upAllBubbles->paint();

  moveSpriteTo(currSprtDir);
  paintSprite();

  glFlush();
  glutPostRedisplay();
  glutSwapBuffers();
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

  // Create bubbles sprites.
  createBubbles();

  decodeOneStep("pacmat-bubble.png");
  glutDisplayFunc(display); // display callback function.

  glClearColor(0.0f,0.0f,0.0f,0.0f);
  gluOrtho2D(0.0,1080,0.0,1080);
  glutSpecialFunc(specialKey); // kayboard callback function.

  glutMainLoop();
  return 0;
}
