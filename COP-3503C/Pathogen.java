// Backtracking program

import java.io.*;
import java.util.*;

public class Pathogen
{
	// create a Hashset to hold the paths we can take to get to the exit
	private static HashSet<String> hashPaths = new HashSet<String>();

	// Used to toggle "animated" output on and off (for debugging purposes).
	private static boolean animationEnabled = false;

	// "Animation" frame rate (frames per second).
	private static double frameRate = 4.0;

	// Setters. Note that for testing purposes you can call enableAnimation()
	// from your backtracking method's wrapper method (i.e., the first line of
	// your public findPaths() method) if you want to override the fact that the
	// test cases are disabling animation. Just don't forget to remove that
	// method call before submitting!
	public static void enableAnimation() { Pathogen.animationEnabled = true; }
	public static void disableAnimation() { Pathogen.animationEnabled = false; }
	public static void setFrameRate(double fps) { Pathogen.frameRate = fps; }

	// Maze constants.
	private static final char WALL       = '#';
	private static final char PERSON     = '@';
	private static final char EXIT       = 'e';
	private static final char BREADCRUMB = '.';  // visited
	private static final char SPACE      = ' ';  // unvisited
	private static final char VIRUS      = '*';  // virus, cant touch

	// Takes a 2D char maze and returns true if it can find a path from the
	// starting position to the exit. Assumes the maze is well-formed according
	// to the restrictions above.
	public static HashSet<String> findPaths(char [][] maze)
	{
		int height = maze.length;
		int width = maze[0].length;

		// The visited array keeps track of visited positions. It also keeps
		// track of the exit, since the exit will be overwritten when the '@'
		// symbol covers it up in the maze[][] variable. Each cell contains one
		// of three values:
		//
		//   '.' -- visited
		//   ' ' -- unvisited
		//   'e' -- exit
		char [][] visited = new char[height][width];

		// we make a stringbuilder for the string that we are going to place inside
		// our hash set
		StringBuilder path = new StringBuilder();
		for (int i = 0; i < height; i++)
			Arrays.fill(visited[i], SPACE);

		// Find starting position (location of the '@' character).
		int startRow = -1;
		int startCol = -1;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (maze[i][j] == PERSON)
				{
					startRow = i;
					startCol = j;
				}
			}
		}

		// Let's goooooooooo!!
		return findPaths(maze, visited, startRow, startCol, height, width, path);
	}

	private static HashSet<String> findPaths(char [][] maze, char [][] visited,
	                                 int currentRow, int currentCol,
	                                 int height, int width, StringBuilder path)
	{
		// This conditional block prints the maze when a new move is made.
		if (Pathogen.animationEnabled)
		{
			printAndWait(maze, height, width, "Searching...", Pathogen.frameRate);
		}

		// Hoorayyyy!
		if (visited[currentRow][currentCol] == 'e')
		{
			if (Pathogen.animationEnabled)
			{
				char [] widgets = {'|', '/', '-', '\\', '|', '/', '-', '\\',
				                   '|', '/', '-', '\\', '|', '/', '-', '\\', '|'};

				for (int i = 0; i < widgets.length; i++)
				{
					maze[currentRow][currentCol] = widgets[i];
					printAndWait(maze, height, width, "Hooray!", 12.0);
				}

				maze[currentRow][currentCol] = PERSON;
				printAndWait(maze, height, width, "Hooray!", Pathogen.frameRate);
			}

			// trim the last space 
			String str = path.toString().trim();

			// add the string into the hash set
			hashPaths.add(str);
			return hashPaths;
		}

		// Moves: left, right, up, down
		int [][] moves = new int[][] {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

		for (int i = 0; i < moves.length; i++)
		{
			int newRow = currentRow + moves[i][0];
			int newCol = currentCol + moves[i][1];

			// Check move is in bounds, not a wall, and not marked as visited.
			if (!isLegalMove(maze, visited, newRow, newCol, height, width))
				continue;

			// Change state. Before moving the person forward in the maze, we
			// need to check whether we're overwriting the exit. If so, save the
			// exit in the visited[][] array so we can actually detect that
			// we've gotten there.
			//
			// NOTE: THIS IS OVERKILL. We could just track the exit position's
			// row and column in two int variables. However, this approach makes
			// it easier to extend our code in the event that we want to be able
			// to handle multiple exits per maze.

			if (maze[newRow][newCol] == EXIT)
				visited[newRow][newCol] = EXIT;

			maze[currentRow][currentCol] = BREADCRUMB;
			visited[currentRow][currentCol] = BREADCRUMB;
			maze[newRow][newCol] = PERSON;

			// it went up
			if (currentRow > newRow && currentCol == newCol)
			{
				String up = "u ";
				// store up
				path.append(up);
				
				// recursive call within this path
				findPaths(maze, visited, newRow, newCol, height, width, path);
			}

			// it went down
			else if (currentRow < newRow && currentCol == newCol)
			{
				String down = "d ";
				// store d
				path.append(down);

				// recursive call within this path
				findPaths(maze, visited, newRow, newCol, height, width, path);
			}

			// it went right
			else if (currentRow == newRow && currentCol < newCol)
			{
				String right = "r ";
				// store r
				path.append(right);

				// recursive call within this path
				findPaths(maze, visited, newRow, newCol, height, width, path);
			}

			// it went left
			else if (currentRow == newRow && currentCol > newCol)
			{
				String left = "l ";
				// store l
				path.append(left);

				// recursive call within this path
				findPaths(maze, visited, newRow, newCol, height, width, path);
			}

			// Undo state change. Note that if we return from the previous call,
			// we know visited[newRow][newCol] did not contain the exit, and
			// therefore already contains a breadcrumb, so I haven't updated
			// that here.
			maze[newRow][newCol] = BREADCRUMB;
			maze[currentRow][currentCol] = PERSON;

			// visited is going to be space so we can visit it again, if not then
			// the maze is going to end prematurely without going through all the possible
			// paths
			visited[currentRow][currentCol] = SPACE;

			// we want to delete the characters that we backtracked
			path.deleteCharAt(path.length() - 1);
			path.deleteCharAt(path.length() - 1);

			// This conditional block prints the maze when a move gets undone
			// (which is effectively another kind of move).
			if (Pathogen.animationEnabled)
			{
				printAndWait(maze, height, width, "Backtracking...", frameRate);
			}
		}

		return hashPaths;
	}

	// Returns true if moving to row and col is legal (i.e., we have not visited
	// that position before, and it's not a wall).
	private static boolean isLegalMove(char [][] maze, char [][] visited,
	                                   int row, int col, int height, int width)
	{
		// checks if we are out of bounds when there are no walls
		if (row < 0 || row >= height || col < 0 || col >= width)
			return false;

		if (maze[row][col] == WALL || visited[row][col] == BREADCRUMB || maze[row][col] == VIRUS)
				return false;

		return true;
	}

	// This effectively pauses the program for waitTimeInSeconds seconds.
	private static void wait(double waitTimeInSeconds)
	{
		long startTime = System.nanoTime();
		long endTime = startTime + (long)(waitTimeInSeconds * 1e9);

		while (System.nanoTime() < endTime)
			;
	}

	// Prints maze and waits. frameRate is given in frames per second.
	private static void printAndWait(char [][] maze, int height, int width,
	                                 String header, double frameRate)
	{
		if (header != null && !header.equals(""))
			System.out.println(header);

		if (height < 1 || width < 1)
			return;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				System.out.print(maze[i][j]);
			}

			System.out.println();
		}

		System.out.println();
		wait(1.0 / frameRate);
	}

	public static double difficultyRating()
	{
		return 3.5;
	}

	public static double hoursSpent()
	{
		return 7.30;
	}
}
