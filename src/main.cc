#include "gap-buffer.h"

int main() {
  GapBuffer gap_buffer;

  gap_buffer.TextInsert("Theaiak");
  gap_buffer.PrintBuffer();

  for (int i = 0; i < 5; ++i) {
    gap_buffer.MoveCharacterLeft();
  }
  gap_buffer.PrintBuffer();

  gap_buffer.MoveCharacterRight();
  gap_buffer.PrintBuffer();

  gap_buffer.TextInsert("01234567");  // 16 (resize)
  gap_buffer.PrintBuffer();

  gap_buffer.CharacterInsert('w');  // 17
  gap_buffer.PrintBuffer();

  for (int i = 0; i < 20; ++i) {
    gap_buffer.CharacterDelete();
  }
  gap_buffer.PrintBuffer();

  // gap_buffer.LoadFile("example.txt");
  // gap_buffer.PrintBuffer();

  for (int i = 0; i < 8; ++i) {
    gap_buffer.MoveCharacterLeft();
  }
  gap_buffer.PrintBuffer();

  gap_buffer.CharacterBackspace();
  gap_buffer.CharacterBackspace();
  gap_buffer.PrintBuffer();

  for (int i = 0; i < 3; ++i) {
    gap_buffer.MoveCharacterRight();
  }
  gap_buffer.PrintBuffer();

  return 0;
}
