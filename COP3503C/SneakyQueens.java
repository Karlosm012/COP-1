// Karlos Morales, KA649665
// COP 3503, Fall 2022
// Sneaky Queens project

import java.io.*;
import java.util.*;
import java.lang.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;

public class SneakyQueens
{
	// creates the board with the information gathered in coordinateStrings
	public static boolean allTheQueensAreSafe(ArrayList<String> coordinateStrings, int boardSize)
	{
		// creating the board state
		boolean[] column = new boolean[boardSize + 1];
		boolean[] row = new boolean[boardSize + 1];
		boolean[] leftDiag = new boolean[2 * boardSize + 1];
		boolean[] rightDiag = new boolean[2 * boardSize + 1];

		// getting the size of the array list
		int arrSize = coordinateStrings.size();

		int queenCol = 0;
		int queenRow = 0;

		// create a hashmap so that it is quicker to find the values for our
		// alpha characters, o(1) when we use get and put.
		HashMap <Character, Integer> alphaVal = new HashMap<>();
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

		// here we have the first for loop (n in pdf) where we loop through all
		// the coordinates in arraylist
		for(int n = 0; n < arrSize; n++)
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

			// I'm using var k just to visualize what I read on the pdf.
			// We start at the end of the string so we can get the letters
			// without having problems of using more than one for loop.
			for(int k = strLen - 1; k >= 0; k--)
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

			// set the row num and col num for the current queen
			queenRow = numRes;
			queenCol = alphaRes;

			// check if the queens are attacking in columns
			if (column[queenCol] == true)
				return false;
			column[queenCol] = true;

			// check if the queens are attacking in rows
			if (row[queenRow] == true)
				return false;
			row[queenRow] = true;

			// check if the queens are attacking in left diagonal.
			int posDiagVal = queenRow + queenCol;
			if (leftDiag[posDiagVal] == true)
				return false;
			leftDiag[posDiagVal] = true;

			// check if the queens are attacking in right diagonal
			int negDiagVal = queenRow - queenCol + boardSize - 1;
			if (rightDiag[negDiagVal] == true)
				return false;
			rightDiag[negDiagVal] = true;
		}

		return true;
	}

	// Difficulty ratings
	public static double difficultyRating()
	{
		return 5.0;
	}

	// hours spent on the program
	public static double hoursSpent()
	{
		return 16.0;
	}
}
