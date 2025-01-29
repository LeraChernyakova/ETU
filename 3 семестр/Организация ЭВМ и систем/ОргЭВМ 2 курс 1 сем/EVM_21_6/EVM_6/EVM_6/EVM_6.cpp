#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include"RANDOM.H"


extern "C"
{
	void MAS_FUNC(int n, int ni, int xmi, int xma, int* nums, int* lB, int* res);
}

//using namespace std;
int main()
{
	dnk_randomize();
	dnk_randomize();
	int n = 0;
	int ni = 0;
	int xMin = 0;
	int xMax = 0;

	std::cout << "Enter amount of elements:\n";
	std::cin >> n;
	if (n > 16 * 1024) {
		std::cout << "amount of elements shold be no bigger than " << 16 * 1024; exit(1);
	}
	std::cout << "Enter amount of intervals:\n";
	std::cin >> ni;
	if (ni > 24) {
		std::cout << "amount of intervals shold be no bigger than " << 24; exit(1);
	}
	std::cout << "Enter lower border:\n";
	std::cin >> xMin;
	std::cout << "Enter upper border:\n";
	std::cin >> xMax;

	int *nums = new int[n];
	int *lB = new int[ni];
	int *res = new int[ni];
	for (int i = 0; i < ni; i++)res[i] = 0;

	std::cout << "Enter "<<ni-1<<" left borders:\n";
	for (int i = 0; i < ni-1; i++) {
		//check for inside borders
		std::cin >> lB[i];
		if (lB[i] > xMax || lB[i] < xMin) {
			std::cout << "Left borders shoult be within min-max interval"; exit(1);
		}
	}
	/*
	lB[0] = xMin;
	lB[ni] = xMax;
	*/
	
	lB[ni - 1] = xMax;
	for (int i = 0; i < n; i++) {
		nums[i] = round(dnk_normal((double)((xMin+xMax)/2), (double)((xMax-xMin)/2)));
		// std::cout << nums[i] << " ";
		if (nums[i] > xMax)nums[i] = xMax-1;
		if (nums[i] < xMin)nums[i] = xMin+1;
	}
	std::cout << std::endl;


	MAS_FUNC(n, ni, xMin, xMax,nums, lB,res);
	
	printf("NInt\tlGrInt\tNum\n");
	for (int i = 0; i < ni; i++) {
		printf("%d\t%d\t%d\n", i, i ? lB[i - 1] : xMin, res[i]);
	}
	/*
	for (int i = 0; i < n; i++) {
		std::cout << nums[i] << " ";
	}
	std::cout << std::endl;

	for (int i = 0; i < ni; i++) {
		std::cout << res[i] << " ";
	}
	std::cout << std::endl;
	*/
	
	
	
	
}

extern "C"
int mul2(int a) {
	return a * 2;
}

extern "C"
int cmpF(float d) {
	return d > 0 ? 1 : d == 0 ? 0 : -1;
}

extern "C"
void* readName()
{
	char* name = (char*)calloc(1, 255);
	scanf("%s", name);
	while (getchar() != '\n');
	return name;
}