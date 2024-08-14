#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>

#include "gap-buffer.h"

int main() {
  GapBuffer buffer;

  ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();

  ftxui::Component component = ftxui::Renderer([&buffer] {
    return ftxui::vbox({
        ftxui::window(ftxui::text("Buffer"),
                      ftxui::paragraph(buffer.PrintBuffer()) | ftxui::inverted),
        ftxui::window(ftxui::text("Input"),
                      ftxui::paragraph(buffer.GetBufferContent())),
    });
  });

  ftxui::Component event_handler =
      ftxui::CatchEvent(component, [&](ftxui::Event event) {
        if (event == ftxui::Event::Escape) {
          screen.ExitLoopClosure()();
        } else if (event == ftxui::Event::Backspace) {
          buffer.CharacterBackspace();
        } else if (event == ftxui::Event::Delete) {
          buffer.CharacterDelete();
        } else if (event == ftxui::Event::ArrowLeft) {
          buffer.MoveCharacterLeft();
        } else if (event == ftxui::Event::ArrowRight) {
          buffer.MoveCharacterRight();
        } else if (event == ftxui::Event::Return) {
          buffer.CharacterInsert('\n');
        } else if (event.is_character()) {
          char c = *event.character().data();
          buffer.CharacterInsert(c);
        }
        return false;
      });
  screen.Loop(event_handler);

  return 0;
}
