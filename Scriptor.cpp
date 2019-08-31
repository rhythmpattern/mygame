#include "Scriptor.h"

Scriptor* Scriptor::s_pInstance = 0;

double Scriptor::getNum(const char *in)
{
 
  double x;
  for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
      if (e->Value() == std::string(in))
      	{
	  e->Attribute("value",&x);
      	}
      	}
 
	  return x;
}

int Scriptor::getInt(const char *in)
{
  int x;
  for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
      if (e->Value() == std::string(in))
      	{
	  e->Attribute("value",&x);
      	}
      	}
	  return x;
}


std::string Scriptor::getString(std::string in)
{
 
   for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
      if (e->Value() == std::string(in))
      	{
	  return e->Attribute("value");
      	}
      	}
	  return "";
}
