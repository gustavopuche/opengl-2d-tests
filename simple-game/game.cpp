#include "lodepng.h"
#include "sprites.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

// Global variables to move the object.

float xr = 180, yr = 170;
size_t sprBlckX,sprBlckY,sprOffX,sprOffY;

enum class SpriteDirection {LEFT,RIGHT,UP,DOWN};
enum class SpriteMove {HORIZONTAL,VERTICAL};

SpriteDirection currSprtDir = SpriteDirection::LEFT;

const size_t TEXCOL = 2;
const size_t MAP_SIDE = 40;
const size_t BLOCK_SIDE = 10;
const size_t SPRITE_SIDE = 40;
const size_t BLOCKS_PER_SPRITE = SPRITE_SIDE / BLOCK_SIDE;

std::vector<std::vector<size_t>> gameMap = {{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1},
  {1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1},
  {1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1},
  {1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
  {1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1},
  {1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1},
  {1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1},
  {1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1},
  {1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
  {1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1},
  {1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1},
  {1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1},
  {1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1},
  {1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1},
  {1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1},
  {1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1},
  {1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
  {1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1},
  {1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1},
  {1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1},
  {1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
  }};

std::vector<unsigned char> img;
unsigned w, h;
GLuint texture[0];

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
  glColor3f(1 ,0.5 ,0);
  glVertex2f(0,0);
  glVertex2f(BLOCK_SIDE,0);
  glVertex2f(BLOCK_SIDE,BLOCK_SIDE);
  glVertex2f(0,BLOCK_SIDE);
  glEnd();
}

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

void paintSprite()
{
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
  glColor3f(1 ,1 ,0);

  switch(currSprtDir){
  case SpriteDirection::LEFT:
    glTexCoord2f(1.0/TEXCOL, 1); glVertex2f(0+xr,0+yr);
    glTexCoord2f(0  , 1); glVertex2f(SPRITE_SIDE+xr,0+yr);
    glTexCoord2f(0  , 0); glVertex2f(SPRITE_SIDE+xr,SPRITE_SIDE+yr);
    glTexCoord2f(1.0/TEXCOL, 0); glVertex2f(0+xr,SPRITE_SIDE+yr);
    break;
  case SpriteDirection::RIGHT:
    glTexCoord2f(0, 1); glVertex2f(0+xr,0+yr);
    glTexCoord2f(1.0/TEXCOL, 1); glVertex2f(SPRITE_SIDE+xr,0+yr);
    glTexCoord2f(1.0/TEXCOL, 0); glVertex2f(SPRITE_SIDE+xr,SPRITE_SIDE+yr);
    glTexCoord2f(0, 0); glVertex2f(0+xr,SPRITE_SIDE+yr);
    break;
  case SpriteDirection::UP:
    glTexCoord2f(0, 0); glVertex2f(0+xr,0+yr);
    glTexCoord2f(0, 1); glVertex2f(SPRITE_SIDE+xr,0+yr);
    glTexCoord2f(1.0/TEXCOL, 1); glVertex2f(SPRITE_SIDE+xr,SPRITE_SIDE+yr);
    glTexCoord2f(1.0/TEXCOL, 0); glVertex2f(0+xr,SPRITE_SIDE+yr);
    break;
  case SpriteDirection::DOWN:
    glTexCoord2f(1.0/TEXCOL, 0); glVertex2f(0+xr,0+yr);
    glTexCoord2f(1.0/TEXCOL, 1); glVertex2f(SPRITE_SIDE+xr,0+yr);
    glTexCoord2f(0, 1); glVertex2f(SPRITE_SIDE+xr,SPRITE_SIDE+yr);
    glTexCoord2f(0, 0); glVertex2f(0+xr,SPRITE_SIDE+yr);
    break;
  }
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

std::vector<Sprite> bubbles;

void createBubbles()
{
  bubbles.push_back(Sprite(SPRITE_SIDE,xr+SPRITE_SIDE,yr));
  bubbles.push_back(Sprite(SPRITE_SIDE,xr-SPRITE_SIDE,yr));
  bubbles[1].setTexture(0,1,2);
  bubbles[1].setColor(0,1,0);
  bubbles.push_back(Sprite(SPRITE_SIDE,xr-2*SPRITE_SIDE,yr));
  bubbles[2].setColor(1,1,1);
}

void paintBubbles()
{
  for(size_t i = 0;i < bubbles.size(); i++)
  {
    bubbles[i].paint();
  }
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  // glMatrixMode(GL_MODELVIEW);      // To operate on Model-View matrix
  // glLoadIdentity();                // Reset the model-view matrix

  paintMap();

  paintBubbles();

  paintSprite();

  glFlush();
  glutPostRedisplay();
  glutSwapBuffers();
}

void calculateSpritePos()
{
  sprBlckX = (size_t)xr / 10;
  sprBlckY = (size_t)yr / 10;
  sprOffX = (size_t)xr % 10;
  sprOffY = (size_t)yr % 10;
}

void printSpritePos()
{
  std::cout << "(" << xr << "," << yr << ") " ;
  std::cout << "Block:[" << (size_t)xr / 10 << " " << (size_t)yr / 10 << "] ";
  std::cout << "Offset:< "<< (size_t)xr % 10 << " " << (size_t)yr % 10 << "> " << std::endl;
}

bool wallCollision(size_t x, size_t y, SpriteMove moving)
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

bool moveSpriteTo(SpriteDirection direction)
{
  calculateSpritePos();

  switch(direction){
  case SpriteDirection::LEFT:
    currSprtDir = SpriteDirection::LEFT;
    if(wallCollision(sprBlckX - 1,sprBlckY,SpriteMove::HORIZONTAL))
    {
      return false;
    }
    break;
  case SpriteDirection::RIGHT:
    currSprtDir = SpriteDirection::RIGHT;
    if(wallCollision(sprBlckX + BLOCKS_PER_SPRITE,sprBlckY,SpriteMove::HORIZONTAL))
    {
      return false;
    }
    break;
  case SpriteDirection::UP:
    currSprtDir = SpriteDirection::UP;
    if(wallCollision(sprBlckX,sprBlckY + BLOCKS_PER_SPRITE,SpriteMove::VERTICAL))
    {
      return false;
    }
    break;
  case SpriteDirection::DOWN:
    currSprtDir = SpriteDirection::DOWN;
    if(wallCollision(sprBlckX,sprBlckY - 1,SpriteMove::VERTICAL))
    {
      return false;
    }
    break;
  }

  return true;
}

void collision()
{
  std::cout << "Wall collision!!!" << std::endl;
}

void specialKey(int key, int x, int y)
{
  switch(key){
   case GLUT_KEY_UP: // when the up key is pressed.
     if(moveSpriteTo(SpriteDirection::UP))
     {
       yr++;
     }
     printSpritePos();
     glutPostRedisplay();
     break;
   case GLUT_KEY_DOWN: // when the down key is pressed.
     if(moveSpriteTo(SpriteDirection::DOWN))
     {
       yr--;
     }
     printSpritePos();
     glutPostRedisplay();
     break;
   case GLUT_KEY_LEFT: // when the left key is pressed.
     if(moveSpriteTo(SpriteDirection::LEFT))
     {
       xr--;
     }
     else
     {
       collision();
     }
     printSpritePos();
     glutPostRedisplay();
     break;
   case GLUT_KEY_RIGHT: // when the right key is pressed.
     if(moveSpriteTo(SpriteDirection::RIGHT))
     {
       xr++;
     }
     else
     {
       collision();
     }
     printSpritePos();
     break;
  }
}

int main(int argc, char** argv)
{
  std::cout << "Use arrow keys..." << std::endl;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(400, 400);
  glutInitWindowPosition(50, 50);
  glutCreateWindow("sIMPle gAMe!");

  // Create bubbles sprites.
  createBubbles();

  decodeOneStep("pacmat-bubble.png");
  glutDisplayFunc(display); // display callback function.

  glClearColor(0,0,0,0);
  gluOrtho2D(0.0,400,0.0,400);
  glutSpecialFunc(specialKey); // kayboard callback function.

  glutMainLoop();
  return 0;
}
