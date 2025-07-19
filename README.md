# ♟ Chess Bot AI

Chess Bot AI is a terminal-based C++ chess engine built entirely from scratch using bitboards, move generation, and a simple Minimax algorithm. It’s a fully playable AI where a human can play against the engine in real time through the console.

I made this project during year 12, exploring how AI and game logic come together in chess. The engine isn’t perfect — there are likely bugs and missing rules (like castling or en passant) — but the core logic is all hand-coded and demonstrates how a basic chess bot can function.

---

## Features

- Bitboard-based board representation
- Move generation for all piece types
- Minimax AI with a simple evaluation function
- Legal move filtering and check detection
- Command-line input with standard chess algebraic notation
- ❌ No castling, en passant, or promotion support (yet)

---

## Setup

### Download executable
1. Download the latest executable file [chess-bot-mac](https://github.com/aqmeraamir/chess-bot/releases/download/1.0/chess-bot-mac) (only works on mac/unix)

2. Run the executable 

OR

### Build from source (will work on windows)

1. Clone the repo:
   ```bash
   git clone https://github.com/aqmeraamir/chess-bot.git
   cd chess-bot
   ```

2. Build the project using make
    run the build file


3. Run the game
    ```
    .bin/ChessBot
    ```

## How to Play
Once the board prints in the terminal, enter your moves using standard algebraic notation:

| Example | Meaning                 |
| ------- | ----------------------- |
| `e2e4`  | Move pawn from e2 to e4 |
| `Nf3`   | Move knight to f3       |
| `q`     | Quit the game           |

The AI will play as Black and make its move after yours.

## Sample Output

CLI:

```
8 ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜
7 ♟ ♟ ♟ ♟ ♟ ♟ ♟ ♟
6
5
4
3
2 ♙ ♙ ♙ ♙ ♙ ♙ ♙ ♙
1 ♖ ♘ ♗ ♕ ♔ ♗ ♘ ♖
  a b c d e f g h
```

Enter your move (e.g., e2e4) or 'q' to quit:

## License
MIT — feel free to use or modify this for your own chess projects.