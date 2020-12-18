#include "pch.h"
#include <iostream>
#include <windows.h>
#include <ctime>
#include <cstdlib>
using namespace std;

int mas [10];

int thread01()
{
	srand(time(NULL));
	HANDLE hMutex01 = OpenMutex(SYNCHRONIZE, FALSE, "MyMutex");
	if (hMutex01 == NULL)
		cout << "Open mutex01 failed" << GetLastError() << endl;
	WaitForSingleObject(hMutex01, INFINITE);
	for (int i = 0; i < 10; i++)
	{
		mas[i] = rand();
		cout << mas[i] << " ";
	};
	cout << endl;
	ReleaseMutex(hMutex01);
	CloseHandle(hMutex01);
	return 0;
}

int thread02()
{
	HANDLE hMutex02 = OpenMutex(SYNCHRONIZE, FALSE, "MyMutex");
	Sleep(1);
	if (hMutex02 == NULL)
		cout << "Open mutex02 failed" << GetLastError() << endl;
	WaitForSingleObject(hMutex02, INFINITE);
	for (int i = 0; i < 10; i++)
	{
		if (mas[i] % 2 == 0)
		{
			mas[i] = 0;
		}
		cout << mas[i] << " ";
	}
	cout << endl;
	ReleaseMutex(hMutex02);
	CloseHandle(hMutex02);
	return 0;
}

int main()
{
	HANDLE hMutex = CreateMutex(NULL, FALSE, "MyMutex");
	if (hMutex == NULL)
		cout << "Create mutex failed" << GetLastError() << endl;

	HANDLE hTh01 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread01, NULL, 0, NULL);
	if (hTh01 == NULL) return GetLastError();

	HANDLE hTh02 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread02, NULL, 0, NULL);
	if (hTh02 == NULL)return GetLastError();

	cin.get();

	CloseHandle(hMutex);

	CloseHandle(hTh01);
	CloseHandle(hTh02);
	system("pause");
	return 0;
}

