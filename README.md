This is the REPO referring to our Artifitial Intelligence project:

Given the Professor's base code, we will write our own Player code.
The Player will take in a Flood-It game board, and based on it,
the Player will try to find (under 10 minutes) the best possible
set of color choices to win the game and then return the sequence found.

First, compile the code by typing:
$ make

Second, run the code with the information about the x and y axis and the number of colours
$ ./main < FILE.TXT

And the FILE.TXT should have the following model (all the itens should be integers):

[xaxis] [yaxis] [colors]
[posision 1,1] ...............
..............................
................[position xaxis, yaxis]


/----------ABOUT THE TESTS --------------/

We've tested the efficiency of our algorithm with the professors implementation to generate boards.

Those tests can be found inside the file "customTests".
And it is possible to check if our sequence is actually correct by typing ./exemploProfessor X Y Z W
Where X Y Z W correspond to the numbers found below next to each test. 

Used as input to the professor's implementation were the sequences:

**Test 1- 4 4 3 2**

Our code gave the sequence:
```
3
3 2 1
```
This was a correct answer and it was the minimum answer. It is easy to see it by checking.

**Test 2- 4 4 2 2**

Our code gave the sequence:
```
3
2 1
```
This was a correct answer and it was the minimum answer. It is easy to see it by checking.

**Test 3- 5 5 4 2**

Our code gave the sequence:
```
6
4 2 4 1 3 2
```
It is a correct sequence, and it is a minimum answer.

**Test 4- 50 50 4 2**

Our code gave the sequence:
```
51
1 3 1 2 4 1 2 3 4 2 3 1 3 4 1 2 1 3 4 3 2 1 4 2 3 4 2 4 1 3 2 4 1 2 3 1 4 2 1 3 4 1 2 4 1 4 2 3 1 4 2
```
It is a correct sequence.


**Test 5- 50 50 6 2**

First heuristic, our code gave the correct sequence:
```
80
2 1 3 4 2 6 5 2 1 3 5 4 1 3 2 4 5 2 5 4 2 3 5 1 2 6 4 1 6 3 2 5 4 6 1 2 6 4 2 5 6 2 4 1 2 3 6 4 1 3 5 2 6 3 1 2 3 5 4 2 1 5 6 4 1 5 3 5 4 1 6 2 3 4 5 1 2 6 3 4
```
Second heuristic, our code gave the sequence:
```
88
2 1 3 6 2 4 1 2 4 5 4 6 1 4 3 2 1 4 5 3 6 2 5 4 6 2 5 3 1 4 6 3 2 4 5 1 3 6 4 2 5 1 6 4 2 1 3 6 4 2 5 1 3 2 6 4 1 3 5 4 2 6 3 5 1 4 6 2 5 3 1 4 5 6 2 1 4 3 2 1 5 6 4 3 5 2 1 6
```

**Test 6- 100 100 6 2**

First heuristic: our code gave the sequence(not tested):
```
172
5 2 1 5 3 2 4 1 4 2 3 1 4 5 3 6 4 1 2 4 6 2 5 1 3 6 4 5 6 1 4 3 2 5 6 4 2 1 3 6 5 3 4 2 1 5 3 4 2 1 5 4 6 1 3 5 2 4 1 6 2 4 5 3 4 2 3 5 4 1 2 6 5 3 1 4 5 2 1 4 3 6 5 2 4 1 3 2 4 6 2 1 3 5 6 4 3 1 5 6 4 2 1 3 5 2 6 4 1 3 2 4 5 1 3 6 4 5 1 3 6 2 5 1 4 6 3 1 2 6 5 3 2 4 1 5 6 4 3 6 1 3 6 5 4 1 6 5 3 2 6 5 2 1 3 1 6 3 4 2 3 1 6 5 2 3 6 4 1 5 3 2 
```

Second heuristic, our code gave the sequence:
```
186
5 2 1 5 3 2 4 1 4 2 3 1 4 5 6 4 1 2 3 6 4 2 5 1 3 6 2 4 5 1 3 4 6 5 2 4 1 3 6 2 5 1 3 4 2 6 1 5 4 3 2 5 6 1 4 3 2 5 6 1 4 3 2 5 4 1 6 2 5 3 1 4 2 6 5 3 1 2 4 6 3 5 4 1 2 6 5 3 2 4 1 5 6 3 2 4 5 1 3 6 2 4 1 5 6 2 3 1 4 2 5 6 1 3 4 5 6 2 1 4 5 3 6 1 4 2 3 5 6 1 2 4 3 1 6 5 2 4 1 3 2 5 6 4 1 3 6 5 2 4 1 3 6 5 4 2 6 1 5 4 3 6 2 1 3 5 1 4 2 3 1 5 3 4 6 2 5 3 1 6 4 2 1 3 5 6
```

**Test 7- 5 5 4 3**

Our code gave the sequence:
```
6
1 2 1 3 4 2
```
It is a correc sequence.

**Test 14x14-1**

Our code gave the sequence:
```
20
2 1 2 3 5 2 1 5 4 6 3 4 6 2 6 3 1 5 4 2
```
It is a correct sequence, but the minimum sequence is:
```
19
4 1 4 5 2 1 5 1 2 4 6 2 3 6 3 2 4 5 1
```
