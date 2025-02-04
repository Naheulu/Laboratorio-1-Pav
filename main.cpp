#include "iostream"
#include "DtSocio.h"
#include "Socio.h"
#include "Clase.h"
#include "Spinning.h"
#include "Entrenamiento.h"
#include "DtClase.h"
#include "DtEntrenamiento.h"
#include "DtSpinning.h"
#include "Inscripcion.h"

//Constantes de los arreglos
#define MAX_SOCIOS 20
#define MAX_CLASES 20
using namespace std;

//Colecciones Globales
struct Socios
{
    Socio* s[MAX_SOCIOS];
    int tope = 0;
} colSocios;

struct Clases
{
    Clase* c[MAX_CLASES];
    int tope = 0;
} colClases;


void agregarSocio(string ci, string nombre);
void menuAgregarSocio();
void menuListarSocios();
void ListarSocios();
void agregarClase(DtClase & clase);
void menuAgregarClase();
void menuListarClases();
void ListadoClases();
void agregarInscripcion(string ciSocio, int idClase, Fecha fecha);
void menuAgregarInsc();

void menuAgregarSocio(){
    system("clear");
    cout << "+-----------------------+" << endl;
    cout << "|  1. Agregar un Socio  |" << endl;
    cout << "+-----------------------+" << endl;
    // Funcion para agregar el socio
    string ci, nombre;
    cout << "Ingrese el nombre del Socio: ";
    cin >> nombre;
    cout << "Ingrese la Cedula del Socio: ";    
    cin >> ci;
    
    try
    {        
        agregarSocio(ci, nombre);
        cout << "Socio agregado correctamente!" << endl;
        system("pause");
    }
    catch(invalid_argument& e)
    {
        cout << e.what() << endl;
        system("pause");
    }
}

void menuListarSocios(){
    system("clear");
    cout << "+------------------------+" << endl;
    cout << "|  2. Listar los Socios  |" << endl;
    cout << "+------------------------+" << endl;
    try
    {
        ListarSocios();
    }
    catch(invalid_argument& e)
    {
        cout << e.what() << endl;
        system("pause");
    }
}

void ListarSocios(){
    if(colSocios.tope != 0){
        for (int i = 0; i < colSocios.tope; i++)
        {
            cout << "+---------Socio " << i << "--------+" << endl;
            cout << "Nombre: " << colSocios.s[i]->getNombre() << endl;
            cout << "CI: " << colSocios.s[i]->getCI() << endl;
        }
        cout << endl;
        system("pause");
    }
    else{
        throw invalid_argument("No hay socios para listar!!\n");
    }
}

//Función para agregar un nuevo Socio al sistema, tomando como parametros el Nombre y CI
void agregarSocio(string ci, string nombre){
    int i = 0;
    //Recorro la estructura de socios para ver que no existan dos iguales
    while (i<colSocios.tope && colSocios.s[i]->getCI() != ci)
    {
        i++;
    }
    //Si llego al final de la estructura creo un nuevo Socio
    if(i == colSocios.tope){
        Socio * s = new Socio(ci,nombre);
        colSocios.s[colSocios.tope] = s;
        colSocios.tope++;
    }
    else{
        throw invalid_argument("Ya existe un Socio con ese nombre\n");
    }
    
}

void menuAgregarClase(){
    system("clear");
    cout << "+--------------------+" << endl;
    cout << "|  3. Agregar Clase  |" << endl;
    cout << "+--------------------+" << endl;
    // Funcion para agregar un nueva Inscripción
    try
    {
        int id, turno, tipo, cntB, enR;
        bool enRambla;
        string nombre;
        Turno t;
        /* code */
        cout << "Id de la Clase: ";
        cin >> id;
        cout << "Nombre de la Clase: ";
        cin >> nombre;
        cout << "Turno?\n1.Manana\n2.Tarde\n3.Noche\nOPCION: ";
        cin >> turno;

        switch (turno)
        {
            case 1:
                t = MANANA;
                break;
        
            case 2:
                t = TARDE;
                break;
            case 3:
                t = NOCHE;
                break;
        }

        cout << "Tipo?\n1.Spinning\n2.Entrenamiento\nOPCION: ";
        cin >> tipo;
        DtSpinning sp;
        DtEntrenamiento en;
        switch (tipo)
        {
            case 1:
                cout << "Cantidad de Bicicletas: ";
                cin >> cntB;
                if(cntB > 50){
                    throw invalid_argument("La cantidad de bicicletas debe ser a lo sumo 50!\n");
                }
                sp = DtSpinning(id,nombre,t,cntB);
                agregarClase(sp);
                break;
            case 2:
                cout << "Es en Rambla? Si = 1 o No = 2: ";
                cin >> enR;
                if(enR == 1){
                    enRambla = true;
                }
                else if(enR == 2){
                    enRambla = false;
                }
                else{
                    throw invalid_argument("Opcion no valida!\n");
                }
                en = DtEntrenamiento(id,nombre,t,enRambla);
                agregarClase(en);
        }
        cout << "Clase agregada correctamente !!" << endl;
        system("pause");
    }
    catch(invalid_argument& e)
    {
        cout << e.what() << endl;
        system("pause");
    }
}

