This is the REPO referring to our Artifitial Intelligence project:

Given the Professor's base code, we will write our own Player code.
The Player will take in a Flood-It game board, and based on it, 
the Player will try to find (under 10 minutes) the best possible 
set of color choices to win the game and return it.

First, compile the code by typing:
make

Second, run the code with the information about the x and y axis and the number of colours
./main < FILE.TXT

And the FILE.TXT should have the following model (all the itens should be integers):
[xaxis] [yaxis] [colors]
[posision 1,1] ...............
..............................
................[position xaxis, yaxis]


/----------ABOUT THE TESTS --------------/

We've tested the efficiency of our algorithm with the professors implementation to genrate boards.
Used as input to the professor's implementation were the sequences:

Test 1- 4 4 3 2
Our code gave the sequence:
3
3 2 1
This was a correct answer and it was the minimum answer. It is easy to see it by checking.

Test 2- 4 4 2 2
Our code gave the sequence:
3
2 1 2
This was the wrong answer. The correct answer would be only "2 1". The game can be won in 2 steps.

Test 3- 5 5 4 2
Our code gave the sequence:
6
4 2 4 1 3 2
It is a correct sequence, and it is a minimum answer.

Test 4- 50 50 4 2
Our code gave the sequence:
60
1 3 4 3 2 1 2 3 4 2 3 4 2 1 4 3 2 4 3 2 1 4 2 3 1 2 3 4 1 2 4 3 2 1 4 2 3 4 1 2 3 4 1 3 2 4 1 3 4 1 2 3 4..3 1 2 4! 3 1 2
Where it was marked with "..", if after the 4 the algorithm had given the subsequence "1 2 4" the game would be over.
So this sequence is wrong and it is not minimum. At that point, our algorithm is not recognizing that the number "3" in the table is non-existant, it should not have played "3" after the ".."
After the mark "!" the game would be over, our algorithm did not recognize the game was over and played another "3 1 2"

--------------- NOT ANALYSED yet --------------
Test 5- 50 50 6 2
Our code gave the sequence:
93
2 1 3 6 2 4 1 2 4 5 4 6 4 3 1 4 5 3 6 2 3 4 1 6 3 2 5 4 6 2 1 6 3 4 2 1 5 6 3 4 2 5 6 4 1 2 4 6 3 5 1 3 2 6 1 4 5 3 2 6 4 5 1 3 6 4 2 5 1 3 2 6 4 5 1 2 4 1 5 3 6 1 2 4 5 2 3 6 5 1 4 3 6

Test 6- 100 100 6 2
Our code gave the sequence:
191
5 2 1 5 3 2 4 1 4 2 3 1 4 5 6 4 2 1 6 3 2 5 4 1 6 2 3 1 5 4 6 2 3 4 6 5 1 2 6 4 3 5 1 3 4 6 1 2 5 3 4 1 2 6 5 4 1 2 3 5 6 1 4 2 3 5 6 2 4 1 5 3 2 4 6 5 1 2 3 4 5 2 6 1 3 4 5 2 6 1 3 4 5 2 1 3 6 4 1 5 2 6 3 1 4 2 5 6 1 4 2 3 5 6 4 1 2 3 6 5 4 1 3 6 2 4 5 3 1 6 5 4 2 3 1 6 5 4 3 2 1 6 4 5 3 1 6 2 4 5 1 3 4 2 6 3 4 6 1 5 2 3 1 6 4 5 2 6 3 4 1 2 5 4 6 3 1 2 5 1 3 4 6 2 5 3 4 1 6 2 3
