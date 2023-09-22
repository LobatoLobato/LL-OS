#pragma once
#include <stddef.h>
#include <stdint.h>

typedef uint8_t uchar8_t;

class VGATerminal {
 public:
  enum class Color : uint8_t {
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Brown = 6,
    Gray = 7,
    DarkGray = 8,
    LightBlue = 9,
    LightGreen = 10,
    LightCyan = 11,
    LightRed = 12,
    Pink = 13,
    Yellow = 14,
    White = 15,
  };

  VGATerminal() {
    clear();
  }

  ~VGATerminal() {
  }

  void write(char string);
  void write(const char* fmt);
  void writeln(char c);
  void writeln(const char* fmt = "");
  void setColor(Color foreground, Color background = VGATerminal::Color::Black);
  void clear();

 private:
  typedef struct {
    uint8_t character;
    Color color;
  } TermChar;

  const size_t c_NumCols = 80;
  const size_t c_NumRows = 25;

  TermChar* m_buffer = (VGATerminal::TermChar*)0xb8000;

  size_t m_col = 0;
  size_t m_row = 0;
  Color m_color = static_cast<Color>((uint8_t)Color::White | (uint8_t)Color::Black << 4);

  void writeChar(uchar8_t character);
  void writeString(const char* string);
  void writeNewLine();
  void clearRow(size_t row);
  void scrollDown();
};