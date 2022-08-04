#include<iostream>

#include<fstream>

using namespace std;

int** makeptr(int row, int col)
{
	int** ptr = new int* [row];
	for (int i = 0; i < row; i++)
	{
		ptr[i] = new int[col];
	}
	return ptr;
}

int* grow(int* ptr, int size)
{
	int* temp = new int[size + 1];
	for (int i = 0; i < size; i++)
	{
		temp[i] = ptr[i];
	}
	delete[] ptr;
	return temp;
}

int** grow1(int** data, int size)
{
	int** temp = new int* [size + 1];
	for (int i = 0; i < size; i++)
	{
		temp[i] = data[i];

	}
	delete[] data;
	return temp;
}

int* extract_data(ifstream& fin, int size)
{
	int* ptr = nullptr;
	int num;
	for (int i = 0; i < size; i++)
	{

		ptr = grow(ptr, i);
		fin >> num;

		ptr[i] = num;

	}
	return ptr;

}

int** extract_data_two(ifstream& fin, int size1, int& size2)
{

	int** ptr = nullptr;
	while (!fin.eof())
	{
		ptr = grow1(ptr, size2);
		ptr[size2] = extract_data(fin, size1);
		size2++;
	}
	return ptr;
}

void print(int** data, int size, int size2)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size2; j++)
		{
			if (data[i][j + 1] < 0)
			{
				cout << data[i][j] << " ";
			}
			else if (data[i][j] < 10 && data[i][j]>0)
			{
				cout << "  " << data[i][j] << "  ";
			}

			else if (data[i][j] < 100 && data[i][j] >= 10)
			{
				cout << " " << data[i][j] << "  ";
			}
			else if (data[i][j] >= 100)
			{
				cout << data[i][j] << "  ";
			}
			else if (data[i][j] < 0)
			{
				cout << data[i][j] << "  ";
			}

		}
		cout << endl;
	}

}

void read_file(ifstream& fin)
{
	int num;
	while (fin >> num)
	{
		cout << num;
	}


}

int** rotation_270_degree(int** ptr, int row, int col)
{
	int i = row;
	int** temp = makeptr(row, col);
	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{
			temp[c][i - 1] = ptr[r][c];
		}
		i--;
	}


	return temp;
}
int** rotation_90_degree(int** ptr, int row, int col)
{
	int i = row;
	int** temp = makeptr(row, col);
	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{
			temp[c][r] = ptr[r][c];
		}

	}
	int r = row;
	for (int i = 0; i < row / 2; i++)
	{
		swap(temp[i], temp[i + r - 1]);
		r--;
	}
	return temp;
}
void swap(int* arr2)
{
	int temp = 0;
	temp = arr2[0];
	arr2[0] = arr2[1];
	arr2[1] = temp;
}

int** rotation_180_degree(int** ptr, int row, int col)
{

	int** temp = makeptr(row, col);
	for (int i = 0; i < row; i++)
	{
		int c1 = col;
		for (int j = 0; j < col; j++)
		{
			temp[i][j] = ptr[i][c1 - 1];
			c1--;
		}
	}
	for (int i = 0; i < row / 2; i++)
	{
		swap(temp[i], temp[i + 2]);
	}

	cout << endl;
	return temp;
}


void check(int** ptr, int** ptr2, int row, int col, int row2, int col2)
{
	int count = 0;
	int num = 0;
	num = ptr2[0][0];
	int r1, c1;
	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{

			if (num == ptr[r][c])
			{

				r1 = r;
				count = 0;
				if (r1 < row - row2 + 1)
				{

					for (int k = 0; k < row2; k++)
					{

						c1 = c;
						if (c1 < col - col2 + 1)
						{

							for (int j = 0; j < col2; j++)
							{

								if (ptr[r1][c1] == ptr2[k][j] || ptr[r1][c1] == ptr2[k][j] * -1)
								{

									count++;

								}
								c1++;
							}
						}
						r1++;
					}
					if (count == row2 * col2)
					{

						r1 = r;
						c1 = c;

						for (int i = 0; i < row2; i++)
						{
							for (int j = 0; j < col2; j++)
							{
								if (ptr[r1][c1] > 0)
								{
									ptr[r1][c1] = ptr[r1][c1] * -1;
									c1++;
								}

							}
							r1++;
							c1 = c;
						}
					}
				}

			}
		}

	}

}
void deleteptr(int** ptr, int row)
{
	for (int i = 0; i < row; i++)
	{
		delete[] ptr[i];
	}
	delete[] ptr;
}
int main()
{

	ifstream fin("t.txt");

	int col1;
	char data[50];
	fin >> col1;
	int row1 = 0;
	int** ptr = extract_data_two(fin, col1, row1);
	cout << "DISPLAY DATA : " << endl;
	print(ptr, row1, col1);
	ifstream fin2;
	while (true)
	{
		cout << "If YOU HAVE FILES TO CHECK SUB MATRIXS then click Y/y for yes and N/n for NO : ";

		char ch;

		cin >> ch;
		if (ch == 'y' || ch == 'Y')
		{
			while (true)
			{

				cout << "\nEnter file name : ";
				cin >> data;
				fin2.open(data);
				if (!fin2.is_open())
				{
					cout << "error file dont exsit please enter correct name : ";

				}
				else
				{
					break;
				}
			}



			int row2 = 0;
			int col2 = 0;
			fin2 >> col2;
			int** ptr2 = extract_data_two(fin2, col2, row2);
			cout << "\nSub matrix read ftom file : " << endl;

			print(ptr2, row2, col2);
			check(ptr, ptr2, row1, col1, row2, col2);

			cout << "\nAfter found sub matrixs : " << endl;
			print(ptr, row1, col1);
			int** ptr270 = rotation_270_degree(ptr2, row2, col2);

			cout << "\n270 Degree rotation : " << endl;
			print(ptr270, row2, col2);

			int** ptr180 = rotation_180_degree(ptr2, row2, col2);

			cout << "180 Degree rotation : " << endl;
			print(ptr180, row2, col2);

			int** ptr90 = rotation_90_degree(ptr2, row2, col2);

			cout << "\n90 Degree rotation : " << endl;
			print(ptr90, row2, col2);
			cout << endl;
			check(ptr, ptr90, row1, col1, row2, col2);
			check(ptr, ptr180, row1, col1, row2, col2);
			check(ptr, ptr270, row1, col1, row2, col2);
			cout << "\nAfter found sub matrixs with differnt rotation : " << endl;
			print(ptr, row1, col1);
			fin2.close();
			deleteptr(ptr2, row2);
			deleteptr(ptr270, row2);
			deleteptr(ptr90, row2);
			deleteptr(ptr180, row2);

		}
		else if (ch == 'n' || ch == 'N')
		{
			cout << "GOOD BYE ";
			break;
		}
		else
		{
			cout << "You enter wrong option : " << endl;
		}
	}
	deleteptr(ptr, row1);
	fin.close();
	system("pause");
	return 0;

}