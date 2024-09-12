#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <conio.h>

int main()
{
    while (true)
    {

        std::string num_input;

        std::cout << "Enter numbers: ";
        std::getline(std::cin, num_input);
        std::cout << '\n';
        char sorting_method = '0';
        std::cout << "Choose sorting method\n1 - merge sort\n2 - quick sort\n";
        while (true)
        {
            sorting_method = getch();
            if (sorting_method == '1' || sorting_method == '2')
            {
                break;
            }
        }

        { // daughter app

            STARTUPINFO StartupInfo;
            ZeroMemory(&StartupInfo, sizeof(StartupInfo));
            StartupInfo.cb = sizeof(StartupInfo);
            PROCESS_INFORMATION ProcInfo;
            ZeroMemory(&ProcInfo, sizeof(ProcInfo));

            std::string s_App_Name = "Daughter.exe \"" + num_input + "\"" + " " + sorting_method;
            char AppName[2048];
            strcpy(AppName, s_App_Name.c_str());

            size_t convertedChars = 0;
            wchar_t commandlinetext[500] = {0};
            mbstowcs_s(&convertedChars, commandlinetext, s_App_Name.size(), AppName, _TRUNCATE);

            if (!CreateProcess(NULL, AppName, NULL, NULL, FALSE, 0,
                               NULL, NULL, &StartupInfo, &ProcInfo))
            {

                return 0;
            }

            WaitForSingleObject(ProcInfo.hProcess, INFINITE);

            TerminateProcess(ProcInfo.hProcess, 1);
            CloseHandle(ProcInfo.hProcess);
            CloseHandle(ProcInfo.hThread);
        }

        char ch = NULL;

        std::cout << '\n';

        std::cout
            << "q - quit" << '\n';
        std::cout << "Any other key - repeat" << '\n';
        std::cout << '\n';

        ch = getch();

        if (ch == 'q')
        {
            return 0;
        }
    }

    // std::ifstream file;
    // file.open("data.txt");
}