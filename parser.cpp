#include "parser.h"

Parser::Parser(){}
Parser::~Parser(){}

bool Parser::read_text(const char* source_file, char** destination)
{
    // Open the file
    SDL_RWops *file;
    file = SDL_RWFromFile(source_file, "r");



    size_t file_length = SDL_RWseek(file, 0, SEEK_END);
    (*destination) = new char[file_length+1]; // allow an extra character


    // Reset seek to beginning of file and read text
    SDL_RWseek(file, 0, SEEK_SET);
    int n_blocks = SDL_RWread(file, (*destination), 1, file_length);
    if (n_blocks <= 0)
    {


    }
    SDL_RWclose(file);

    (*destination)[file_length] = '\0';



    return true;
}