#pragma once
#include"pubUse.h"
#include"user.h"
class UI
{
public:
	UI();
	~UI();
	void initial();
	void welcome();
	void logIn();
	void guest(user guest);
	void manager(user manager);
	void inquire();
};

