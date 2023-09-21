#pragma once
#include <stddef.h>
#include <stdint.h>

typedef uint8_t uchar8_t;

class Console {
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

  /**
   * @brief
   */
  template <typename Arg>
  static Console write(Arg arg) {
    writeString(arg);

    return s_instance;
  }
  template <typename Arg, typename... Args>
  static Console write(Arg arg, Args... args) {
    writeString(arg);

    write(args...);

    return s_instance;
  }
  static Console writef(const char* fmt, ...);
  /**
   * @brief
   */
  static Console writeln(const char* fmt = "", ...);
  /**
   * @brief
   */
  static Console setColor(Color foreground, Color background = Console::Color::Black);
  /**
   * @brief
   */
  static Console clear();

 private:
  typedef struct {
    uint8_t character;
    Color color;
  } TermChar;

  static const Console s_instance;
  static const size_t c_NumCols = 80;
  static const size_t c_NumRows = 27;

  static TermChar* s_buffer;

  static size_t s_col;
  static size_t s_row;
  static Color s_color;

  static void writeChar(uchar8_t character);
  static void writeString(const char* string);
  static void writeNumber(float num);
  static void writeNumber(double num);
  static void writeNumber(int64_t num);
  static void writeNumber(uint64_t num);
  static void writeNewLine();
  static void clearRow(size_t row);
};