#ifndef PARSER_H
#define PARSER_H

#include <SDL.h>

class Parser {
public:
Parser();
~Parser();
bool read_text(const char* source_file, char** destination);
};
#endif