#include <stdlib.h>
#include <iostream>

using namespace std;

void map_gen(int MAX, int H_INIT);

void smoother(int iterations, int map[x][x]);

int main() {
	map_gen(17, 500);
	for (int x = 0; x < 18; x++)
	{
		for(int y = 0; y < 18; y++) {
			cout << map[x][y] << " ";
		}
		
		cout << endl;
	}
}

void map_gen(int MAX, int H_INIT) { // note: MAX must = (2^n) + 1.

	int map[MAX][MAX]; //grid

	map[0][0] = map[0][MAX-1] = map[MAX-1][0] = map[MAX-1][MAX-1] = H_INIT;
	// ^^ setting corner heights ("seeding")

	double range = 250.0; //range for height offset (now 1/2 seed height)
	double randim; // random number (use rand() % range - ( rand() % range) )
	// ^^ randim is ostensibly superfluous, since you aren't using
	//    an object to set a range for the random number.

	for(int side_ln = MAX-1; side_ln >= 2; side_ln /= 2, range /= 2.0) {

		int half_sln = side_ln/2; // half of the side length

		//generates all square values;
		for(int x=0; x<(MAX-1); x += side_ln) {
			for(int y=0; y<(MAX-1); y += side_ln) {
				double avg = ( map[x][y] +
				map[x+side_ln][y] +
				map[x][y+side_ln] +
				map[x+side_ln][y+side_ln] )
				/ 4; // get the avg height of the 4 corners

				map[x+half_sln][y+half_sln] = avg + (rand() % (2*range) - range);
				// ^^ center value is the avg of the points, plus an offset.
			}
		}

		//generates diamond values;
		for(int x=0; x<(MAX); x += half_sln) {
			for(int y=(x+half_sln)%side_ln; y<(MAX); y += side_ln) {
				double avg = (
					map[(x-half_sln+(MAX-1)%(MAX-1)][y] + /* left o' c  */
					map[(x+half_sln)%(MAX-1)][y] +     /* right o' c */
					map[x][(y+half_sln)%(MAX-1)] +     /* below c    */
					map[x][(y-half_sln+(MAX-1)%(MAX-1)]   /* above c    */
					) / 4;

				map[x][y] = avg + (rand() % (2*range) - range);
				// ^^ set diamond center values
			}
		}
	}
}

void smoother(int iter, int how_smuve, int map[z][z]) {
// ^^ NOTE: z must = (2^n) + 1.

	MAX = z; // rec'd how_smuve: .5

	while(iter) {

		// left-to-right:
		for(x = 1; x < MAX; x++) {
			for(y = 0; y < MAX; y++) {
				map[x][y] = map[x-1][y] * (1-how_smuve) +
				map[x][y] * how_smuve;
			}
		}

		//right-to-left:
		for(x = MAX-2; x > -1; x--) {
			for(y = 0; y < MAX; y++) {
				map[x][y] = map[x+1][y] * (1-how_smuve) +
				map[x][y] * how_smuve;
			}
		}

		//bottom-to-top:
		for(x = 0; x < MAX; x++) {
			for(y = 1; y < MAX; y++) {
				map[x][y] = map[x][y-1] * (1-how_smuve) +
				map[x][y] * how_smuve;
			}
		}

		//top-to-bottom:
		for(x = 0; x < MAX; x++) {
			for(y = MAX; y < -1; y--) {
				map[x][y] = map[x][y+1] * (1-how_smuve) +
				map[x][y] * how_smuve;
			}
		}

		iter--;
	}
}
