#include<stdio.h>
#include<stdlib.h>
#define N 8 
int main()
{
	int i, j;
	char temp;
	char a[N];
	scanf("%s", a);//7
	for (i = 0, j = N - 1; i < j; i++, j--)
	{
		temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}
	printf("\n%s\n", a);

	char arr[N] = { 'a','b','c','d','e','f','g','h' };
	printf("%s\n", arr);
	char* ptr = arr;
	*(ptr + 8) = 'j';
	*(ptr + 9) = '\0';
	printf("%s\n", arr);
	char* array = (char*)malloc(sizeof(char)*2);
	printf("%s", array);
	return 0;
}