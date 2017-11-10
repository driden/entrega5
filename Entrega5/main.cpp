#include "CasoDePrueba.h"
#include "PruebaMemoria.h"
#include "ConductorPrueba.h"
#include "Sistema.h"

Puntero<ISistema> Inicializar()
{
	return new Sistema();
}

void sil1()
{
	Puntero<ISistema> interfaz = Inicializar();
	Array<Puntero<IEdificio>> ciudad(5);
	ciudad[0] = new EdificioMock(2, 9, 10);
	ciudad[1] = new EdificioMock(3, 7, 15);
	ciudad[2] = new EdificioMock(5, 12, 12);
	ciudad[3] = new EdificioMock(15, 20, 10);
	ciudad[4] = new EdificioMock(19, 24, 8);

	Array<Puntero<ITira>> siluetaEsperada(7);
	siluetaEsperada[0] = new TiraMock(2, 10);
	siluetaEsperada[1] = new TiraMock(3, 15);
	siluetaEsperada[2] = new TiraMock(7, 12);
	siluetaEsperada[3] = new TiraMock(12, 0);
	siluetaEsperada[4] = new TiraMock(15, 10);
	siluetaEsperada[5] = new TiraMock(20, 8);
	siluetaEsperada[6] = new TiraMock(24, 0);

	Array<Puntero<ITira>> siluetaObtenida = interfaz->CalcularSiluetaDeLaCiudad(ciudad);
	
}
void main()
{
	/*Puntero<ConductorPrueba> cp = new ConductorPrueba();
	Array<Puntero<Prueba>> pruebas = Array<Puntero<Prueba>>(3);
	pruebas[0] = new PruebaMemoria();
	pruebas[1] = new CasoDePrueba(Inicializar);
	pruebas[2] = pruebas[0];
	cp->CorrerPruebas(pruebas.ObtenerIterador());*/

	sil1();
	system("pause");
}
