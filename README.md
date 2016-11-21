How it (probably) will work:

1. Start minesweeper (AKA "Mines")
2. Start minesweeper-sweeper (AKA "Solver")
3. The solver should be able to interpret the GUI of Mines and represent it internally in whatever way is fitting for the solver 
 - 1. "Print" window and pattern-match (or get handles to controls/forms/whattheyarecalled and access that way)
 - 2. Find the grid
 - 3. Find the individual tiles
 - 4. Interpret different tiles (determine if number, flag, empty (clicked or not clicked))
4. Determine next move and send input to Mines.
5. Repeat from 3 until solved (again, detect through GUI).
6. Start new round and solve again.

Should support analytics (time per round, rounds played, successrate etc.).
