#!/bin/bash
make
if [[ "$1" == "term" ]]; then
  bochs -f .bochsrc-term
else
  bochs -f .bochsrc-gui
fi
