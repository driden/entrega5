#ifndef SISTEMA_H
#define SISTEMA_H

#include "ISistema.h"
#include "Tira.h"
#include "Lista.h"
#include "ArrayIteracion.h"
#include "ListaOrd.h"

class Sistema : public ISistema
{
public:
	Sistema();
	//EJ 1
	void TransponerMatriz(Matriz<nat> matriz);
	Puntero<ListaOrd<Puntero<ITira>>>
	MergeSkyLines(Puntero<ListaOrd<Puntero<ITira>>> skIzq, Puntero<ListaOrd<Puntero<ITira>>> skDer);
	Puntero<ListaOrd<Puntero<ITira>>> SkyLine(Array<Puntero<ListaOrd<Puntero<ITira>>>> tiras, int desde, int hasta);
	//EJ 2
	Array<Puntero<ITira>> CalcularSiluetaDeLaCiudad(Array<Puntero<IEdificio>> ciudad);
	//EJ 3
	nat CalcularCoeficienteBinomial(nat n, nat k);
private:
	//Comaprador de Tiras
	Comparador<Puntero<ITira>> compITira;
};
#endif
