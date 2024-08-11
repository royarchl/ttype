#ifndef EDITOR_INTERFACE
#define EDITOR_INTERFACE

#include <string>

/*
 * I'm unsure of if some of these features should be stored in this class (which
 * defines a structure for holding text) or the Editor class which would make
 * use of the structure for text and lines.
 */

class EditorInterface {
 public:
  virtual ~EditorInterface() = default;

  /* File operations */
  virtual void LoadFile(const std::string& filename) = 0;
  // virtual bool SaveFile(const std::string& filename) = 0;

  /* Text operations */
  virtual void CharacterInsert(char character) = 0;
  virtual void CharacterBackspace() = 0;
  virtual void CharacterDelete() = 0;
  // virtual void CharacterSpecialDelete() = 0;

  /* Cursor operations */
  virtual void MoveCharacterLeft() = 0;
  virtual void MoveCharacterRight() = 0;
  // virtual void MoveLineUp() = 0;
  // virtual void MoveLineDown() = 0;

  /* Selection operations */
  virtual void TextInsert(const std::string& text) = 0;
  // virtual void TextBackspace(std::size_t start, std::size_t length) = 0;
  // virtual void TextDelete(std::size_t start, std::size_t length) = 0;
  // virtual void ClipboardCopy(std::size_t start, std::size_t length) = 0;
  // virtual void ClipboardPaste() = 0;

  /* Optional */
  // virtual void Undo() = 0;
  // virtual void Redo() = 0;
};

#endif  // EDITOR_INTERFACE
