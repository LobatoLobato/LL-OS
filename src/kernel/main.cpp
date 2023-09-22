#include "VGATerminal.hpp"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

// #include "Console.hpp"
// #include "String.hpp"

extern "C" void kernel_main() {
  VGATerminal terminal;
  // const char* numbers[] = {
  //     "0",
  //     "1",
  //     "2",
  //     "3",
  //     "4",
  //     "5",
  //     "6",
  //     "7",
  //     "8",
  //     "9",
  //     "10",
  //     "11",
  //     "12",
  //     "13",
  //     "14",
  //     "15",
  //     "16",
  //     "17",
  //     "18",
  //     "19",
  //     "20",
  //     "21",
  //     "22",
  //     "23",
  //     "24",
  //     "25",
  //     "26",
  //     "27",
  //     "28",
  //     "29",
  //     "30",
  // };
  // int i = 0;
  // while (true)
  //   terminal.writeln(numbers[i++ % 31]);

  using Color = VGATerminal::Color;

  terminal.clear();
  terminal.setColor(Color::LightGreen);
  terminal.writeln("                            _   __        _                 ");
  terminal.setColor(Color::Green);
  terminal.writeln("                  |  |  __ / \\ (_   __   |_  |_|_ __ |_  o _|_");
  terminal.setColor(Color::LightGreen);
  terminal.writeln("                  |_ |_    \\_/ __)       |_)   |     |_) |  |_");
  terminal.writeln();

  terminal.setColor(Color::Yellow);
  terminal.write((
      "                              (@@@@@@@@@@@@@@@@                \n"
      "                          @@@ @@@@@@@@@@@@@@@  @@@@@           \n"
      "                        @. @@@@@     @@@@@@*@@@*@@@@@@@        \n"
      "                   @@@@ @@@@@@  @@@ #@@@@ @@ @ @@@@@@@@@@      \n"
      "                 @@@@@@.@@@@  @@@@@@@@@@@   @@@@@@@@@@@@@@@    \n"
      "                  @@  @@ @@@@@@.   @@@/ @@@  &@@@@@@@@@@@@@@   \n"
      "                @@ @@ ,,,,  ,,,@@,,  ,,@ ,%@@@@@@@@@@@@@@@@@@, \n"
      "                @ ,,@@@ ,@@@@ @@@@@@@ @@@@@@@@@@@@@@@@@ @@@@@@ \n"
      "                  @ @@@@@@@@@@@@@ @@@@@@@@@@@ @ @@@@@@ @@@@@@@@\n"
      "                  @@@@@@@@@      @             @( @@@@@ @.@@@@@\n"
      "                    % @@@@@@@@ @# .......       @@@#@@@@@@ @@@@\n"
      "                       @ .        ..  .......... @@@@@@@ @@@@@ \n"
      "                        @. ..  .   ...........     @@@@@@@@@@@ \n"
      "                         @ ....  ,,,,,...... @@@    @ @@@@@@   \n"
      "                          @&    ,,,,,,...@@@@@@@@@# @@@@@@@@   \n"
      "                          @@@@@@@@@@@@@@@@@@@@@,,,@@@ @@@@     \n"
      "                         @@@@@@@@@@@@@@@@#,,, @@  @* @@@       \n"
      "                       @  ,,@@, @ ,,,,, @@ @@@ @@@@ @          \n"
      "                         @@@@@@@@@  (@@@@@@@@@@@               \n"));
}