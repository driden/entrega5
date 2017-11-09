﻿#include "Sistema.h"
#include "Lista.h"
#include "ListaOrd.h"
#include "ListaEncadenadaImp.h"

Sistema::Sistema()
{

}

void Sistema::TransponerMatriz(Matriz<nat> matriz)
{
	/*
	Codigo de implementacion de la solucion
	*/
	return; //retorno por defecto
};

Puntero<ListaOrd<Puntero<ITira>>> GetSiluetas(Array<Puntero<IEdificio>> ciudad)
{
	Comparador<Puntero<ITira>> compTira;
	Puntero<ListaOrd<Puntero<ITira>>> siluetas = new ListaEncadenadaImp<Puntero<ITira>>(compTira);

	for (nat i = 0; i < ciudad.Largo ; i++)
	{
		Puntero<IEdificio> edificio = ciudad[i];
		Puntero<ITira> tira;
		
		tira = new Tira(edificio->ObtenerXInicial(), edificio->ObtenerAltura());
		siluetas->InsertarOrdenado(tira);
		tira = new Tira(edificio->ObtenerXFinal(), 0);
		siluetas->InsertarOrdenado(tira);
	}

	return siluetas;
}


Array<Puntero<ITira>> Sistema::CalcularSiluetaDeLaCiudad(Array<Puntero<IEdificio>> ciudad)
{
	// Paso 1: Convierto todos los IEdificio en ITiras de (x, altura)
	Array<Puntero<ITira>> siluetas = GetSiluetas(ciudad);




	return Array<Puntero<ITira>>(); //retorno por defecto
};


nat Sistema::CalcularCoeficienteBinomial(nat n, nat k)
{
	/*
	Codigo de implementacion de la solucion
	*/
	return 0; //retorno por defecto
};