void agregarClase(DtClase& clase){
    try
    {
        int i = 0;
        DtSpinning& sp = dynamic_cast<DtSpinning&>(clase);
        while (i < colClases.tope && colClases.c[i]->getId() != sp.getId())
        {
            i++;
        }
        if(i == colClases.tope){

            Spinning* spinning = new Spinning(sp.getId(),sp.getNombre(),sp.getTurno(),sp.getCantBic());
            colClases.c[colClases.tope]=spinning;
            colClases.tope++;
        }
        else{
            throw invalid_argument("Ya existe una clase Spinning con ese ID!\n");
        }
    }
    catch(bad_cast)
    {
        try{
            int i = 0;
            DtEntrenamiento& en = dynamic_cast<DtEntrenamiento&>(clase);
            while (i < colClases.tope && colClases.c[i]->getId() != en.getId())
            {
                i++;
            }
            if(i == colClases.tope){
                Entrenamiento* entrenamiento= new Entrenamiento(en.getId(),en.getNombre(),en.getTurno(),en.getEnRambla());
                colClases.c[colClases.tope]=entrenamiento;
                colClases.tope++;
            }
            else{
                throw invalid_argument("Ya existe una clase Entrenamiento con ese ID!\n");
            }
        } catch(bad_cast){}
    }
    
}


void menuListarClases(){
    system("clear");
    cout << "+------------------------+" << endl;
    cout << "|  4. Listar las Clases  |" << endl;
    cout << "+------------------------+" << endl;
    // Funcion para listar
    try
    {
        ListadoClases();
    }
    catch(invalid_argument &e)
    {
        cout << e.what() << endl;
        system("pause");
    }
    
}

void ListadoClases(){
    if(colClases.tope != 0){
        for (int i = 0; i < colClases.tope; i++)
        {
            cout << "+---------Clase " << i << "--------+" << endl;
            if(Spinning* sp = dynamic_cast<Spinning*>(colClases.c[i])){
                cout << "Id Clase: " << sp->getId() << endl;
                cout << "Nombre Clase: " << sp->getNombre() << endl;
                if(sp->getTurno() == MANANA){
                    cout << "Turno Clase: MANANA" << endl; 
                } else if(sp->getTurno() == TARDE){
                    cout << "Turno Clase: TARDE" << endl;
                }
                else{
                    cout << "Turno Clase: NOCHE" << endl;
                }
                cout << "Tipo: Spinning" << endl;
            }
            else if(Entrenamiento* en = dynamic_cast<Entrenamiento*>(colClases.c[i])){
                cout << "Id Clase: " << en->getId() << endl;
                cout << "Nombre Clase: " << en->getNombre() << endl;
                if(en->getTurno() == MANANA){
                    cout << "Turno Clase: MANANA" << endl; 
                } else if(en->getTurno() == TARDE){
                    cout << "Turno Clase: TARDE" << endl;
                }
                else{
                    cout << "Turno Clase: NOCHE" << endl;
                }
                cout << "Tipo: Entrenamiento" << endl;
            }
        }
        cout << endl;
        system("pause");
        
    }
    else{
        throw invalid_argument("No hay Clases para listar!\n");
    }
}

void menuAgregarInsc(){
    system("clear");
    cout << "+--------------------------+" << endl;
    cout << "|  5. Agregar Inscripcion  |" << endl;
    cout << "+--------------------------+" << endl;
    // Funcion para agregar un nueva Inscripción
    string ci;
    int id, dia, mes, anio;
    Fecha f;
    cout << "Ingrese la cedula del socio: ";
    cin >> ci;
    cout << "Ingrese el Id de la clase: ";
    cin >> id;
    cout << "Ingrese el dia de la inscipcion: ";
    cin >> dia;
    cout << "Ingrese el mes de la inscipcion: ";
    cin >> mes;
    cout << "Ingrese el anio de la inscipcion: ";
    cin >> anio;
    try
    {
        f = Fecha(dia, mes, anio);
        agregarInscripcion(ci,id,f);
    }
    catch(invalid_argument& e)
    {
        cout << e.what() << endl;
        system("pause");
    }

}

