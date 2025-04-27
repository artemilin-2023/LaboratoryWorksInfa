#ifndef LOCATION_H
#define LOCATION_H

class location {
  public:
    location(int x, int y);
    ~location();
    [[nodiscard]] int get_x() const;
    [[nodiscard]] int get_y() const;
    void move_to(int x, int y);

  protected:
    int x, y;
};

#endif // LOCATION_H
