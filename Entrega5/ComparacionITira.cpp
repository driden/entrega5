#ifndef COMPARACION_TIRA_CPP
#define COMPARACION_TIRA_CPP
#include "ComparacionITira.h"
#include <cassert>


ComparacionITira::ComparacionITira() {}

ComparacionITira::~ComparacionITira() {}

CompRetorno ComparacionITira::Comparar(const Puntero<ITira>& t1, const Puntero<ITira>& t2) const
{
	const nat x1 = t1->ObtenerX(), x2 = t2->ObtenerX();
	if (x1 >  x2) return MAYOR;
	if (x1 <  x2) return MENOR;
	if (x1 == x2) return IGUALES;

	assert(false);
	return DISTINTOS;
}
#endif