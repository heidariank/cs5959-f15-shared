#include <stdio.h>
#include <stdlib.h>

// Question: Without adding the -lm flag to my makefile my program could not find the sqrt function
// even though i've included the math library, according to stack overflow there is a difference 
// between linking to the definitions of functions as apposed to just the definitions of those functions
// in the header file and although i am not using the sqrt function anymore my question still remains

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

typedef struct point 
{
	long x, y;
} POINT;


long long getDistanceSquared(POINT a, POINT b)
{
  // Don't take the square root so as to not lose precision
	long long val =((a.x - b.x)*(a.x - b.x)) + ((a.y - b.y)*(a.y - b.y));
	return val;
}

void printType(long long a, long long b, long long c)
{
	if(a == b && a == c)
	{
		printf("equilateral ");
	}
	else if(a != b && a != c && c != b)
	{
		printf("scalene ");
	}
	else
	{
		printf("isosceles ");
	}
}

void printAngle(long long longest, long long other, long long another)
{
	if((other + another) > longest)
	{
		printf("acute\n");
	}
	else if((other + another) == longest)
	{
		printf("right\n");
	}
	else
	{
		printf("obtuse\n");
	}

}

void printAngleType(long long a, long long b, long long c)
{
	// Find longest side
  long long max = MAX(a, b);
	max = MAX(max, c);

	if(max == a)
	{
		printAngle(a, b, c);
	}
	else if(max == b)
	{
		printAngle(b, a, c);
	}
	else
	{
		printAngle(c, b, a);
	}
}

void isTriangle(POINT a, POINT b, POINT c)
{
	// Check the slopes against each other
	long long val1 = (b.y - a.y)*(c.x - b.x);
	long long val2 = (b.x - a.x)*(c.y - b.y);

	if(val1 == val2)
	{
		printf("not a triangle\n");
		exit(0);
	}
	
}

int main (int argc, char** argv)
{
  // START INPUT VALIDATION
	if(argc != 7)
	{
		printf("error\n");
		exit(0);
	}

  int counter;
	long values[6];
	char *ptr;

	for(counter = 1; counter < argc; counter++)
	{
		long result = strtol(argv[counter], &ptr, 10);
	  
		// Check if we are not at the end of the input or if the input is
		// valid but exceeds the given range of -(2^30-1) - (2^30-1)
		if(*ptr != '\0' || (result > 1073741823 || result < -1073741823)) {
			printf("error\n");
			exit(0);
		}
		
		values[counter - 1] = result;
	}
	// END INPUT VALIDATION

	POINT a;
	POINT b;
	POINT c;

	a.x = values[0];
	a.y = values[1];
	b.x = values[2];
	b.y = values[3];
	c.x = values[4];
	c.y = values[5];

	// Determine if 'not a triangle'
	isTriangle(a, b, c);

  // Determine side lengths
	long long lengthA = getDistanceSquared(a, b);
	long long lengthB = getDistanceSquared(b, c);
	long long lengthC = getDistanceSquared(c, a);

  printType(lengthA, lengthB, lengthC);
  printAngleType(lengthA, lengthB, lengthC);

	return 0;
}
