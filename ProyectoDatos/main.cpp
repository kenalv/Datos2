//Mapa por medio de grafos, arboles y
//memoria secundaria
//------------------------------------
//Fecha de inicio: 07/10/2015
//Ultima modificacion: ...
//------------------------------------
//Programadores:
//      Mauro López J.
//      Kenneth Alvarez E.


//Librerias a utilizar
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string.h>

using namespace std;

//Estructura de arbol binario tipo conductor
struct conductor
{
    string id;
    string nombreConductor;
    string tipoVehiculo;
    //apuntador a archivo de rutas ---> por hacer

    struct conductor *izq;
    struct conductor *der;

    conductor(string identif, string nombC, string tipoV)
    {
        id = identif;
        nombreConductor = nombC;
        tipoVehiculo = tipoV;

        izq = NULL;
        der = NULL;
    }
}*raizConductor;

//Estructura de arbol binario tipo ruta

struct ruta
{
    string nombre; //El nombre estara compuesto por la primera y ultima ciudad en la ruta
    int distanciaRuta; //puede ser de tipo long

    //lista que contiene las ciudades que compone la ruta
    struct ruta *izq;
    struct ruta *der;

    ruta(string n, int distancia)
    {
        nombre = n;

        distanciaRuta = distancia;
        izq = NULL;
        der = NULL;
    }
}*raizRuta;



struct ciudad{
	string nombreCiudad;
	bool visitado; // para evitar que vuelva a pasar por esta ciudad.. marcarlo como true o false
	struct ciudad * sigC; //para señalar la siguiente ciudad
	struct autoPista *primerAutoPista;//sublista de arcos
	ciudad (string n){
		nombreCiudad = n;
		visitado = false;
        sigC=NULL;
		primerAutoPista = NULL;
	}
}*grafo; // declaaramos el grafo

//struct ciudad listaRutas[10];

struct autoPista {
    //char destino; //para directorio de nodos
    struct vertice *destino;// para multilista
    int distancia;
    int velocidad;
    bool dirigido;
    struct autoPista *sigA;

    autoPista(struct vertice * enlaceDestino,int dist, int velocidad){ // dist = hace referencia a distancia.
        distancia = dist;
        destino = enlaceDestino;    //Va a ser la union con la ciudad...
        sigA = NULL;
        dirigido = false;
        velocidad = velocidad;
    }
};



//Estructura archivo Rutas
struct nombre{
    char nom[10];

};

struct rutas{
//arregki de 19 ciudades
    struct nombre ciudad[10]; //un nombre de 10 caracteres...  //por ahora una sola ciudad
    int distancia;
    long sig;
    struct nombre listaCiudades[10];

}reg;

fstream archivoRutas("ArchivoRutas.txt",ios::in | ios::out |ios::binary | ios::trunc);


struct conductoresArch{
    public:
    int id;
    char nombreConductor[10];
    char tipoVehiculo[10];

    long izq, der,punteroRutas;

}regConductor;

fstream archivoConductores("ArchivoConductores.txt",ios::in | ios::out |ios::binary | ios::trunc);

struct arcoArch{
    char destino[10];
    int velocidad;
    char dirigido[10];
    int distancia;

    long sig;
};


fstream archivoArcos("ArchivoArcos.txt",ios::in | ios::out |ios::binary | ios::trunc);



int main()
{
//insertar Arcos
    struct arcoArch reg1;

    strcpy(reg1.destino, "Ana");
    strcpy(reg1.dirigido, "TRUE");
    reg1.distancia = 100;
    reg1.velocidad = 80;
    reg1.sig=-1;
    archivoArcos.write(reinterpret_cast<char *>(&reg1),sizeof(reg1));
//Insertar Archivo Ciudades


    struct conductoresArch reg2;

    strcpy(reg2.nombreConductor, "Kenneth");
    strcpy(reg2.tipoVehiculo, "New");
    reg2.der=3;
    reg2.izq = -1;
    reg2.id = 30;
    archivoConductores.write(reinterpret_cast<char *>(&reg2),sizeof(reg2));

        archivoArcos.seekg(sizeof(0,ios::beg));
        archivoArcos.read(reinterpret_cast<char*>(&reg1),sizeof(reg1));
    cout<<sizeof(reg1);
    return 0;
}
