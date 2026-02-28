//
// Created by Binh Nguyen Thanh on 28/2/26.
//

#include "Cell.h"
#include <iostream>
#include "Snake/SnakeData.h"

Cell::Cell(int Row, int Col, Assets &AssetList) :
    Row(Row),
    Column(Col),
    AssetList(AssetList),
    BackgroundRect(
      Column * Config::CELL_SIZE + Config::PADDING,
      Row * Config::CELL_SIZE + Config::PADDING,
      Config::CELL_SIZE,
      Config::CELL_SIZE),
    BackgroundColor(
      (Row + Column) % 2 == 0
          ? Config::CELL_COLOR_A
          : Config::CELL_COLOR_B
    ) {
  Initialize();
}

void Cell::HandleEvent(const SDL_Event &E) {
  if (E.type == UserEvents::ADVANCE) {
    Advance(E.user);
  }
}

void Cell::Render(SDL_Surface *Surface) {
    SDL_FillSurfaceRect(Surface, &BackgroundRect,
    SDL_MapRGB(
      SDL_GetPixelFormatDetails(Surface->format),
      nullptr,
      BackgroundColor.r,
      BackgroundColor.g,
      BackgroundColor.b
    )
  );
  if (State == CellState::Apple) {
    AssetList.Apple.Render(Surface, &BackgroundRect);
  } else if (State == CellState::Snake) {
    SDL_FillSurfaceRect(Surface, &BackgroundRect,
      SDL_MapRGB(
        SDL_GetPixelFormatDetails(Surface->format),
        nullptr,
        Config::SNAKE_COLOR.r,
        Config::SNAKE_COLOR.g,
        Config::SNAKE_COLOR.b
      )
    );
  }
}

void Cell::Update(Uint64 DeltaTime) {
}

void Cell::Initialize() {
  State = CellState::Empty;
  SnakeDuration = 0;
  int MiddleRow{Config::GRID_ROWS / 2};
  if (Row == MiddleRow && Column == 2) {
    State = CellState::Snake;
    SnakeDuration = 1;
  } else if (Row == MiddleRow && Column == 3) {
    State = CellState::Snake;
    SnakeDuration = 2;
  } else if (Row == MiddleRow && Column == 11) {
    State = CellState::Apple;
  }
}

void Cell::Advance(const SDL_UserEvent& event) {
  SnakeData* Data = static_cast<SnakeData*>(event.data1);

  bool isThisCell{
    Data->HeadRow == Row &&
    Data->HeadCol == Column
  };

  if (isThisCell) {
    State = CellState::Snake;
    SnakeDuration = Data->Length;
  } else if (State == CellState::Snake) {
    --SnakeDuration;
    if (SnakeDuration == 0) {
      State = CellState::Empty;
    }
  }
}
