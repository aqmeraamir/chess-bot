# ♟ Chess Bot AI

Chess Bot AI is a terminal-based C++ chess engine built entirely from scratch using bitboards, move generation, and a simple Minimax algorithm. It’s a fully playable AI where a human can play against the engine in real time through the console.

This was one of my earlier projects from when I was around 14, exploring how AI and game logic come together in chess. The engine isn’t perfect — there are likely bugs and missing rules (like castling or en passant) — but the core logic is all hand-coded and demonstrates how a basic chess bot can function.

---

## Features

- ✅ Bitboard-based board representation
- ✅ Move generation for all piece types
- ✅ Minimax AI with a simple evaluation function
- ✅ Legal move filtering and check detection
- ✅ Command-line input with algebraic notation
- ❌ No GUI (console only)
- ❌ No castling, en passant, or promotion support (yet)

---

## Getting Started

### Build Instructions

1. Clone the repo:
   ```bash
   git clone https://github.com/aqmeraamir/chess-bot.git
   cd chess-bot
   ```

2. Compile the code 
    run the build file


3. Run the build
    ```
    bin/main
    ```

## How to Play
Once the board prints in the terminal, enter your moves using standard algebraic notation:

| Example | Meaning                 |
| ------- | ----------------------- |
| `e2e4`  | Move pawn from e2 to e4 |
| `Nf3`   | Move knight to f3       |
| `q`     | Quit the game           |

The AI will play as Black and make its move after yours.

### Sample Output