void agregarInscripcion(string ciSocio, int idClase, Fecha fecha){
    int i = 0;
    while (i < colSocios.tope && colSocios.s[i]->getCI() != ciSocio)
    {
        i++;
    }
    int j = 0;
    while (j < colClases.tope && colClases.c[j]->getId() != idClase)
    {
        j++;
    }
    cout << "i:" << i << "j:" << j << endl;
    //Si i = al tope de la coleccion de socios, no existe ese socio
    if(i == colSocios.tope && j == colClases.tope){
        throw invalid_argument("No existen la clase ni el socio indicados!!\n");
    }
    else if(i == colSocios.tope){
        throw invalid_argument("No existe el socio con la cedula indicada!!\n");
    }
    else if(j == colClases.tope){
        throw invalid_argument("No existe la clase con el id indicado!!\n");
    }
    else if(colSocios.s[i]->existeInscripcion(idClase)){
        throw invalid_argument("Este socio ya esta inscripto en esa clase!!\n");
    }
    else{

        /*cout << colClases.c[j]->getId() << endl;
        cout << colSocios.s[i]->getCI() << endl;
        cout << "Cantidad de inscriptos: " << endl;
        cout << colClases.c[j]->getCantSociosClase() << endl;*/

        // Chequear si la clase tiene cupos 
        if(colClases.c[j]->getCantSociosClase() < colClases.c[j]->cupo()){
            Inscripcion * insc = new Inscripcion(fecha, colClases.c[j]);
            Socio * soc = new Socio(colSocios.s[i]->getCI(), colSocios.s[i]->getNombre());
            colSocios.s[i]->agregarInscripcion(insc);
            colClases.c[j]->agregarSocioClase(soc);
            cout << "Inscripcion agregada correctamente" << endl;
            insc->getFecha().toString();
            system("pause");
        }
        else{
            throw invalid_argument("No hay más cupos disponibles para esta clase :(");
        } 
        
        /*cout << colClases.c[j]->getId() << endl;
        cout << colSocios.s[i]->getCI() << endl;
        Inscripcion * insc = new Inscripcion(fecha, colClases.c[j]);
        colSocios.s[i]->agregarInscripcion(insc);
        cout << "Inscripcion agregada correctamente" << endl;
        insc->getFecha().toString();
        system("pause");*/
    }
    //Falta evaluar el tema de los cupos.
}

int main(){
    
    cout << "+-----------------------+" << endl;
    cout << "| Bienvenido al sistema |" << endl;
    cout << "+-----------------------+" << endl;
    system("pause");
    int opcion = 0;
    do{

        system("clear");

        cout << "+--------------------------+" << endl;
        cout << "|   Opciones disponibles   |" << endl;
        cout << "+--------------------------+" << endl;
        cout << "| 1) Agregar un Socio.     |" << endl;
        cout << "| 2) Listar los Socios     |" << endl;
        cout << "| 3) Agregar una Clase     |" << endl;
        cout << "| 4) Listar las Clases     |" << endl;
        cout << "| 5) Agregar Inscripcion   |" << endl;
        cout << "| 6) Listar Inscripciones  |" << endl;
        cout << "| 7) Eliminar Inscripcion  |" << endl;
        cout << "+--------------------------+" << endl;
        cout << "| 8) Salir                 |" << endl;
        cout << "+--------------------------+" << endl;
        cout << "OPCION: ";
        cin >> opcion;
        
        switch (opcion)
        {
            case 1:
                menuAgregarSocio();
                break;
            
            case 2:
                menuListarSocios();
                break;
            case 3:
                menuAgregarClase();
                break;
            case 4: 
                menuListarClases();
                break;
            case 5:
                menuAgregarInsc();
                break;
            case 6:
                system("clear");
                cout << "+---------------------------+" << endl;
                cout << "|  6. Listar Inscripciones  |" << endl;
                cout << "+---------------------------+" << endl;
                // Funcion para agregar un nueva Inscripción
                system("pause");
                break;
            case 7:
                system("clear");
                cout << "+---------------------------+" << endl;
                cout << "|  7. Eliminar Inscripcion  |" << endl;
                cout << "+---------------------------+" << endl;
                // Funcion para agregar un nueva Inscripción
                system("pause");
                break;
            case 8:
                system("clear");
                cout << "+------------+" << endl;
                cout << "|  8. Salir  |" << endl;
                cout << "+------------+" << endl;
                break;
            default:
                cout << "+---------------------------------------+" << endl;
                cout << "|           Opcion Incorrecta           |" << endl;
                cout << "+---------------------------------------+" << endl;
                opcion = 0;
                system("pause");
                break;
        }

    } while(opcion != 8);
    return 1;
}

