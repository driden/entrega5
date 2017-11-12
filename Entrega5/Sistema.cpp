#include "Sistema.h"
#include "ListaOrd.h"
#include "ListaEncadenadaImp.h"
#include "ComparacionITira.h"
#include "ListaEncadenada.h"
#include <tuple>
#include <condition_variable>

//#define DEBUG

Sistema::Sistema()
{
	Puntero<Comparacion<Puntero<ITira>>> pComp = new ComparacionITira();
	compITira = Comparador<Puntero<ITira>>(pComp);
}

void Intercambiar(Matriz<nat>& matriz, int x3, int y3, int x2, int y2, int dimension)
{
	// pq es el de abajo a la izq, posX y posY son el de arriba a la der
	int p = x3, q = y3, posX = x2;

	for (int x = p; x < dimension + p; x++)
	{
		int posY = y2;
		for(int y = q ; y < dimension + q; y++)
		{			
			int nX = posX;
			int nY = posY; 
			int temp = matriz[nX][nY];

			matriz[nX][nY] = matriz[x][y];
			matriz[x][y] = temp;
			posY++;
		}

		posX++;
	}
}

void traspuesta(Matriz<nat> &m, int x, int y, int n) // n es la dimension
{
	if (n > 1) {
		assert(n%2==0);

		traspuesta(m, x, y, n / 2);
		traspuesta(m, x + n / 2, y, n / 2);
		traspuesta(m, x, y + n / 2, n / 2);
		traspuesta(m, x + n / 2, y + n / 2, n / 2);

		Intercambiar(m, x, y + (n / 2), x + (n / 2), y , n / 2);
	}
	else
		assert(n == 1);
}

void Sistema::TransponerMatriz(Matriz<nat> matriz)
{
	traspuesta(matriz, 0, 0, matriz.Largo);	
};

template <class T>
Array<T> ListOrdToArray(Puntero<ListaOrd<T>> lista)
{
	Iterador<T> itLista = lista->ObtenerIterador();

	Array<T> arrConv(lista->Largo());

	for (nat i = 0; i < arrConv.Largo; i++)
	{
		arrConv[i] = itLista.ElementoActual();
		itLista.Avanzar();
	}
	return arrConv;
}

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

void InsertarRestantes(Iterador<Puntero<ITira>> itIzq, Iterador<Puntero<ITira>> itDer, Puntero<ListaOrd<Puntero<ITira>>> &lMerge)
{
	int hAnterior = -1;
	Puntero<ITira> tira;
	if(itIzq.HayElemento())
	{
		while(itIzq.HayElemento())
		{
			tira = itIzq.ElementoActual();
			itIzq.Avanzar();

			if (hAnterior != tira->ObtenerAltura())
			{
				lMerge->InsertarOrdenado(tira);
				hAnterior = tira->ObtenerAltura();
			}				
		}
	}
	else if (itDer.HayElemento())
	{
		while (itDer.HayElemento())
		{
			tira = itDer.ElementoActual();
			itDer.Avanzar();

			if (hAnterior != tira->ObtenerAltura())
			{
				lMerge->InsertarOrdenado(tira);
				hAnterior = tira->ObtenerAltura();
			}
		}
	}

}

void MergearListas(Iterador<Puntero<ITira>> itIzq, Iterador<Puntero<ITira>> itDer, Puntero<ListaOrd<Puntero<ITira>>> &lMerge)
{
#ifdef DEBUG
	std::cout << "Skyline de: \n";
	while (itIzq.HayElemento())
	{
		std::cout << "(" << itIzq.ElementoActual()->ObtenerX() << "," << itIzq.ElementoActual()->ObtenerAltura() << ") ";
		itIzq.Avanzar();
	}
	itIzq.Reiniciar();
	std::cout << "|| ";
	while (itDer.HayElemento())
	{
		std::cout << "(" << itDer.ElementoActual()->ObtenerX() << "," << itDer.ElementoActual()->ObtenerAltura() << ") ";
		itDer.Avanzar();
	}
	itDer.Reiniciar();
#endif


	nat hIzq = 0, hDer = 0;
	Puntero<ITira> tira;
	while(itIzq.HayElemento() && itDer.HayElemento())
	{
		Puntero<ITira> pDer = itDer.ElementoActual(), pIzq = itIzq.ElementoActual();		
		nat x = 0;

		if (pDer->ObtenerX() < pIzq->ObtenerX())
		{
			hDer = pDer->ObtenerAltura();
			x = pDer->ObtenerX();

			itDer.Avanzar();
		}
		else if (pDer->ObtenerX() > pIzq->ObtenerX())
		{
			hIzq = pIzq->ObtenerAltura();
			x = pIzq->ObtenerX();

			itIzq.Avanzar();
		}
		else
		{
			//Misma x, me quedo con el que tenga mayor altura
			if (pIzq->ObtenerAltura() > pDer->ObtenerAltura())
				hIzq = pIzq->ObtenerAltura();
			else
				hDer = pDer->ObtenerAltura();
			
			itDer.Avanzar();
			itIzq.Avanzar();
		}
		
		nat nuevaH = Max(hIzq, hDer);
		
		//controlo que no haya un nodito con la misma altura ya
		if (tira && tira->ObtenerAltura() == nuevaH) continue;
		
		tira = new Tira(x, nuevaH);
		lMerge->InsertarOrdenado(tira);

	}
	InsertarRestantes(itIzq, itDer, lMerge);

#ifdef DEBUG
	Iterador<Puntero<ITira>> itMerge = lMerge->ObtenerIterador();
	std::cout << endl << "Obtenido: \n";
	while (itMerge.HayElemento())
	{
		std::cout << "(" << itMerge.ElementoActual()->ObtenerX() << "," << itMerge.ElementoActual()->ObtenerAltura() << ") ";
		itMerge.Avanzar();
	}
	itMerge.Reiniciar();
	std::cout << endl << endl;
#endif // DEBUG
}

