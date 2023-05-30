class Sprite
{
 public:
  Sprite(int side = 16, int x = 0, int y = 0) :
    side{side},
    x{x},
    y{y}
  {
    r = 1.0;
    g = 0.0;
    b = 0.0;
  }
  void paint();
  void setTexture();
  void setColor(float r, float g, float b);
  void setTexture(int row, int column, int maxTextures);
 private:
  int side;
  float r,g,b;
  float u0,u1,v0,v1;
  int x, y;
};
