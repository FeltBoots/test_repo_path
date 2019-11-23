#define _CRT_SECURE_NO_WARNINGS
using namespace std;
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <functional>
#include <map>

int dp[1000][200][200][2];

int strategy_havaut(int a, int b)
{
	bool block = false;
	int ans = 0;
	while (a > 1 && b > 0)
	{
		ans++;
		a--;
		block = false;
		if (a > 0)
		{
			a--;
			b++;
			block = true;
		}
		else
		{
			if (b > 0)
			{
				b--;
				block = false;
			}
		}
	}
	int go = false;
	while (a > 0 || b > 0)
	{
		if (a == 0)
		{
			if (!block && b > 0)
			{
				a = 1;
				b--;
			}
			block = false;
			if (b != 0)
				b--;
		}
		else
		{
			ans++;
			a--;
			if (b != 0)
			{
				b--;
				block = false;
			}
			else
			{
				if (!block && a > 0)
				{
					b++;
					a--;
					block = true;
				}
				else
					block = false;
			}
		}
	}
	return ans;
}

int havaet_afk(int a, int b, bool fl = false)
{
	int ans = 0;
	if (fl && b % 2 == 1 && a > 0)
	{
		ans++;
		a--;
		b--;
	}

	bool block = false;
	
	while (b > 0)
	{
		a++;
		b--;
		if (b > 0)
			b--;
	}
	while (a > 0)
	{
		a--;
		ans++;
		if (b != 2 && a > 0)
		{
			a--;
			b++;
		}
		else
		if (b == 2)
		{
			b--;//Съел
			a++;//Забрал
			b--;//Отдал
			a--;//Съел
			ans++;
			if (a > 0)
			{
				a--;//отдал
				b++;//забрал;
			}
		}
	}
	return ans;
}

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	for (int a = 0; a <= 50; a++)
		for (int b = 0; b <= 50; b++)
		{
			dp[0][a][b][0] = 1;
			for (int i = 0; i < 1000; i++)
				for (int j = 0; j <= a + b; j++)
					for (int q = 0; q <= a + b; q++)
						for (int can = 0; can <= 1; can++)
						{
							if (i % 2 == 0)
							{
								if (dp[i][j][q][can] != 0)
								{
									if (j > 0)
										dp[i + 1][j - 1][q][0] = max(dp[i + 1][j - 1][q][0], dp[i][j][q][can] + 1);
									if (can == 1 && j == 0)
										dp[i + 1][j][q][0] = max(dp[i + 1][j][q][0], dp[i][j][q][can]);
									if (q != 0 && can == 0)
										dp[i + 1][j + 1][q - 1][1] = max(dp[i + 1][j + 1][q - 1][1], dp[i][j][q][can]);
								}
							}
							else
							{
								if (dp[i][j][q][can] != 0)
								{
									if (q > 0)
										dp[i + 1][j][q - 1][0] = max(dp[i + 1][j][q - 1][0], dp[i][j][q][can]);
									if (can == 1 && q == 0)
										dp[i + 1][j][q][0] = max(dp[i + 1][j][q][0], dp[i][j][q][can]);
									if (j != 0 && can == 0)
										dp[i + 1][j - 1][q + 1][1] = max(dp[i + 1][j - 1][q + 1][1], dp[i][j][q][can]);
								}
							}
						}
			int ans = 0;
			for (int i = 0; i < 1000; i++)
				for (int j = 0; j <= a + b; j++)
					for (int q = 0; q <= a + b; q++)
						for (int can = 0; can <= 1; can++)
						{
							ans = max(dp[i][j][q][can], ans);
							dp[i][j][q][can] = 0;
						}
			//cout << "###################" << endl;
			
			if (havaet_afk(a, b) < ans - 1)
			{
				cout << a << ' ' << b << endl;
				cout << ans - 1 << " vs " << havaet_afk(a, b) << " vs " << havaet_afk(a, b, true) << endl;
			}
			cout << "###################" << endl;
		}

}