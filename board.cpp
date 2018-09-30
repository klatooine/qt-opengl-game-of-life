#include "board.h"

Board::Board(int sideSize) {
  sideSize_ = sideSize;

  initialize();

  connect(timer_, SIGNAL(timeout()), this, SLOT(SetNextTickBoard()));
  timer_->start(60);
}

void Board::initialize() {
  InitializeSingleGlider();
}

int Board::GetSideSize() {
  return sideSize_;
}

bool Board::IsCellAlive(int row, int column) {
  return board_[row][column].IsAlive();
}

void Board::SetNextTickBoard() {
  int neighbors = 0;

  Cell **nextBoard = new Cell*[sideSize_];

  for (int rowIndex = 0; rowIndex < sideSize_; ++rowIndex) {
    nextBoard[rowIndex] = new Cell[sideSize_];
  }

  for (int rowIndex = 0; rowIndex < sideSize_; rowIndex++) {
    for (int columnIndex = 0; columnIndex < sideSize_; columnIndex++) {
      neighbors = NeighborsNumber(rowIndex, columnIndex);

      Cell * cell = new Cell();

      if(IsCellAlive(rowIndex, columnIndex) && neighbors == 2 || neighbors == 3) {
        cell->GiveLive();

        nextBoard[rowIndex][columnIndex] = *cell;
      }
    }
  }

  delete [] board_;

  board_ = nextBoard;

  emit Changed();
}

int Board::NeighborsNumber(int row, int column) {
    int neighborsNumber = 0;
    int testRow = 0;

    if (row - 1 >= 0) {
      testRow = row - 1;
    } else {
      testRow = sideSize_ - 1;
    }

    neighborsNumber += NeighborsNumberInRow(testRow, row, column);

    testRow = row;

    neighborsNumber += NeighborsNumberInRow(testRow, row, column);

    if (row + 1 <= sideSize_ - 1) {
      testRow = row + 1;
    } else {
      testRow = 0;
    }

    neighborsNumber += NeighborsNumberInRow(testRow, row, column);

    return neighborsNumber;
}

int Board::NeighborsNumberInRow(int testRow, int row, int column) {
  int neighborsNumber = 0;
  int testColumn = 0;

  if (column - 1 >= 0) {
    testColumn = column - 1;
  } else {
    testColumn = sideSize_ - 1;
  }

  if (IsCellAlive(testRow, testColumn)) {
    neighborsNumber++;
  }

  if (testRow != row) {
    testColumn = column;

    if (IsCellAlive(testRow, testColumn)) {
      neighborsNumber++;
    }
  }

  if (column + 1 <= sideSize_ - 1) {
    testColumn = column + 1;
  } else {
    testColumn = 0;
  }

  if (IsCellAlive(testRow, testColumn)) {
      neighborsNumber++;
  }

  return neighborsNumber;
}

void Board::SetSize(int size) {
  sideSize_ = size;

  initialize();

  emit SizeChanged();
}

void Board::ResetBoard() {
  if (board_) {
    delete [] board_;
  }

  board_ = new Cell*[static_cast<unsigned int>(sideSize_)];

  for (int rowIndex = 0; rowIndex < sideSize_; ++rowIndex) {
    board_[rowIndex] = new Cell[static_cast<unsigned int>(sideSize_)];
  }
}

void Board::InitializeSingleGlider() {
  ResetBoard();

  DrawGlider(0, 0);
}

void Board::InitializeMultipleGliders() {
  ResetBoard();

  for (int rowIndex = 3; rowIndex < sideSize_ - 3; rowIndex += 8) {
    for (int columnIndex = 3; columnIndex < sideSize_ - 3; columnIndex += 8) {
      if(rand() % 5) {
        if(rand() % 5) {
          DrawGlider(rowIndex, columnIndex);
        } else {
          DrawInverseGlider(rowIndex, columnIndex);
        }
      }
    }
  }
}

void Board::InitializeRandom() {
  ResetBoard();

  for (int rowIndex = 0; rowIndex < sideSize_; ++rowIndex) {
    for (int columnIndex = 0; columnIndex < sideSize_; ++columnIndex) {
      if(rand() % 3) {
        board_[rowIndex][columnIndex].GiveLive();
      }
    }
  }
}

void Board::DrawGlider(int x, int y) {
  if (x <= sideSize_ - 3 && y <= sideSize_ - 3) {
    board_[x][y+1].GiveLive();
    board_[x+1][y+2].GiveLive();
    board_[x+2][y].GiveLive();
    board_[x+2][y+1].GiveLive();
    board_[x+2][y+2].GiveLive();
  }
}

void Board::DrawInverseGlider(int x, int y) {
  if (x <= sideSize_ - 3 && y <= sideSize_ - 3) {
    board_[x][y+1].GiveLive();
    board_[x+1][y].GiveLive();
    board_[x+2][y].GiveLive();
    board_[x+2][y+1].GiveLive();
    board_[x+2][y+2].GiveLive();
  }
}
