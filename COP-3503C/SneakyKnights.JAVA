// Karlos Morales Ramos, ka649665
// COP 3503C, Fall 2022
// Sneaky Knights project

import java.util.*;
import java.awt.*;

public class SneakyKnights
{
	// creates the board with the information from coordinateStrings
	public static boolean allTheKnightsAreSafe(ArrayList<String> coordinateStrings, int boardSize)
	{
		// gets the size of the array
		int arrSize = coordinateStrings.size();

		// the difference between the columns
		int colSub = 0;

		// initialize board
		HashSet<Point> boardState;

		// if we have the max val, we have to double it
		if (boardSize == Integer.MAX_VALUE)
		{
			// max board size is doubled if at max value
			int maxBoardSize = boardSize * boardSize;

			// makes the board using a hashset with x and y. Rows and columns
			boardState = new HashSet<>(maxBoardSize);
		}

		// if we do not have max val, we do not need to double it
		else 
		{
			boardState = new HashSet<>(boardSize);
		}
		

		// create a hashmap so that it is quicker to find the values for our
		// alpha characters, o(1) when we use get and put.
		HashMap<Character, Integer> alphaVal = new HashMap<>();
		alphaVal.put('a', 1);
		alphaVal.put('b', 2);
		alphaVal.put('c', 3);
		alphaVal.put('d', 4);
		alphaVal.put('e', 5);
		alphaVal.put('f', 6);
		alphaVal.put('g', 7);
		alphaVal.put('h', 8);
		alphaVal.put('i', 9);
		alphaVal.put('j', 10);
		alphaVal.put('k', 11);
		alphaVal.put('l', 12);
		alphaVal.put('m', 13);
		alphaVal.put('n', 14);
		alphaVal.put('o', 15);
		alphaVal.put('p', 16);
		alphaVal.put('q', 17);
		alphaVal.put('r', 18);
		alphaVal.put('s', 19);
		alphaVal.put('t', 20);
		alphaVal.put('u', 21);
		alphaVal.put('v', 22);
		alphaVal.put('w', 23);
		alphaVal.put('x', 24);
		alphaVal.put('y', 25);
		alphaVal.put('z', 26);

		// n loop, loop through all the the coordinates in arraylist
		for (int n = 0; n < arrSize; n++)
		{
			String coords = coordinateStrings.get(n);
			int strLen = coords.length();

			// variables for digits
			int numRes = 0;
			int numTrack = 1;
			boolean numFlag = true;

			// variables for letters
			int alphaRes = 0;
			int alphaTrack = 1;
			boolean alphaFlag = true;

			// We start at the end of the string so we can get the letters
			// without having problems of using more than one for loop.
			for (int k = strLen - 1; k >= 0; k--)
			{
				// If the character is a digit, enter.
				if (Character.isDigit(coords.charAt(k)))
				{

					// If it's the first number we are seeing, we just add it.
					if (numFlag)
					{
						numRes += coords.charAt(k) - '0';
						numFlag = false;
					}

					// If it's a number after the first one, we multiply it by a power of 10
					// and then add it with the numbers before.
					else 
					{
						numRes = ((10 * numTrack) * (coords.charAt(k) - '0') + numRes);

						numTrack *= 10;
					}
				}

				// If the character is a letter, enter.
				else if (Character.isLetter(coords.charAt(k)))
				{

					// if it's the first letter, we just add it.
					if (alphaFlag)
					{
						alphaRes += alphaVal.get(coords.charAt(k));
						alphaFlag = false;
					}

					// if it's a letter after the first one, we multiply it by a power of 26
					// and then add it with the result before.
					else 
					{
						alphaRes = ((26 * alphaTrack) * (alphaVal.get(coords.charAt(k))) + alphaRes);

						alphaTrack *= 26;
					}
				}
			}

			int knightRow = numRes;
			int knightCol = alphaRes;

			// upper part of the knight. We start at plus 1 because the row that 
			// the knight is in doesnt have any places to attack
			for (int currRow = knightRow + 1; currRow <= knightRow + 2; currRow++)
			{
				colSub = ((currRow - knightRow) % 2) + 1;

				if (boardState.contains(new Point(currRow, knightCol - colSub)) || 
					boardState.contains(new Point(currRow, knightCol + colSub)))
					return false;
			}

			// bottom part of the knight. We end before the row the knight is 
			// currently on
			for (int currRow = knightRow - 2; currRow < knightRow; currRow++)
			{
				colSub = ((knightRow - currRow) % 2) + 1;

				if (boardState.contains(new Point(currRow, knightCol - colSub)) ||
					boardState.contains(new Point(currRow, knightCol + colSub)))
					return false;
			}

			// adds knight to the board state
			boardState.add(new Point(numRes, alphaRes));
		}

		return true;
	}

	public static double difficultyRating()
	{
		return 4.0;
	}

	public static double hoursSpent()
	{
		return 8.0;
	}
}
