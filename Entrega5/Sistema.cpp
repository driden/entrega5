#include "Sistema.h"
#include "Lista.h"
#include "ListaOrd.h"
#include "ListaEncadenadaImp.h"
#include "ComparacionITira.h"
#include "ListaEncadenada.h"

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

Array<Puntero<ListaOrd<Puntero<ITira>>>> GetSiluetas(Array<Puntero<IEdificio>> ciudad)
{
	Puntero<Comparacion<Puntero<ITira>>> pComp = new ComparacionITira();
	Comparador<Puntero<ITira>> compTira(pComp);

	Puntero<ListaOrd<Puntero<ITira>>> siluetas = new ListaEncadenadaImp<Puntero<ITira>>(compTira);
	
	Array<Puntero<ListaOrd<Puntero<ITira>>>> arrSiluetas(ciudad.Largo);


	for (nat i = 0; i < ciudad.Largo ; i++)
	{
		Puntero<IEdificio> edificio = ciudad[i];
		Puntero<ListaOrd<Puntero<ITira>>> tiras = new ListaEncadenadaImp<Puntero<ITira>>(compTira);
		arrSiluetas[i] = tiras;
		
		Puntero<ITira> tira;
		
		tira = new Tira(edificio->ObtenerXInicial(), edificio->ObtenerAltura());
		tiras->InsertarOrdenado(tira);
		tira = new Tira(edificio->ObtenerXFinal(), 0);
		tiras->InsertarOrdenado(tira);
	}


	// Ordenar el arreglo antes de devolverlo por la x del principio ?
	return arrSiluetas;
}

int Max(int n1, int n2)
{
	return n1 > n2 ? n1 : n2;
}

Puntero<Lista<Puntero<ITira>>> MergeSkyLines(Puntero<Lista<Puntero<ITira>>> skIzq, Puntero<Lista<Puntero<ITira>>> skDer)
{
	//assert(estaOrdenada(skIzq));
	//assert(estaOrdenada(skDer));
	//assert(noTieneAlturasRepetidas(skIzq));
	//assert(noTieneAlturasRepetidas(skDer));

	

	Iterador<Puntero<ITira>> itIzq = skIzq->ObtenerIterador(), itDer = skDer->ObtenerIterador();



	nat hIzq = 0, hDer = 0;
	Puntero<ITira> tira;

	Puntero<Comparacion<Puntero<ITira>>> pComp = new ComparacionITira();
	Comparador<Puntero<ITira>> compTira(pComp);
	Puntero<Lista<Puntero<ITira>>> lMerge = new ListaEncadenada<Puntero<ITira>>(compTira);

	while(itIzq.HayElemento() && itDer.HayElemento())
	{
		Puntero<ITira> pDer = itDer.ElementoActual(), pIzq = itIzq.ElementoActual();
		
		nat x = 0;

		if (pDer->ObtenerX() < pIzq->ObtenerAltura())
		{
			hDer = pDer->ObtenerAltura();
			x = pDer->ObtenerX();

			itDer.Avanzar();
		}
		else
		{
			hIzq = pIzq->ObtenerAltura();
			x = pIzq->ObtenerX();

			itIzq.Avanzar();
		}
		nat nuevaH = Max(hIzq, hDer);
		
		//controlo que no haya un nodito con la misma altura ya
		if (tira->ObtenerAltura() == nuevaH) continue;
		
		tira = new Tira(x, nuevaH);
		lMerge->Insertar(tira);
	}

	if(itIzq.HayElemento())
	{
		while(itIzq.HayElemento())
		{
			lMerge->Insertar(itIzq.ElementoActual());
			itIzq.Avanzar();
		}
	}
	else if (itDer.HayElemento())
	{
		while (itDer.HayElemento())
		{
			lMerge->Insertar(itDer.ElementoActual());
			itDer.Avanzar();
		}
	}
	return lMerge;
}

Puntero<Lista<Puntero<ITira>>> SkyLine(Array<Puntero<ListaOrd<Puntero<ITira>>>> tiras, int desde, int hasta)
{
	Puntero<Lista<Puntero<ITira>>> lista = nullptr;
	if (desde < hasta)
	{
		int medio = (desde + hasta) / 2;
		Puntero<Lista<Puntero<ITira>>> skIzq = SkyLine(tiras, desde, medio);
		Puntero<Lista<Puntero<ITira>>> skDer = SkyLine(tiras, medio+1, hasta);
		lista = MergeSkyLines(skIzq, skDer);
	}
	return lista;
}
Array<Puntero<ITira>> Sistema::CalcularSiluetaDeLaCiudad(Array<Puntero<IEdificio>> ciudad)
{
	// Paso 1: Convierto todos los IEdificio en ITiras de (x, altura)
	Array<Puntero<ListaOrd<Puntero<ITira>>>> siluetas = GetSiluetas(ciudad);

	std::cout << "Tiras:\n";
	
	for (nat i = 0; i < siluetas.Largo; i++)
	{
		Iterador<Puntero<ITira>> iterTiras = siluetas[i]->ObtenerIterador();
		while (iterTiras.HayElemento())
		{
			Puntero<ITira> tiraActual = iterTiras.ElementoActual();
			std::cout << "(x:" << tiraActual->ObtenerX() << ", h:" << tiraActual->ObtenerAltura() << ") ";

			iterTiras.Avanzar();
		}
		std::cout << endl;
	}
	
	std::cout << endl;

	Puntero<Lista<Puntero<ITira>>> lsita = SkyLine(siluetas, 0, siluetas.Largo - 1);
	Iterador<Puntero<ITira>> iterTiras = lsita->ObtenerIterador();
	std::cout << " skyline: "<< endl;
	while (iterTiras.HayElemento())
	{
		Puntero<ITira> tiraActual = iterTiras.ElementoActual();
		std::cout << "(x:" << tiraActual->ObtenerX() << ", h:" << tiraActual->ObtenerAltura() << ") ";

		iterTiras.Avanzar();
	}
	std::cout << endl;

	// Algoritmo principal

	return Array<Puntero<ITira>>(); //retorno por defecto
};


nat Sistema::CalcularCoeficienteBinomial(nat n, nat k)
{
	/*
	Codigo de implementacion de la solucion
	*/
	return 0; //retorno por defecto
};


