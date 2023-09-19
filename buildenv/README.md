First build the cross compiler image with:
  docker build buildenv/gcc-cross-x86_64-elf -t gcc-cross-x86_64-elf
Then run:
  docker build . -t myos-buildenv
