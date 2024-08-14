#ifndef GAP_BUFFER
#define GAP_BUFFER

#include <cstddef>
#include <utility>

#include "editor-interface.h"

/*
 * I am intentionally using C-style arrays and pointers because using
 * std::vector confused me. Additionally, though I know I can do this with
 * indices, I ~want to use pointers.
 */

class GapBuffer : EditorInterface {
 public:
  /* Constructors */
  GapBuffer(std::size_t gsize = kDefaultGapSize);
  GapBuffer(const std::string& filename, std::size_t gsize = kDefaultGapSize);
  ~GapBuffer() override; /* = default; */

  /* Public methods */
  void LoadFile(const std::string& filename) override;
  void CharacterInsert(char character) override;
  void CharacterBackspace() override;
  void CharacterDelete() override;
  void MoveCharacterLeft() override;
  void MoveCharacterRight() override;
  void TextInsert(const std::string& text) override;
  std::string PrintBuffer() const;

  /* Methods to assist testing */
  std::size_t GetBufferSize() const { return (buffer_end_ - buffer_start_); }
  std::size_t GetGapSize() const { return (gap_end_ - gap_start_); }
  std::size_t GetDefaultGapSize() const { return kDefaultGapSize; }
  std::pair<std::size_t, std::size_t> GetGapOffsets() const {
    return {(gap_start_ - buffer_start_), (gap_end_ - buffer_start_)};
  }
  std::string GetBufferContent() const {  // Intentionally copying string
    std::string buffer_content;
    for (const char* it = buffer_start_; it < buffer_end_; ++it) {
      if (it == gap_start_) {
        // Remember to REMOVE THIS when I walk away from TUI
        buffer_content += '|';
        it = gap_end_;
        if (it >= buffer_end_) {
          break;
        }
      }
      buffer_content += *it;
    }
    return buffer_content;
  }

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
