#ifndef SISTEMA_H
#define SISTEMA_H

#include "ISistema.h"
#include "Tira.h"

class Sistema : public ISistema
{
public:
	Sistema();
	//EJ 1
	void TransponerMatriz(Matriz<nat> matriz);
	//EJ 2
	Array<Puntero<ITira>> CalcularSiluetaDeLaCiudad(Array<Puntero<IEdificio>> ciudad);
	//EJ 3
	nat CalcularCoeficienteBinomial(nat n, nat k);
	};

#endif
