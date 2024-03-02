# include<stdio.h>
# include<stdlib.h>


struct table{
	char conten[9][9];
	bool possible[9][9][9];
};

table* transfer(char* input) {
	table* out = (table*)calloc(sizeof(table), 1);if(out==NULL)return NULL;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (input[i * 9 + j] == 0) {
				out->conten[i][j] = 0;
				for (int k = 0; k < 9; k++)out->possible[i][j][k] = 1;
			}
			if (input[i * 9 + j] <= 9 && input[i * 9 + j] >= 1) {
				out->conten[i][j] = input[i * 9 + j];
				for (int k = 0; k < 9; k++)out->possible[i][j][k] = 0;
			}
		}
	}
	return out;
}

table* deletepossible_all_new(table* target) {
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			for (int k = 0; k < 9; k++)
				target->possible[i][j][k] = 1;
	for (int i = 0; i < 9; i++) 
		for (int j = 0; j < 9; j++) {
			if (target->conten[i][j] == 0)continue;
			for (int ii = 0; ii < 9; ii++)target->possible[ii][j][target->conten[i][j] - 1] = 0;
			for (int jj = 0; jj < 9; jj++)target->possible[i][jj][target->conten[i][j] - 1] = 0;
			for (int ii = (i / 3) * 3; ii < (i / 3) * 3 + 3; ii++) {
				if (ii == i)continue;
				for (int jj = (j / 3) * 3; jj < (j / 3) * 3 + 3; jj++) {
					if (jj == j)continue;
					target->possible[ii][jj][target->conten[i][j] - 1] = 0;
				}
			}
		}
	return target;
}

int find_crowdedest(table* target) {
	int max = 0;
	int place = -1;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (target->conten[i][j] != 0)continue;
			int tmp = 0;
			for (int ii = 0; ii < 9; ii++)if (target->conten[ii][j] != 0)tmp++;
			for (int jj = 0; jj < 9; jj++)if (target->conten[i][jj] != 0)tmp++;
			for (int ii = (i / 3) * 3; ii < (i / 3) * 3 + 3; ii++) {
				if (ii == i)continue;
				for (int jj = (j / 3) * 3; jj < (j / 3) * 3 + 3; jj++) {
					if (jj == j)continue;
					if (target->conten[ii][jj] != 0)tmp++;
				}
			}
			if (max < tmp) {
				max = tmp;
				place = 10 * i + j;
			}
		}
	}
	return place;
}

int judge_able(table* target, int i, int j, int val) {
	for (int ii = 0; ii < 9; ii++)if (target->conten[ii][j] == val)return 0;
	for (int jj = 0; jj < 9; jj++)if (target->conten[i][jj] == val)return 0;
	for (int ii = (i / 3) * 3; ii < (i / 3) * 3 + 3; ii++) {
		if (ii == i)continue;
		for (int jj = (j / 3) * 3; jj < (j / 3) * 3 + 3; jj++) {
			if (jj == j)continue;
			if (target->conten[ii][jj] == val)return 0;
		}
	}
	return 1;
}

table* add_content(table* target, int i, int j) {

	//printf("\n操作位置:%d,%d\n可以填入的有:", i, j);

	char value = -1;
	for (int k = 1; k <= 9; k++)
		if (target->possible[i][j][k - 1] && judge_able(target, i, j, k)) {
			value = k;

			//printf("%d,", value);

		}
	if (value == -1) return NULL;
	target->possible[i][j][value - 1] = 0;
	target->conten[i][j] = value;

	/*printf("\n当前情况:");
	for (int ii = 0; ii < 9; ii++) {
		printf("\n");
		for (int jj = 0; jj < 9; jj++)
			printf(" %d", target->conten[ii][jj]);
	}
	printf("\n");*/

	int place;
	if ((place = find_crowdedest(target)) == -1)return target;

	if (add_content(target, place / 10, place % 10))return target;
	else {
		target->conten[i][j] = 0;
		if (!add_content(target, i, j)) {
			target->possible[i][j][value - 1] = 1;
			return NULL;
		}
		else return target;
	}
}

char* solve(char* input) {
	table* target = transfer(input);
	deletepossible_all_new(target);
	int place = find_crowdedest(target);
	add_content(target, place / 10, place % 10);

	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			input[i * 9 + j] = target->conten[i][j];
	return input;
}


int main() {
	char input[81] = {	5,3,0,0,7,0,0,0,0,
						6,0,0,1,9,5,0,0,0,
						0,9,8,0,0,0,0,6,0,
						8,0,0,0,6,0,0,0,3,
						4,0,0,8,0,3,0,0,1,
						7,0,0,0,2,0,0,0,6,
						0,6,0,0,0,0,2,8,0,
						0,0,0,4,1,9,0,0,5,
						0,0,0,0,8,0,0,7,9 };
	char input1[81] = { 5,0,0,0,0,0,0,0,2,
						0,0,8,0,4,0,7,0,0,
						0,3,0,8,0,7,0,6,0,
						0,0,6,0,7,0,5,0,0,
						0,9,0,3,0,5,0,8,0,
						0,0,3,0,2,0,6,0,0,
						0,8,0,9,0,6,0,7,0,
						0,0,4,0,3,0,9,0,0,
						7,0,0,0,8,0,0,7,6 };

	solve(input1);

	printf("\n\n结果:\n");
	for (int i = 0; i < 9; i++) {
		printf("\n");
		for (int j = 0; j < 9; j++)
			printf(" %d", input1[i*9 + j]);
	}
}