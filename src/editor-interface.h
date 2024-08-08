#ifndef EDITOR_INTERFACE
#define EDITOR_INTERFACE

#include <string>

class EditorInterface {
 public:
  virtual ~EditorInterface() = default;

  // File operations
  // virtual bool LoadFile(const std::string& filename) = 0;
  // virtual bool SaveFile(const std::string& filename) = 0;

  // Text operations
  virtual void InsertCharacter(char character) = 0;
  virtual void CharacterBackspace() = 0;
  virtual void CharacterDelete() = 0;
  // virtual void CharacterSpecialDelete() = 0;

  // Cursor operations
  virtual void MoveLineUp() = 0;
  virtual void MoveLineDown() = 0;
  virtual void MoveCharacterLeft() = 0;
  virtual void MoveCharacterRight() = 0;

  // Selection operations
  // virtual void ClipboardCopy(std::size_t start, std::size_t length) = 0;
  // virtual void ClipboardPaste() = 0;
  virtual void InsertText(const std::string& text) = 0;
  virtual void DeleteText(std::size_t start, std::size_t length) = 0;

  // Optional
  // virtual void Undo() = 0;
  // virtual void Redo() = 0;
};

#endif  // EDITOR_INTERFACE
