#pragma once
#include"pubUse.h"
class user
{
private:
	string rights;
	string ID;
	string password;
public:
	void setRights(string r) { rights = r; }
	void setID(string i) { ID = i; }
	void setPwd(string p) { password = p; }
	string getID() { return ID; }
	string getPwd() { return password; }
};