Puntero<ListaOrd<Puntero<ITira>>> Sistema::MergeSkyLines(Puntero<ListaOrd<Puntero<ITira>>> skIzq, Puntero<ListaOrd<Puntero<ITira>>> skDer)
{
	if (!skIzq && skDer) //Si la izq es nula
	{
		return skDer;
	}
	if (skIzq && !skDer) //Si la der es nula
	{
		return skIzq;
	}
	if(!skIzq && !skDer)
	{
		return nullptr;
	}

	Iterador<Puntero<ITira>> 
		itIzq = skIzq->ObtenerIterador(), 
		itDer = skDer->ObtenerIterador();

	
	Puntero<ListaOrd<Puntero<ITira>>> lMerge = new ListaEncadenadaImp<Puntero<ITira>>(compITira);

	MergearListas(itIzq, itDer, lMerge);
	
	return lMerge;
}

Puntero<ListaOrd<Puntero<ITira>>> ListarTiras (Array<Puntero<ListaOrd<Puntero<ITira>>>> tiras, int desde, int hasta)
{
	Puntero<Comparacion<Puntero<ITira>>> pComp = new ComparacionITira();
	Puntero<ListaOrd<Puntero<ITira>>> l = new ListaEncadenadaImp<Puntero<ITira>>(Comparador<Puntero<ITira>>(pComp));

	for ( int i = desde; i <= hasta ; i++)
	{
		Puntero<ListaOrd<Puntero<ITira>>> ltiras = tiras[i];
		Iterador<Puntero<ITira>> itPTira = ltiras->ObtenerIterador();
		
		while (itPTira.HayElemento())
		{
			l->InsertarOrdenado(itPTira.ElementoActual());
			itPTira.Avanzar();
		}
		
	}
	return l;
}

Puntero<ListaOrd<Puntero<ITira>>> Sistema::SkyLine(Array<Puntero<ListaOrd<Puntero<ITira>>>> tiras, int desde, int hasta)
{
	if (desde < hasta)
	{
		int medio = (desde + hasta) / 2;
		
		//ListarTiras(tiras, desde, medio);
		Puntero<ListaOrd<Puntero<ITira>>> lIzq = SkyLine(tiras, desde, medio);		
		//ListarTiras(tiras, medio + 1, hasta);
		Puntero<ListaOrd<Puntero<ITira>>> lDer = SkyLine(tiras, medio + 1, hasta);
		
#ifdef DEBUG
		std::cout << "\n SkyLine desde " << desde << " hasta " << hasta << endl;
#endif
		return MergeSkyLines(lIzq, lDer);
	}else if (desde == hasta)
	{
		return ListarTiras(tiras, desde, hasta);
	}
	return nullptr;
}

Array<Puntero<ITira>> Sistema::CalcularSiluetaDeLaCiudad(Array<Puntero<IEdificio>> ciudad)
{
	// Paso 1: Convierto todos los IEdificio en ITiras de (x, altura)
	Array<Puntero<ListaOrd<Puntero<ITira>>>> siluetas = GetSiluetas(ciudad);
#ifdef DEBUG
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
#endif
	
	Puntero<ListaOrd<Puntero<ITira>>> lista = SkyLine(siluetas, 0, siluetas.Largo - 1);	
#ifdef DEBUG
	Iterador<Puntero<ITira>> iterTiras = lista->ObtenerIterador();
	std::cout << " skyline: "<< endl;
	while (iterTiras.HayElemento())
	{
		Puntero<ITira> tiraActual = iterTiras.ElementoActual();
		std::cout << "(x:" << tiraActual->ObtenerX() << ", h:" << tiraActual->ObtenerAltura() << ") ";

		iterTiras.Avanzar();
	}
	std::cout << endl;
#endif
	// Algoritmo principal

	Puntero<ListaOrd<Puntero<ITira>>> listaRes = SkyLine(siluetas, 0, static_cast<int>(siluetas.Largo)-1);

	return ListOrdToArray(listaRes);
};



nat Sistema::CalcularCoeficienteBinomial(nat n, nat k)
{
	if (k > n) return 0;
	if (n < 1) return 1;

	Array<int> memorizacion(n + 1,0);
	memorizacion[0] = 1; 

	for (nat i = 1; i <= n; i++)
	{
		// Compute next row of pascal triangle using
		// the previous row
		for (nat j = i; j > 0; j--)
			memorizacion[j] = memorizacion[j] + memorizacion[j - 1];
	}
	return memorizacion[k];

};


