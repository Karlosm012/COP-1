// Karlos Morales Ramos, ka649665
// COP 3505, Fall 2022
// RunLikeHell Project

import java.util.*;
import java.io.*;
import java.util.Arrays;
import java.lang.Math;

public class RunLikeHell
{
	public static int maxGain(int[] blocks)
	{
		// create a new array to hold the values we need and to not
		// compute the same values over and over again
		int[] knowledgePoints = new int[3];

		// we take the first block, the second for if we skip the first block
		// and the sum of the first block and the third block so we dont need to
		// add them up again in the future
		knowledgePoints[0] = blocks[0];
		knowledgePoints[1] = blocks[1];
		knowledgePoints[2] = blocks[0] + blocks[2];

		// do a for loop starting at the block index we havent used before
		for (int i = 3; i < blocks.length; i++)
		{
			// FIRST CASE COMMENT:
			// if what's on our first block plus our new block is greater than what
			// we calculated on blocks 0 + 2, OR, if what's on our second block plus
			// our new block is greater than what we calculated on block 0 + 2
			if (knowledgePoints[i%3] + blocks[i] > knowledgePoints[(i-1)%3] || 
				knowledgePoints[(i-2)%3] + blocks[i] > knowledgePoints[(i-1)%3])

				// FIRST CASE COMMENT:
				// we get the max number out of block 0 and block 1 and add that with our
				// new block and we place the new value on block 0
				knowledgePoints[i%3] = Math.max(knowledgePoints[i%3], knowledgePoints[(i-2)%3]) 
				+ blocks[i];

			// else we skip the block and add normally
			else 
				knowledgePoints[i%3] = knowledgePoints[(i-1)%3];
		}

		// return whatever there is on the last block we used
		return knowledgePoints[(blocks.length - 1) % 3];
	}

	public static double difficultyRating()
	{
		return 5.0;
	}

	public static double hoursSpent()
	{
		return 17.0;
	}
}
