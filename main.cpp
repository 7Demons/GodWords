#include <stdlib.h>
#include <iostream>
#include <immintrin.h>
#include <windows.h>
#include <winuser.h>
#include <fstream>
#include <vector>
#include <locale>
#include <codecvt>
#include "file.cpp"
#pragma comment(lib, "User32.lib")


int intInRange(int max) {
    unsigned int rand;
    _rdrand32_step(&rand);
    rand = rand % max;

    return rand;
}

void typeString(std::string& godsWord) {
    godsWord += " ";
    for (char c : godsWord) {
        INPUT input;
        input.type = INPUT_KEYBOARD;
        input.ki.wVk = 0;
        input.ki.wScan = c;
        input.ki.dwFlags = KEYEVENTF_UNICODE;
        input.ki.time = 0;
        input.ki.dwExtraInfo = 0;

        SendInput(1, &input, sizeof(INPUT));

        input.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &input, sizeof(INPUT));
    }
}

void getGodsWord(std::vector<std::string> godWords) {
    int max = godWords.size();
    int rand = intInRange(max);
    char *holyWord = (char *)godWords.at(rand).c_str(); 
    printf("%s ", holyWord);
    typeString((std::string)holyWord);
}   

void getBibleQuote(std::vector<std::string> bibleWords) {
    int max = bibleWords.size();
    int rand = intInRange(max);
    char *holyScripture = (char *)bibleWords.at(rand).c_str(); 
    printf("%s \n ", holyScripture);
    typeString((std::string)holyScripture);
}

int main() {
    std::vector<std::string> godWords = readFile("vocab.txt", '\n', 0);
    std::vector<std::string> bibleWords = readFile("bible.txt", '\n', 2);
    
    system("color f1");
    printf("God says: ");
    while (!GetAsyncKeyState(VK_ESCAPE)) {
        if (GetAsyncKeyState(VK_F7) && GetAsyncKeyState(VK_SHIFT))  {
            getBibleQuote(bibleWords);
        }

        else if (GetAsyncKeyState(VK_F7)) {
            getGodsWord(godWords);
        }

        Sleep(100);
    }

    return EXIT_SUCCESS;

}