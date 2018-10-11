#include "cell.h"

Cell::Cell() {
  state_ = false;
}

Cell::~Cell() {
}

void Cell::GiveLive() {
  state_ = true;
}

void Cell::Kill() {
  state_ = false;
}

bool Cell::IsAlive() {
  return state_;
}
