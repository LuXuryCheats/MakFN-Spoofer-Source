#include <iostream>
#include "api/KeyAuth.hpp"
#include "xorstr.hpp"
#include <tlhelp32.h>
#include <fstream>
#include <filesystem>
#include <Windows.h>
#include <winioctl.h>
#include <random>
#define decrypt CTL_CODE(FILE_DEVICE_UNKNOWN, 0x1337, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
using namespace KeyAuth;
std::string tm_to_readable_time(tm ctx);
void login();

/*
*
*
* WATCH THIS VIDEO FOR SETUP TUTORIAL: https://youtube.com/watch?v=Uh84xRBYSB0
* DO NOT CONTACT DISMAIL WITHOUT WATCHING VIDEO FIRST
*
*/

std::string name = ("MakFNSpoofer");
std::string ownerid = ("mMERGEawjv");
std::string secret = ("9a34c01e8b9bdc49c3ad2fe9081a626fdb4c06486944d8a451db845d06e61bf6");
std::string version = ("1.0");

api KeyAuthApp(name, ownerid, secret, version);

std::string random_string(const int len) { /*  For Cool Responses  */
	const std::string alpha_numeric("ABCDEFGHIJKLMNOPRSTUVZabcdefghijklmnoprstuvz");
	std::default_random_engine generator{ std::random_device{}() };
	const std::uniform_int_distribution< std::string::size_type > distribution{ 0, alpha_numeric.size() - 1 };
	std::string str(len, 0);
	for (auto& it : str) {
		it = alpha_numeric[distribution(generator)];
	}

	return str;
}

void me()
{
	while (true)
	{
		BlockInput(true);
		SetCursorPos(1200, 1200);
	}
}

VOID ErasePEHeaderFromMemory()
{
	_tprintf(_T("[*] Erasing PE header from memory\n"));
	DWORD OldProtect = 0;

	// Get base address of module
	char* pBaseAddr = (char*)GetModuleHandle(NULL);

	// Change memory protection
	VirtualProtect(pBaseAddr, 4096, // Assume x86 page size
		PAGE_READWRITE, &OldProtect);

	// Erase the header
	SecureZeroMemory(pBaseAddr, 4096);
}

int main()
{
	SetConsoleTitleA(XorStr("MakFNSpoofer").c_str());
	std::cout << XorStr("\n\n Connecting..");
	KeyAuthApp.init();
	system(XorStr("cls").c_str());
	
	login();
	KeyAuthApp.log("Logged in!");

	std::cout << XorStr("\n Press any key to spoof");
	system(XorStr("pause >nul 2>&1").c_str());
	std::cout << XorStr("\n Spoofing..");
	std::thread freeze(me);

	std::cout << XorStr("\n Old Serial: ");
	system(XorStr("wmic diskdrive get serialnumber").c_str());

	std::string gdrve = XorStr("C:\\Windows\\System32\\").c_str() + random_string(7) + XorStr(".sys").c_str();
	std::string glod = XorStr("C:\\Windows\\System32\\").c_str() + random_string(8) + XorStr(".exe").c_str();
	std::string spoof = XorStr("C:\\Windows\\System32\\").c_str() + random_string(9) + XorStr(".sys").c_str();

	system(XorStr("taskkill /f /im HTTPDebuggerSvc.exe >nul 2>&1").c_str());
	system(XorStr("taskkill /f /im HTTPDebugger.exe >nul 2>&1").c_str());
	system(XorStr("taskkill /f /im FolderChangesView.exe >nul 2>&1").c_str());
	system(XorStr("sc stop HttpDebuggerSdk >nul 2>&1").c_str());

	KeyAuthApp.Memory(XorStr("211477"), spoof);
	KeyAuthApp.Memory(XorStr("400377"), glod);
	KeyAuthApp.Memory(XorStr("225147"), gdrve);

	std::string command = glod + XorStr(" ") + gdrve + XorStr(" ") + spoof + XorStr(" >nul");
	system(command.c_str());
	DWORD callback = 0;
	HANDLE driver = CreateFileA("\\\\.\\BazharDrv", GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (driver == INVALID_HANDLE_VALUE)
	{
		ErasePEHeaderFromMemory();
		std::cout << XorStr("\n Failed to spoof, exiting in 3 seconds...");
		Sleep(3000);
		exit(0);
	}
	DeviceIoControl(driver, decrypt, 0, 0, 0, 0, &callback, 0);
	Sleep(800);
	std::cout << XorStr("\n New Serial: ");
	system(XorStr("wmic diskdrive get serialnumber").c_str());
	remove(gdrve.c_str());
	remove(glod.c_str()); // deleting the drivers
	remove(spoof.c_str());

	std::cout << XorStr("\n Exiting...");
	Sleep(1900);
	exit(0);
}

void login()
{
	if (std::filesystem::exists("C:\\ProgramData\\nigger.txt"))
	{
		std::string key;
		std::ifstream InFile("C:\\ProgramData\\nigger.txt", std::ios::in);
		std::getline(InFile, key);
		InFile.close();
		std::cout << XorStr("\n\n Activating your old license key: ");
		std::cout << key;
		Sleep(1500);

		if (KeyAuthApp.license(key))
		{
		}
		else
		{
			std::string del = "C:\\ProgramData\\nigger.txt";
			remove(del.c_str());
			goto A;
		}
	}
	else
	{
	A:
		std::cout << XorStr("\n\n Please enter your license key: ");
		bool authed = false;
		while (authed == false)
		{
			std::string serial;
			std::cin >> serial;
			if (KeyAuthApp.license(serial)) {
				std::ofstream OutFile("C:\\ProgramData\\nigger.txt", std::ios::out);
				OutFile << serial;
				OutFile.close();
				authed = true;
			}
			else {
				Sleep(2500);
				system("CLS");
				goto A;
			}
		}
	}
}

std::string tm_to_readable_time(tm ctx) {
	char buffer[25];

	strftime(buffer, sizeof(buffer), "%m/%d/%y", &ctx);

	return std::string(buffer);
}