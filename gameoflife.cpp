#include "gameoflife.h"
#include "ui_gameoflife.h"

GameOfLife::GameOfLife(QWidget *parent) : QMainWindow(parent), ui(new Ui::GameOfLife) {
  ui->setupUi(this);

  board_ = new Board(boardSize_);

  ui->boardSize_input->setValue(boardSize_);
  ui->boardWidget->SetBoard(board_);
}

GameOfLife::~GameOfLife() {
  delete ui;
}

void GameOfLife::on_setSize_btn_clicked() {
  board_->SetSize(static_cast<int>(ui->boardSize_input->value()));
}

void GameOfLife::on_singleGliderReset_btn_clicked() {
  board_->DrawSingleGlider();
}

void GameOfLife::on_multipleGlidersReset_btn_clicked() {
  board_->DrawMultipleGliders();
}

void GameOfLife::on_randomReset_btn_clicked()
{
  board_->DrawRandom();

}
