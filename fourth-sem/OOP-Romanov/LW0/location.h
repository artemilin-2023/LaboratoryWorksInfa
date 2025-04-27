#ifndef LOCATION_H
#define LOCATION_H

class location {
  public:
    location(int x, int y);
    ~location();
    [[nodiscard]] int get_x() const;
    [[nodiscard]] int get_y() const;
    void set_x(int x);
    void set_y(int y);

  protected:
    int x, y;
};

#endif // LOCATION_H
