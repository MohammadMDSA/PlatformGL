#pragma once
#include "pch.h"

class IFunctionalObject
{

public:
	virtual void			Update(GLFWwindow* window) = 0;
	virtual void			Setup() = 0;

};

