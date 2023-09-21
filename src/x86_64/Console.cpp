#include "Console.hpp"
#include <stdarg.h>

Console::TermChar* Console::s_buffer = (Console::TermChar*)0xb8000;
size_t Console::s_col = 0;
size_t Console::s_row = 0;
Console::Color Console::s_color = static_cast<Console::Color>((uint8_t)Console::Color::White | (uint8_t)Console::Color::Black << 4);

/*==================== PUBLIC METHODS ====================*/
Console Console::writef(const char* fmt, ...) {
  writeString(fmt);
  // https://en.cppreference.com/w/cpp/utility/variadic

  return Console::s_instance;
}

Console Console::writeln(const char* fmt, ...) {
  write(fmt);
  writeNewLine();

  return Console::s_instance;
}

Console Console::setColor(Color foreground, Color background) {
  s_color = static_cast<Color>((uint8_t)foreground + ((uint8_t)background << 4));

  return Console::s_instance;
}

Console Console::clear() {
  for (size_t i = 0; i < c_NumRows; i++) {
    clearRow(i);
  }

  return Console::s_instance;
}

/*==================== PRIVATE METHODS ====================*/
void Console::writeChar(uchar8_t character) {
  if (character == '\n') {
    writeln();
    return;
  }

  if (s_col > c_NumCols) {
    writeln();
  }

  s_buffer[s_col + c_NumCols * s_row] = (TermChar){
    character : (uint8_t)character,
    color : s_color,
  };

  s_col++;
}

void Console::writeString(const char* string) {
  while (*string) {
    writeChar(*string);
    string++;
  }
}

void Console::writeNewLine() {
  s_col = 0;

  if (s_row < c_NumRows - 1) {
    s_row++;
    return;
  }

  for (size_t row = 1; row < c_NumRows; row++) {
    for (size_t col = 0; col < c_NumCols; col++) {
      TermChar character = s_buffer[col + c_NumCols * row];
      s_buffer[col + c_NumCols * (row - 1)] = character;
    }
  }

  clearRow(c_NumCols - 1);
}

void Console::clearRow(size_t row) {
  TermChar empty = (TermChar){
    character : ' ',
    color : s_color,
  };

  for (size_t col = 0; col < c_NumCols; col++) {
    s_buffer[col + c_NumCols * row] = empty;
  }
}