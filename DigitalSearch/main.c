#include <windows.h> // Для работы с виндой
#include <tchar.h> // Для юникода
#include "DigitalSearch.h"

// Для красоты кнопок
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

// Идентификаторы кнопок
#define BTN_0 1000
#define BTN_1 1001

#define INPUT_BUFFER_SIZE 32 // Вместимость поля ввода данных
#define OUTPUT_BUFFER_SIZE 128 // Вместимость поля вывода данных

// Функция обработки событий окна
LRESULT
WndProc(
	HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam)
{
	static HWND edits[4]; // Объекты полей ввода/вывода
	static DIGITAL_TREE dt;

	switch (message)
	{
		// Разово при открытии окна
		case WM_CREATE:
		{
			dt = DTCreate();

			edits[0] = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER, 10, 10, 200, 30, hWnd, NULL, NULL, NULL);
			edits[1] = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER, 10, 50, 200, 30, hWnd, NULL, NULL, NULL);
			edits[2] = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_READONLY, 10, 90, 280, 20, hWnd, NULL, NULL, NULL);
			edits[3] = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_READONLY | ES_MULTILINE, 10, 120, 280, 100, hWnd, NULL, NULL, NULL);

			CreateWindow(_T("button"), _T("Insert"), WS_CHILD | WS_VISIBLE, 220, 10, 70, 30, hWnd, BTN_0, NULL, NULL);
			CreateWindow(_T("button"), _T("Find"), WS_CHILD | WS_VISIBLE, 220, 50, 70, 30, hWnd, BTN_1, NULL, NULL);

			break;
		}

		// При взаимодействии с окном
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case BTN_0:
				{
					TCHAR InputBuffer[INPUT_BUFFER_SIZE];

					// Получить данные с поля
					if (!GetWindowText(edits[0], InputBuffer, INPUT_BUFFER_SIZE))
					{
						// Вывести данные в поле
						SetWindowText(edits[2], _T("Empty line"));
						break;
					}

					BOOL uniq;
					BOOL status = DTInsert(dt, InputBuffer, lstrlen(InputBuffer), &uniq);
					if (status)
					{
						SetWindowText(edits[2], _T("System error"));
						break;
					}

					if (uniq)
					{
						TCHAR OutputBuffer[OUTPUT_BUFFER_SIZE];
						// Взять существующие данные поля
						GetWindowText(edits[3], OutputBuffer, OUTPUT_BUFFER_SIZE);

						// С конкатенировать с новыми данными
						_tcscat_s(OutputBuffer, OUTPUT_BUFFER_SIZE, InputBuffer);
						_tcscat_s(OutputBuffer, OUTPUT_BUFFER_SIZE, _T("\r\n"));

						SetWindowText(edits[3], OutputBuffer);
						SetWindowText(edits[0], NULL);
						SetWindowText(edits[2], _T("Success"));
					}
					else
						SetWindowText(edits[2], _T("Duplication"));

					break;
				}

				case BTN_1:
				{
					TCHAR InputBuffer[INPUT_BUFFER_SIZE];
					if (!GetWindowText(edits[1], InputBuffer, INPUT_BUFFER_SIZE))
					{
						SetWindowText(edits[2], _T("Empty line"));
						break;
					}
					
					BOOL res;
					BOOL status = DTFind(dt, InputBuffer, lstrlen(InputBuffer), &res);
					if (status)
					{
						SetWindowText(edits[2], _T("System error"));
						break;
					}

					SetWindowText(edits[2], res ? _T("Data found") : _T("Data not found"));

					break;
				}
			}
			break;
		}

		// При закрытии окна
		case WM_DESTROY:
		{
			PostQuitMessage(EXIT_SUCCESS);
			break;
		}

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return EXIT_SUCCESS;
}

// Точка входа
INT
_tWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ INT nCmdShow)
{
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = WndProc;
	wc.hbrBackground = COLOR_WINDOW + 1; // Цвет фона окна
	wc.lpszClassName = _T("MainWindow");

	if (!RegisterClass(&wc))
		return EXIT_FAILURE;

	HWND hWnd = CreateWindow(
		wc.lpszClassName,
		NULL, WS_OVERLAPPEDWINDOW,
		700, 300, 315, 270, // Размеры окна
		NULL, NULL, hInstance, NULL);

	if (!hWnd)
		return EXIT_FAILURE;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}