#define _CRT_SECURE_NO_WARNINGS
using namespace std;
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>
#include <functional>
#include <set>
#include <sstream>
#include <queue>
#include <string>
#include <cstring>
#include <map>
#include <iomanip>
#include <random>
#include <cassert>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>


int dp[2][10000][10000][2];

string make_str_in(int i)
{
	stringstream ss;
	ss << i;
	string s;
	ss >> s;
	if (i < 10)
		s = "0" + s;
	s += ".in";
	return s;
}

string make_str_out(int i)
{
	stringstream ss;
	ss << i;
	string s;
	ss >> s;
	if (i < 10)
		s = "0" + s;
	s += ".out";
	return s;
}

int main(){


	for (int z = 5; z < 50; z++)
	{

		string s_in = make_str_in(z + 1);
		string s_out = make_str_out(z + 1);
		const char *file_name = s_in.c_str();
		ifstream cin(file_name);
		file_name = s_out.c_str();
		ofstream cout(file_name);

		int a, b;
		cin >> a >> b;

		dp[0][a][b][0] = 1;
		for (int i = 0; i <= 2 * a + 2 * b; i++)
		{

			for (int j = 0; j <= a + b; j++)
				for (int q = 0; q <= a + b; q++)
					for (int can = 0; can <= 1; can++)
					{
						if (i % 2 == 0)
						{
							if (dp[i % 2][j][q][can] != 0)
							{
								if (j > 0)
									dp[(i + 1) % 2][j - 1][q][0] = max(dp[(i + 1) % 2][j - 1][q][0], dp[(i) % 2][j][q][can] + 1);
								if (can == 1 && j == 0)
									dp[(i + 1) % 2][j][q][0] = max(dp[(i + 1) % 2][j][q][0], dp[i % 2][j][q][can]);
								if (q != 0 && can == 0)
									dp[(i + 1) % 2][j + 1][q - 1][1] = max(dp[(i + 1) % 2][j + 1][q - 1][1], dp[i % 2][j][q][can]);
							}
						}
						else
						{
							if (dp[i % 2][j][q][can] != 0)
							{
								if (q > 0)
									dp[(i + 1) % 2][j][q - 1][0] = max(dp[(i + 1) % 2][j][q - 1][0], dp[i % 2][j][q][can]);
								if (can == 1 && q == 0)
									dp[(i + 1) % 2][j][q][0] = max(dp[(i + 1) % 2][j][q][0], dp[i % 2][j][q][can]);
								if (j != 0 && can == 0)
									dp[(i + 1) % 2][j - 1][q + 1][1] = max(dp[(i + 1) % 2][j - 1][q + 1][1], dp[i % 2][j][q][can]);
							}
						}
					}
			for (int j = 0; j <= a + b; j++)
				for (int q = 0; q <= a + b; q++)
					for (int can = 0; can <= 1; can++)
						dp[i % 2][j][q][can] = 0;
		}
		int ans = 0;
		for (int i = 0; i <= 1; i++)
			for (int j = 0; j <= a + b; j++)
				for (int q = 0; q <= a + b; q++)
					for (int can = 0; can <= 1; can++)
					{
						ans = max(dp[i % 2][j][q][can], ans);
						dp[i % 2][j][q][can] = 0;
					}
		cout << ans - 1;
	}

}