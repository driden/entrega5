#pragma once
#include "Comparacion.h"
#include "ITira.h"
#include "Puntero.h"

class ComparacionITira : public Comparacion<Puntero<ITira>>
{
public:
	ComparacionITira();
	~ComparacionITira();

	CompRetorno Comparar(const Puntero<ITira>& t1, const Puntero<ITira>& t2) const override;
};

