#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

std::vector<std::string> readFile(const char *fn, const char delim, int delimCount) {
    std::fstream fs;
    fs.open(fn);

    if (!fs.is_open()) {
        printf("Error. Could not fine the file.\n %s", fn);
        exit(EXIT_FAILURE);
    }

    std::filebuf *buf = fs.rdbuf();

    std::vector<std::string> words;

    std::string word;

    int delimCounter = 0;
    do {
      char ch = buf->sgetc();
      if (ch == delim && delimCounter == delimCount) {
        words.push_back(word);
        word.clear();
        delimCounter = 0;
      } 
      else if (ch == delim || ch == '\r')  {
        delimCounter++;
      } 
      else {
        word.push_back(ch);
      }
    } while ( buf->snextc() != EOF );

    buf->close();
    fs.close();

    return words;
}