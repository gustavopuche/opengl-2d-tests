
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
 private:
  int side;
  float r,g,b;
  int x, y;
};
