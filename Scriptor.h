#ifndef SCRIPTOR_H
#define SCRIPTOR_H

#include <string>
#include "tinyxml.h"

class Scriptor
{
 public:
  Scriptor(){file="assets/params.xml"; doc.LoadFile(file.c_str()); pRoot = doc.RootElement();}
  ~Scriptor(){}


 
 static Scriptor* Instance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new Scriptor();
            return s_pInstance;
        }
        
        return s_pInstance;
    }

 double getNum(const char *in);
 int    getInt(const char *in);
 std::string getString(std::string in);
 void loadFile(std::string in) {file=in; doc.LoadFile(in); pRoot = doc.RootElement();}
 
 private:
static Scriptor* s_pInstance;
 std::string file;
 TiXmlDocument doc;
 TiXmlElement* pRoot;
};

#define script Scriptor::Instance()

#endif
