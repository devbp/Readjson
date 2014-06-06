// Listview.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Listview.h"
#include "json.h"
#include <commctrl.h>
#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include<time.h>
#pragma warning(disable : 4996)

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_LISTVIEW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LISTVIEW));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LISTVIEW));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_LISTVIEW);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	case WM_CREATE:
	{return 0;
					  // HWND hwndTV = CreateATreeView(hWnd);
					  //InitTreeViewImageLists(hwndTV);
					  //InitTreeViewItems(hwndTV);
					  RECT rc;
					  rc.left = 200;
					  rc.top = 200;
					  rc.bottom = 600;
					  rc.right = 700;
					  			

					  Json::Value root;   // will contains the root value after parsing.
					  Json::Reader reader;

					  std::string json_example = "";

					  char file[] = "config.json";
					  std::string jsonfile = "config.json";
					  std::string str, strTotal;
					  std::ifstream in;
					  in.exceptions(std::ios::failbit | std::ios::badbit);
					  // Example of getting JSON from a local file
					
					  clock_t stime=clock();
					  try
					  {
						  in.open(file);

					  }
					  catch (std::ifstream::failure e)
					  {
						  std::cerr << "\n Exception opening file " << jsonfile << ": " << e.what();
						  return 0;
					  }

					  try
					  {

						  getline(in, str);
						  while (in) {
							 // getline(in, str, '\n')
							  getline(in, str);
							  strTotal += str;

						  }
					  }
					  catch (std::ifstream::failure e)
					  {
						  std::cerr << "\n Exception reading file " << jsonfile << ": " << e.what();

					  }
					  in.close();

					  bool parsingSuccessful = reader.parse(strTotal, root, true);
					  if (!parsingSuccessful)
					  {
						  // report to the user the failure and their locations in the document.
						  std::cout << "Failed to parse configuration\n";
						  //<< reader.getFormattedErrorMessages();
						  return -1;
					  }
					 
					  std::vector <std::string> *description = new std::vector<std::string>[9000];
					  std::vector<int>page;
					  // Get the value of the member of root named 'encoding', return 'UTF-8' if there is no
					  // such member.
					  std::string encoding = root.get("encoding", "UTF-8").asString();
					  // Get the value of the member of root named 'encoding', return a 'null' value if
					  // there is no such member.
					  const Json::Value plugins = root["description"];
					  for (int index = 0; index < plugins.size(); ++index)  // Iterates over the sequence elements.
					  {//  std::cout << plugins[index].asString();
						  description->push_back(plugins[index].asString());
						  page.push_back(index);
					  }


					  clock_t etime = clock();
					  double elapsedtime = double(etime - stime)/CLOCKS_PER_SEC;
					  std::cout << "parsing time and inserting into vector" << elapsedtime << std::endl;
					  system("pause");
					  /*

					  Json::Value books = root["book"];
					  std::vector<std::string> *book = new std::vector<std::string>[9000];
					  for (int index = 0; index < books.size(); ++index)  // Iterates over the sequence elements.
					  {//  std::cout << plugins[index].asString();
						  book->push_back(plugins[index].get("model","R").asString());
						
					  }*/

					  /*

					  Json::Value indent = root["indent"];
					  int x = indent.get("length", 3).asInt();*/
					  HWND hListView1 = CreateWindowEx(WS_EX_CLIENTEDGE, WC_LISTVIEW, TEXT("ListView"),
						  WS_CHILD | WS_VISIBLE | LVS_SHOWSELALWAYS | LVS_REPORT | WS_HSCROLL,
						  rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top,
						  hWnd, NULL, NULL, 0);
					  					  
					  //ListView_SetItemCountEx(hListView1, 10, 1);
					  LVCOLUMN lvCol;
					  lvCol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
					  lvCol.fmt = LVCFMT_LEFT;

					  lvCol.iSubItem = 0;
					  lvCol.cx = 30;
					  lvCol.pszText = L"";
					  ListView_InsertColumn(hListView1, 0, &lvCol);

					  lvCol.iSubItem = 1;
					  lvCol.cx = 150;
					  lvCol.pszText = L"Name";
					  ListView_InsertColumn(hListView1, 1, &lvCol);

					  lvCol.iSubItem = 2;
					  lvCol.cx = 50;
					  lvCol.pszText = L"IndexID";
					  ListView_InsertColumn(hListView1, 2, &lvCol);

					  lvCol.iSubItem = 3;
					  lvCol.cx = 80;
					  lvCol.pszText = L"Model";
					  ListView_InsertColumn(hListView1, 3, &lvCol);

					  long j = 0;
					  //insert the númber of items
					  
					  while (j <description->size()){

						  LVITEM lvItem;
						  lvItem.mask = LVIF_IMAGE | LVIF_STATE;
						  lvItem.state = 0;
						  lvItem.stateMask = 0;
						  lvItem.iSubItem = 0;
						  lvItem.iItem = j;
						  lvItem.iImage = 1;
						  // if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
						  lvItem.iImage = 0;
						  ListView_InsertItem(hListView1, &lvItem);
						  //std::string s(1,idxBuffer[j]);

						  // text = &descBuffer[j];

						  std::string s = description->at(j);

						  wchar_t wtext[20];
						  mbstowcs(wtext, s.c_str(), strlen(s.c_str()) + 1);//Plus null
						  LPWSTR ptr = wtext;


						  int pagenum = page.at(j);
						   char pagestring[10];
						  sprintf(pagestring,"%d",pagenum);

						  wchar_t wtext1[10];
						  mbstowcs(wtext1, pagestring, strlen(pagestring) + 1);//Plus null
						  LPWSTR ptr1 = wtext1;
						  ListView_SetItemText(hListView1, j, 1, wtext);
						  ListView_SetItemText(hListView1, j, 2, ptr1);
						  ListView_SetItemText(hListView1, j, 3, L"item3");
						  j = j + 1;

					  }

					  delete[] description;

	}
		break;



	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
