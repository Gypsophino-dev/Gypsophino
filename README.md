# **Gypsophino**

## Table of Contents

- [About the Project](#about-the-project)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Compilation](#compilation)
    - [Linux](#linux)
    - [Windows/MacOs](#windowsmacos)
- [Usage](#usage)
- [Contributing](#Contributing)
- [License](#license)
- [Contact](#contact)
- [Acknowledgements](#acknowledgments)

## About the project

Gypsophino is a music game that can be played on the computer.

We want to design our own music game because all members in our group love music.
And we’d like to have some new with music games in general, such as pixel blocks
with a major tone and a new storyline.

## Getting Started

Currently no package manager support. Please clone the source code and compile it
yourself. There is no need to install the game somewhere, just run it in building
directory.

### Prerequisites

`raylib`, `cmake`, and a sane `C++17` compiler.

### Compile

#### Linux

```bash
# Clone the repo.
git clone https://github.com/Gypsophino-dev/Gypsophino.git

# Make it.
cd src && mkdir -p build
cd build
cmake ../ && make

# Link necessary resources into build dir to make game run.
ln -s ../song_maps song_maps
ln -s ../res res
```

#### Windows/MacOS

I don't know. If you would like to port, just port it.

## Usage

```bash
# In src/build
./Gypsophino
```

### Keybindings

| Key | Effect |
| -------- | -------- |
| `Esc` | abort |
| `p`    | pause\replay |
| `d` / `f` / `j` / `k` | hit falling note |

## Contributing

Just do it normally. Fork, do something, and open a PR.

## License

Do What the Fuck You Want to Public License.
See [LICENSE](https://github.com/Gypsophino-dev/Gypsophino/blob/master/LICENSE)
for more information.

## Contact

tonyfettes - \<feihaoxiang2014@gmail.com\>

Dolores - \<Dolores1049@sjtu.edu.cn\>

Sherry - \<sherry-wang@sjtu.edu.cn\>

## Acknowlegements

[raylib](https://www.raylib.com)
