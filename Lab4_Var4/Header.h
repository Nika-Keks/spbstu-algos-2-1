#pragma once

int Min(int a, int b);

int*** createMap(int n);

void recur(int*** matrix, int* town, int idx, int n, int time,
	int* timeMin, int money, int FixMoney, int* been, int* way);