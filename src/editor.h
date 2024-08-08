#ifndef EDITOR
#define EDITOR

#include "editor-interface.h"

class Editor {
 public:
  Editor(EditorInterface* textEditor);
  ~Editor();

  // File operations
  // EXAMPLE of inline implementation. Put in a .cc file instead.
  bool loadFile(const std::string& filename);
  bool saveFile(const std::string& filename);

  // Text operations
  void InsertCharacter(char character);
  void CharacterBackspace();
  void CharacterDelete();
  void CharacterSpecialDelete();

  // Cursor operations
  void MoveLineUp();
  void MoveLineDown();
  void MoveCharacterLeft();
  void MoveCharacterRight();

  // Selection operations
  void ClipboardCopy(std::size_t start, std::size_t length);
  void ClipboardPaste();
  void InsertText(const std::string& text);
  void DeleteText(std::size_t start, std::size_t length);

  // Optional
  void Undo();
  void Redo();

 private:
  EditorInterface* textEditor_;
};

#endif  // EDITOR
