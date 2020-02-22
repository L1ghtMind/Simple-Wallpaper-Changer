#include <windows.h>
#include <iostream>
#include <shlobj.h>
#include <time.h>
#include <cstdlib>
#include <string>
#include <sstream>
#include <dirent.h>
using namespace std;

bool setBackground();         
int directorySize();

const string strLocalDirectory = "C:\\Image\\Wallpapers\\"; // PATH TO DIRECTORY WITH THE IMAGES
string filePath;

int main() 
{
	
    if (setBackground()) {
        cout << "Applied Background: " << filePath << "\n";
        cout << directorySize();
    }
    else {
        DWORD DWLastError = GetLastError();
        cout << "\nError: " << std::hex << DWLastError;
    }
    system("pause");
    
    return EXIT_SUCCESS;
}

bool setBackground()
{ 
    int bgChoice = 0; // INDEX OF WALLPAPER WE CHOOSE
    srand((unsigned int)time(NULL));
    bgChoice = rand() % directorySize()+1; ////Convert the index choice into a usable filename string.
    stringstream ssFilePath;
    ssFilePath << strLocalDirectory << bgChoice << ".jpg";
    if (SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (PVOID)ssFilePath.str().c_str(),
        SPIF_UPDATEINIFILE | SPIF_SENDCHANGE) != 0)
    {
        filePath = ssFilePath.str();
        return true;
    }
    return false;
 }

int directorySize()
{
    int file_count = 0;
    DIR* dir;
    struct  dirent* entry;
    dir = opendir("C:\\Image\\Wallpapers\\");
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_REG)
        {
            file_count++;
        }
    }
    closedir(dir);
    return file_count;   //COUNT OF IMAGES IN THE DIRECTORY
}