/*
 * mathevaluation.cpp - Example for the MathEvaluation class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2012 - Steffen Ott
 *
 */
 
 
#include <rush/mathevaluation.h>
#include <rush/console.h>


int main(int argc, char** argv)
{
	MathEvaluation eval;
	eval.SetVariable(_T("a"), 3);
	eval.SetVariable(_T("b"), 5);
	eval.Compile(_T("c = sqrt(a*a + b*b)"));
	eval.Execute();
	double c = eval.GetVariable(_T("c"));
	Console::WriteLine(_T("c = %f"), c);
	// Output: c = 5.830951895
}

