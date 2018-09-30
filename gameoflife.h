#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <QMainWindow>
#include <board.h>

namespace Ui {
class GameOfLife;
}

class GameOfLife : public QMainWindow {
  Q_OBJECT

public:
  explicit GameOfLife(QWidget *parent = nullptr);
  ~GameOfLife();

private slots:
  void on_setSize_btn_clicked();

  void on_singleGliderReset_btn_clicked();

  void on_multipleGlidersReset_btn_clicked();

  void on_randomReset_btn_clicked();

private:
  Ui::GameOfLife *ui;
  int boardSize_ = 200;
  Board * board_ = nullptr;

  void initialize();
};

#endif // GAMEOFLIFE_H
