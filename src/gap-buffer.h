#ifndef GAP_BUFFER
#define GAP_BUFFER

#include "editor-interface.h"

/*
 * I am intentionally using C-style arrays and pointers because using
 * std::vector confused me. Additionally, though I know I can do this with
 * indices, I ~want to use pointers.
 */

class GapBuffer : EditorInterface {
 public:
  GapBuffer(std::size_t gsize = kDefaultGapSize);

  GapBuffer(const std::string& filename, std::size_t gsize = kDefaultGapSize);

  ~GapBuffer() override; /* = default; */

  void LoadFile(const std::string& filename) override;

  void CharacterInsert(char character) override;

  void CharacterBackspace() override;

  void CharacterDelete() override;

  void MoveCharacterLeft() override;

  void MoveCharacterRight() override;

  void TextInsert(const std::string& text) override;

  void PrintBuffer();

 private:
  /* buffer_ can be used/referenced to be the first element in the array. */
  /* char buffer_[] = {}; */

  char* cursor_;
  char* buffer_start_;
  char* buffer_end_;
  char* gap_start_;
  char* gap_end_;

  static const std::size_t kDefaultGapSize = 16;
  std::size_t gap_size_;  // Size to increase the gap by (not used)

  void InitBuffer(std::size_t size);
  void EnlargeBuffer();
};

#endif  // GAP_BUFFER
