#include "pch.h"
#include <iostream>
#include <windows.h>
#include <ctime>
#include <cstdlib>
using namespace std;
HANDLE hSemaphore;
int n;
int *mas = new int[n];

int thread01() 
{
	HANDLE Semaphore1 = OpenSemaphore(SYNCHRONIZE, FALSE, "MySemaphore");
	srand(time(NULL));
	for (int i = 0; i < n; i++)
	{
		mas[i] = rand() % 501;
		cout << mas[i] << " ";
		Sleep(100);
	}
	ReleaseSemaphore(hSemaphore, 1, NULL);
	cout << endl;
	CloseHandle(Semaphore1);
	return 0;
}

int thread02()
{
	Sleep(1000);
	HANDLE Semaphore2 = OpenSemaphore(SYNCHRONIZE, FALSE, "MySemaphore");
	int k = 0;
	WaitForSingleObject(hSemaphore, INFINITE);
	for (int i = 0; i < n; i++)
	{
		if ( mas[i] % 2 == 0 && mas[i] > 0)
		{
			k++;
		}
	}
	cout << "Chetnye and Neotricatelnyje: " << k << endl;
	CloseHandle(Semaphore2);
	return 0;
}



int main()
{
	cout << "Enter arrange number:";
	cin >> n;
	hSemaphore = CreateSemaphore(NULL, 1, n+1, "MySemaphore");
	if (hSemaphore == NULL)
		cout << "Create semaphore failed" << GetLastError() << endl;

	HANDLE hTh01 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread01, NULL, 0, NULL);
	if (hTh01 == NULL)
		return GetLastError();
	HANDLE hTh02 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread02, NULL, 0, NULL);
	if (hTh02 == NULL) return GetLastError();
	
	cin.get();
	
	CloseHandle(hSemaphore);

	CloseHandle(hTh01);
	CloseHandle(hTh02);
	return 0;
}


