#include "gap-buffer.h"

#include <cstddef>  // std::size_t
#include <fstream>
#include <iostream>
#include <string>

GapBuffer::GapBuffer(std::size_t gsize) : gap_size_(gsize) {
  InitBuffer(gsize);
}

GapBuffer::GapBuffer(const std::string& filename, std::size_t gsize)
    : gap_size_(gsize) {
  LoadFile(filename);
}

GapBuffer::~GapBuffer() = default;

void GapBuffer::LoadFile(const std::string& filename) {
  /* Opens the file in binary mode and immediately jumps to the end. */
  std::ifstream file(filename, std::ios::binary | std::ios::ate);

  if (!file) {
    std::cout << "Error opening file.\n";
    return;
  }

  /* Returns the current position in the stream. */
  std::streampos file_size = file.tellg();
  /* Move back to the beginning of the file. */
  file.seekg(0, std::ios::beg);

  InitBuffer(static_cast<std::size_t>(file_size) + gap_size_);

  char ch;
  while (file.get(ch)) {
    CharacterInsert(ch);
  }

  file.close();
}

void GapBuffer::CharacterInsert(char character) {
  *(gap_start_++) = character;
  ++cursor_;

  if (gap_start_ == gap_end_) {
    EnlargeBuffer();
  }
}

void GapBuffer::CharacterBackspace() {
  if (gap_start_ == buffer_start_) {
    return;
  }
  --gap_start_;
  --cursor_;
}

void GapBuffer::CharacterDelete() {
  if (gap_end_ == buffer_end_) {
    return;
  }
  ++gap_end_;
}

void GapBuffer::MoveCharacterLeft() {
  if (gap_start_ == buffer_start_) {
    return;
  }

  *(gap_end_ - 1) = *(gap_start_ - 1);

  gap_start_--;
  gap_end_--;
  cursor_--;
}

void GapBuffer::MoveCharacterRight() {
  if (gap_end_ == buffer_end_) {
    return;
  }

  *gap_start_ = *gap_end_;

  gap_start_++;
  gap_end_++;
  cursor_++;
}

void GapBuffer::TextInsert(const std::string& text) {
  for (auto ch : text) {
    CharacterInsert(ch);
  }
}

void GapBuffer::PrintBuffer() {
  std::cout << '[';

  for (char* it = buffer_start_; it < buffer_end_; ++it) {
    if (it == gap_start_) {
      std::cout << '(';
    }
    if (it >= gap_start_ && it < gap_end_) {
      *it = '_';
    }
    std::cout << *it;
    if (it == gap_end_ - 1) {
      std::cout << ')';
    }
  }
  std::cout << "] (" << (gap_end_ - gap_start_) << ", "
            << (buffer_end_ - buffer_start_) << ")\n";
}

void GapBuffer::InitBuffer(std::size_t size) {
  /* char buffer[size]; (stack-allocated) */

  /* C++ equivalent of buffer = (char*) malloc(size) (heap-allocated) */
  buffer_start_ = new char[size];
  buffer_end_ = buffer_start_ + size;

  gap_start_ = cursor_ = buffer_start_;
  gap_end_ = buffer_end_;
}

void GapBuffer::EnlargeBuffer() {
  std::size_t old_buffer_size = buffer_end_ - buffer_start_;
  std::size_t new_buffer_size = old_buffer_size * 2;

  char* new_buffer = new char[new_buffer_size];

  /*
   * std::copy(buffer_start_, buffer_end_, new_buffer);
   * Chose against this because the internal iterator/pointer is never exposed
   * so I can't dynamically assign the gap_start_ and gap_end_ during the
   * copying process.
   */

  char* new_buffer_ptr = new_buffer;
  for (char* it = buffer_start_; it < gap_start_; ++it, ++new_buffer_ptr) {
    *new_buffer_ptr = *it;
  }

  gap_start_ = new_buffer_ptr;
  new_buffer_ptr += old_buffer_size;
  char* new_gap_end = new_buffer_ptr;

  for (char* it = gap_end_; it < buffer_end_; ++it, ++new_buffer_ptr) {
    *new_buffer_ptr = *it;
  }

  delete[] buffer_start_;

  buffer_start_ = new_buffer;
  buffer_end_ = buffer_start_ + new_buffer_size;

  gap_end_ = new_gap_end;
  std::cout << gap_start_ - new_buffer << ':' << old_buffer_size << ':'
            << gap_end_ - new_buffer << '\n';
}
