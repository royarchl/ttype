#include "gap-buffer.h"

int main() {
  GapBuffer gap_buffer;

  gap_buffer.PrintBuffer();

  gap_buffer.InsertCharacter('c');
  gap_buffer.InsertCharacter('a');
  gap_buffer.InsertCharacter('r');
  gap_buffer.InsertCharacter('r');
  gap_buffer.InsertCharacter('y');

  gap_buffer.PrintBuffer();

  gap_buffer.CharacterBackspace();

  gap_buffer.PrintBuffer();

  gap_buffer.MoveCharacterLeft();
  gap_buffer.MoveCharacterLeft();

  gap_buffer.PrintBuffer();

  gap_buffer.CharacterDelete();

  gap_buffer.PrintBuffer();

  return 0;
}

/*
 * GapEnd: 19 ... -> 18 -> 17 ... -> 18
 *
 */
