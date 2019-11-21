#include "pch.h"
#include <iostream>
#include <vector>
using namespace std;

class Bingo {
public:
	void Push(vector<int> row) {
		matrix.push_back(row);
	}
	int GetEle(int i, int j) {
		return matrix[i][j];
	}
	int SetEle(int i, int j, int num) {
		matrix[i][j] = num;
	}
	void MarkIfNumberInBingo(int number) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (matrix[i][j] == number)
					matrix[i][j] = -1;
			}
		}
	}
	bool IsBingo() {
		for (int i = 0, cur = 0; i < 5; i++, cur = 0) {
			for (int j = 0; j < 5; j++) {
				if (matrix[j][i] == -1)
					cur++;
			}
			if (cur == 5)
				return true;
		}

		for (int i = 0, cur = 0; i < 5; i++, cur = 0) {
			for (int j = 0; j < 5; j++) {
				if (matrix[i][j] == -1)
					cur++;
			}
			if (cur == 5)
				return true;
		}

		for (int i = 0, cur = 0; i < 5; i++) {
			if (matrix[i][i] == -1)
				cur++;
			if (cur == 5)
				return true;
		}

		for (int i = 0, cur = 0; i < 5; i++) {
			if (matrix[i][4 - i] == -1)
				cur++;
			if (cur == 5)
				return true;
		}

		return false;
	}
private:
	vector<vector<int>> matrix;
};

void Swap(vector<int>& row, int i, int j)
{
	int temp = row[i];
	row[i] = row[j];
	row[j] = temp;
}

void GetBingo(Bingo *bingo) 
{
	for (int i = 0; i < 5; i++) {
		vector<int> row;
		int rowNum = (i == 2) ? 4 : 5;
		for (int j = 0; j < rowNum; j++) {
			int num;
			cin >> num;
			row.push_back(num);
		}
		if (i == 2) {
			row.push_back(-1);
			Swap(row, 4, 3);
			Swap(row, 3, 2);
		}
		bingo->Push(row);
	}
}

int GetBingoOrder(Bingo* bingo, vector<int> numbers)
{
	for (int order = 0; order < numbers.size(); order++) {
		bingo->MarkIfNumberInBingo(numbers[order]);
		if (bingo->IsBingo())
			return order + 1;
	}
	return -1;
}

int main()
{
    int n = 0;
	vector<Bingo*> bingos;
	vector<vector<int>> numbers;
	cin >> n;
	for (int i = 0; i < n; i++) {
		Bingo *bingo = new Bingo();
		GetBingo(bingo);
		bingos.push_back(bingo);

		vector<int> eachNumbers;
		for (int i = 0; i < 75; i++) {
			int number = 0;
			cin >> number;
			eachNumbers.push_back(number);
		}
		numbers.push_back(eachNumbers);
	}

	for (int i = 0; i < n; i++) {
		cout << "BINGO after " << GetBingoOrder(bingos[i], numbers[i]) << " numbers announced" << endl;
	}
}
