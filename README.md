# C-SWEEPER
*A Minesweeper inspired game. Developed as a project for programming classes.*

## About
C-Sweeper is a retro-inspired game you play right in your terminal, featuring simplistic keyboard input that brings back old-school vibes. With interactive fun and flexibility at its core, the game lets you:

- **Show off your scores** to your friends and challenge them to beat your best!
- **Play on custom boards** by modifying the game layout to suit your style.
- **Load custom boards and moves** directly from a text file, adding a personalized touch to your gameplay experience.

Dive in and enjoy the thrill of clearing the field without hitting a pointer!

## Project Structure
```
repository/
├── data/           # Scores, scoreboard for TOP5, tests
├── src/            # Source and header files
├── Makefile        # Build instructions
└── README.md       # Project documentation
```

## Building the Project
This project includes a `Makefile` for building and running the program.

Build the program using `make`:
   ```bash
   make
   ```
   The compiled executable will be located in the main directory as `c-sweeper`

## Usage
To launch the game manually, run:
```bash
./c-sweeper
```
or... run it with a custom file:
```bash
./c-sweeper -f <file_path>
```

## Authors
Developed by Jakub Pietrala & Bartosz Starzyński.
