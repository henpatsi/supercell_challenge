# Supercell Coding Test

A vampire survivor style game made in SFML for the Hive x Supercell coding test 2024. The base code for the game was supplied, which was then fixed / updated by me in about 8 hours.

## Prerequisites

You must have [CMake](https://cmake.org/) version 3.22.1 or later installed to build this project.

If you are on Linux, make sure to install SFML's dependencies. For Debian-based distros:
```
sudo apt update
sudo apt install \
    libxrandr-dev \
    libxcursor-dev \
    libudev-dev \
    libfreetype-dev \
    libopenal-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev
```

## Building

Simply run `cmake -B build` and `cmake --build build`. This builds the executable in `./build/bin/`.

The exact location of the executable may differ depending on your system and compiler. Example locations are `./build/bin/survive` and `./build/bin/Debug/survive.exe`.

Alternatively, you can specify a generator suited for your toolchain.
- `cmake -B build -G"Unix Makefiles"`
- `cmake -B build -G"Visual Studio 17 2022"`
- `cmake -B build -GXcode`

Run `cmake -G` to list all available generators.

### Credits

Music - https://clement-panchout.itch.io/yet-another-free-music-pack
SFX - https://leohpaz.itch.io/minifantasy-dungeon-sfx-pack