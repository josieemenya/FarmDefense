// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleMacros.h"

SimpleMacros::SimpleMacros()
{
}

SimpleMacros::~SimpleMacros()
{
}

bool SimpleMacros::FlipFlop(UObject* x)
{
	localbool = !localbool;
	return localbool;
}

