#ifndef GAP_BUFFER
#define GAP_BUFFER

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

#include "editor-interface.h"

/*
 * NOTE:
 * std::size_t is an unsigned int which should be used for sizes, lengths, and
 * counts
 */

// Be mindful of which implementation stuff is read by the interface
class GapBuffer : EditorInterface {
 public:
  static const std::size_t kDefaultGapSize = 20;

  /* Constructor with default gap size */
  GapBuffer(std::size_t gsize = kDefaultGapSize) : gap_size_(gsize) {
    InitBuffer(gap_size_);
    std::cout << gap_start_ << " | " << gap_end_ << " | " << gap_size_ << " | "
              << buffer_.capacity() << std::endl;
  }

  /* Constructor with instantiating an existing file */
  // GapBuffer(FILE *file, int gsize = DEFAULT_GAP_SIZE);

  ~GapBuffer() override = default;

  // File operations
  // bool LoadFile(const std::string& filename) override;
  // bool SaveFile(const std::string& filename) override;

  // Text operations
  /* Add a character to the first available slot of the gap buffer */
  void InsertCharacter(char character) override {
    /* Warning! Check to see if the gap has the available space. */
    buffer_.at(gap_start_) = character;
    ++gap_start_;

    if (gap_start_ == gap_end_) {
      // Resize gap
      // THIS PART IS CONFUSING ME ATM.
    }
  }

  /* Remove the last character in the gap buffer. If none, delete the one from
   * the first span. */
  void CharacterBackspace() override {
    /* Warning! Check to see if you are at the beginning of the buffer. */
    --gap_start_;
  }

  /* Remove the first character from the second span. */
  void CharacterDelete() override {
    /* Warning! Check to see if you are at the end of the buffer. */
    ++gap_end_;
  }

  /* Somehow combine the two characters into one slot. May be optional and
   * instead be handled by a 'formatting tree'. */
  // void CharacterSpecialDelete() override;

  // Cursor operations
  void MoveLineUp() override { return; }
  void MoveLineDown() override { return; }

  /* Shift the gap buffer left once: move last char from first span to first
   * char of second span. */
  void MoveCharacterLeft() override {
    buffer_.at(gap_end_) = buffer_.at(gap_start_ - 1);
    --gap_start_;
    --gap_end_;
    // --cursor_;
  }

  /* Shift the gap buffer right once: move first char from second span to last
   * char of first span. */
  void MoveCharacterRight() override {
    buffer_.at(gap_start_) = buffer_.at(gap_end_ + 1);
    ++gap_start_;
    ++gap_end_;
    // ++cursor_;
  }

  // Selection operations
  // void ClipboardCopy(std::size_t start, std::size_t length) override;
  // void ClipboardPaste() override;
  void InsertText(const std::string& text) override {
    /* Warning! Check to see if the size is larger than the gap/buffer. */
    return;
  }

  void DeleteText(std::size_t start, std::size_t length) override {
    /* Warning! Check to see if size is larger than buffer / existing text. */
    return;
  }

  // Optional
  // void Undo() override;
  // void Redo() override;

  void PrintBuffer() const {
    std::cout << '[';
    for (std::size_t i = 0; i < buffer_.capacity(); ++i) {
      if (i == gap_start_) {
        std::cout << '|';
      }
      std::cout << buffer_[i];
      if (i == gap_end_) {
        std::cout << '|';
      }
    }
    std::cout << "] - (" << gap_start_ << ", " << gap_end_ << ", "
              << buffer_.capacity() << ")\n";
  }

 private:
  // why this and not 'std::vector<std::string>'
  std::vector<char> buffer_;
  std::size_t gap_start_;
  std::size_t gap_end_;
  std::size_t gap_size_;  // expand GAP by this value
  std::size_t cursor_;

  // Helper functions
  void InitBuffer(std::size_t size) {
    /* Apparently, reserve does not resize the vector. */
    // buffer_.reserve(size);
    buffer_.resize(size);
    std::fill(buffer_.begin(), buffer_.end(), ' ');
    gap_start_ = 0;
    gap_end_ = size - 1;

    /* why not set 'gap_size_' equal to paramater 'size'? */
    gap_size_ = gap_end_ - gap_start_;
    cursor_ = gap_start_;
  }
  /* Is this necessary when using a vector? I'm leaning towards, no. */
  // void ExpandBuffer(std::size_t size);

  /* This seems useless. */
  void ExpandGap(std::size_t size) { gap_size_ = size; }
};

#endif  // GAP_BUFFER
