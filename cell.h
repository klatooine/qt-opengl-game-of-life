#ifndef CELL_H
#define CELL_H


class Cell {
public:
  Cell();
  ~Cell();

  void GiveLive();
  void Kill();

  bool IsAlive();

private:
  bool state_ = false;
};

#endif // CELL_H
