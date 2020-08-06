# Gypsophino

## Introduction

2D Music game.

## Compile

### Linux

```bash
git clone https://github.com/Gypsophino-dev/Gypsophino.git
cd src && mkdir -p build
cd build
cmake ../ && make
ln -s ../song_maps song_maps
ln -s ../res res
./Gypsophino
```

## Basic Usage

| Key | Effect |
|-----|--------|
| `Esc` | quit |
| `p` | pause/replay |
| `d`/`f`/`j`/`k` | hit falling note |
