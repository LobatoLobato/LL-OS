#include "VGATerminal.hpp"
#include <stdarg.h>

/*==================== PUBLIC METHODS ====================*/

void VGATerminal::write(char character) {
  writeChar(character);
}
void VGATerminal::write(const char* string) {
  writeString(string);
}

void VGATerminal::writeln(const char* fmt) {
  write(fmt);
  writeNewLine();
}
void VGATerminal::writeln(char character) {
  write(character);
  writeNewLine();
}

void VGATerminal::setColor(Color foreground, Color background) {
  m_color = static_cast<Color>((uint8_t)foreground + ((uint8_t)background << 4));
}

void VGATerminal::clear() {
  for (size_t i = 0; i < c_NumRows; i++) {
    clearRow(i);
  }
}

/*==================== PRIVATE METHODS ====================*/
void VGATerminal::writeChar(uchar8_t character) {
  if (character == '\n') {
    writeNewLine();
    return;
  }

  if (m_col > c_NumCols) {
    writeNewLine();
  }

  m_buffer[m_col + c_NumCols * m_row] = (TermChar){
    character : (uint8_t)character,
    color : m_color,
  };

  m_col++;
}

void VGATerminal::writeString(const char* string) {
  while (*string) {
    writeChar(*string);
    string++;
  }
}

void VGATerminal::writeNewLine() {
  m_col = 0;

  if (m_row < c_NumRows - 1) {
    m_row++;
    return;
  }
  scrollDown();
}

void VGATerminal::clearRow(size_t row) {
  TermChar empty = (TermChar){
    character : ' ',
    color : m_color,
  };

  for (size_t col = 0; col < c_NumCols; col++) {
    m_buffer[col + c_NumCols * row] = empty;
  }
}

void VGATerminal::scrollDown() {
  for (size_t row = 0; row < c_NumRows - 1; row++) {
    for (size_t col = 0; col < c_NumCols; col++) {
      size_t curr_row_it = col + c_NumCols * row;
      size_t next_row_it = col + c_NumCols * (row + 1);
      m_buffer[curr_row_it] = m_buffer[next_row_it];
    }
  }
  // m_row--;
  clearRow(c_NumRows - 1);
}
