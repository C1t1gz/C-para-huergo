#include "taller.h"

// ACLARACION: Todas las funciones devuelven algo del tipo necesario, esto es 
// para que no explote cuando vayan compilando (y de paso para que no se olviden
//de devolver el tipo correcto)

// En algunos casos hay funciones de stl de c++ que ya resuelven cada ejercicio.
// Obviamente no vale utilizarlas para resolver

// En algunos casos es posible usar objetos iteradores que simplifican algunas
// operaciones. Es posible utilizarlos pero consultenme para chequear 

// Ejercicio 0
// Dado un vector v, devuelve el valor maximo encontrado.
// HINT: Para saber la cantidad de elementos de un vector, usar v.size()

int mayor(const vector<int>& v)
{
	int mayor = 0;
	for (int i = 0 ; i < v.size(); i++)
	{
			if (v[i] > mayor)
			{
				mayor = v[i];	
			}
		
	}
	return mayor;
}

// Ejercicio 1 
// Dado un vector v, devuelve el reverso.
// Se puede hacer en una línea usando iteradores (en este caso no vale usarlos)

vector<int> reverso(const vector<int>& v)
{
	vector<int> reverso(v.size()-1);
	int pepe = 0;

	for (int i = v.size()-1; i >= 0; i--)
	{
		reverso[pepe] = v[i];
		pepe++;	
	}
	return reverso;
}

// Ejercicio 2
// Dado un vector v y un entero k, rotar k posiciones los elementos de v.
// [1,2,3,4,5,6] rotado 2, deberia dar [3,4,5,6,1,2].
vector<int> rotar(const vector<int>& v, int k)
{
	vector<int> rotado(v.size());
	for (int i = 0; i < v.size(); i++)
	{
		rotado[i] = v[i];
		
	}
	for (int j = 0; j < k; j++)
	{
		rotado.push_back(v[j]);
		rotado.erase(rotado.begin());
	}
	return rotado;
}

// Ejercicio 3
// Dado un vector v, hacer una función que lo modifique sumandole uno a todos 
// sus elementos. RECORDAR determinar la cabecera de la funcion y definir
// la misma en  taller.h !!

// COMPLETAR

void sumar(vector<int>& v)
{
	for (int i : v)
	{
		v[i] = v[i] + 1;
	}
}

// Ejercicio 4
// Dado un vector, dice si esta ordenado crecientemente o decrecientemente
bool estaOrdenado(const vector<int>& v)
{
	int aux = 0;
	bool pepe;

	for(int i = 0; i < v.size(); i++)
	{
		aux = v[i];
		for (int j = i+1; j < v.size(); j++)
		{
			if (aux >= v[j])
			{
				return false;
			}
			else
			{
				pepe = true;
			}	
		}
	}	
	if (pepe == true)
	{
		return true;
	}	
	return false;
}

// Ejercicio 5
// Dado un vector de enteros, lo muestra por la salida estándar (consola)
// Ej: si el vector es <1, 2, 5, 65> se debe mostrar en pantalla [1, 2, 5, 65]

// HINT: Esta función es general, out es del tipo de dato ostream. 
// Eso significa que el parametro out puede ser cout o bien podrías ser un 
// archivo de texto instancia de ofstream (que hereda de ostream).
// En cualquier caso puedo usar el operador << para escribir.

void mostrarVector(const vector<int>& v, ostream& out)
{
	string string_a_mostrar = "";
	
	for (int i : v)
	{
		string_a_mostrar.append(to_string(i));
		string_a_mostrar.append(", ");
		
	
	}
	string_a_mostrar = string_a_mostrar.substr(0, string_a_mostrar.length() - 2);


	out << string_a_mostrar << endl;

	return;
}

// Ejercicio 6 
// Dado un vector de enteros y el nombre de un archivo de salida,
// escribe al vector en el archivo. Ejemplo: si el vector es <1, 2, 5, 65>
// el archivo contiene [1, 2, 5, 65]
// Ojo con el constructor de ofstream. 
// Es importante hacer la conversion del string a char* usando c_str().
// HINT: Reutilizar la función anterior!

void guardarVector(const vector<int>& v, string nombreArchivo)
{
	string string_a_mostrar = "";
	
	for (int i : v)
	{
		string_a_mostrar.append(to_string(i));
		string_a_mostrar.append(", ");
	}

	string_a_mostrar = string_a_mostrar.substr(0, string_a_mostrar.length() - 2);

   	ofstream file(nombreArchivo.c_str()); 
   	if(file.is_open())
   	{
		file << string_a_mostrar;   	
		file.close();
		
   	}
   	return;
}


//Ejercicio 7 
// Dado un archivo que contiene una lista de números, contar la cantidad de
// apariciones de cada uno y escribir nombreArchivoOut con una linea por cada
// numero encontrado, un espacio y la cantidad de apariciones.
// El parametro max indica el número más grande que puede aparecer en el archivo
// Ejemplo: si el 1 aparece 44 veces y el 2 20 veces (y no hay otros numeros)
// en la salida deberia haber dos lineas, "1 44" y la segunda "2 20"


void cantidadApariciones(string nombreArchivo, string nombreArchivoOut,int max)
{
	// Abro archivo para lectura
	ifstream fileIn(nombreArchivo.c_str());
	string line;
	vector<int> numeros(10, 0);
	while (getline(fileIn, line)) {
        // Lo vamos imprimiendo}

		for (int ch1 = 0; ch1 < max; ch1++){
			size_t count = 0;

			for (char i : line){
				std::string tmp = std::to_string(ch1);
    			char const *ch = tmp.c_str();
				if (i == *ch){
					count++;
				}
			}
			numeros[ch1] = numeros[ch1] + count;
			
		}
    }
	// Abro archivo para escriture
    ofstream fileOut(nombreArchivoOut.c_str());
	for(int i = 0; i< numeros.size();i++){
		if (numeros[i] != 0){
			fileOut << i;
			fileOut << " ";
			fileOut << numeros[i];
			fileOut<< "\n";
		}
	}
    // COMPLETAR
    
	return;
}


//Ejercicio 8 (opcional)
//Dado el nombre de archivo, lo filtra y devuelve los palindromos en el archivo
//  salida, uno por linea.
void palindromos(string nombreArchivo, string nombreArchivoOut)
{
	return;	
}
