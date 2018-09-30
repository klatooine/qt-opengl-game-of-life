#ifndef BOARD_H
#define BOARD_H

#include "cell.h"
#include <QTimer>
#include <cstdlib>

class Board : public QObject {
  Q_OBJECT

public:
  Board(int sideSize);

  int GetSideSize();
  bool IsCellAlive(int row, int column);
  void SetSize(int size);
  void InitializeSingleGlider();
  void InitializeMultipleGliders();
  void InitializeRandom();

signals:
  void Changed();
  void SizeChanged();

private slots:
  void SetNextTickBoard();

private:
  QTimer *timer_ = new QTimer(this);
  int sideSize_ = 0;
  Cell **board_;

  void initialize();
  int NeighborsNumber(int row, int column);
  int NeighborsNumberInRow(int testRow, int row, int column);
  void ResetBoard();
  void DrawGlider(int x, int y);
  void DrawInverseGlider(int x, int y);
};

#endif // BOARD_H
