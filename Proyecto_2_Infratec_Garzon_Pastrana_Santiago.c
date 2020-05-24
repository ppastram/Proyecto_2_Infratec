/*
PROYECTO 1 FUNDAMENTOS DE INFRAESTRUCTURA TECNOLOGICA - 202020
Juan Pablo Garzón - 201912575
Pablo Pastrana - 201822920
Juan Andrés Santiago - 201821950
*/

#define _CRT_SECURE_NO_DEPRECATE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//-- Definicion de la estructura para los datos del archivo de entrada y el de salida
typedef struct datos
{
	int tamanio;
	unsigned char *informacion;
} Datos;


//-- Prototipos de las funciones
int readFile(Datos * archivo, char *);
void writeFile(Datos * archivoEnBinario, char *);
void convertirABinario(Datos * archivo, Datos * archivoEnBinario);


//-- Funciones

// Esta funcion se encarga de abrir un datos y leerlo en el vector informacion.
// Retorna el numero de bytes leidos.
// No hay que completar nada en esta funcion.
int readFile(Datos * archivo, char * nombreArchivo)
{
	FILE *file;
	int n;

	file = fopen(nombreArchivo, "rb");

	if (!file)
	{
		printf("No se pudo abrir el archivo para leer: %s\n", nombreArchivo);
        system("PAUSE");
		exit(EXIT_FAILURE);
	}
	fseek(file, 0, SEEK_END);
	n = ftell(file);
	fseek(file, 0, SEEK_SET);

	archivo->tamanio = n;
	archivo->informacion = (unsigned char *)calloc(n, sizeof(unsigned char));

	fread(archivo->informacion, sizeof(unsigned char), n, file);

	fclose(file);

	return n;
}


// Esta funcion se encarga de escribir un datos a partir del vector datos.
// El numero de bytes que se deben escribir viene en el parametro n.
// No hay que completar nada en esta funcion.
void writeFile(Datos * archivoEnOctal, char *nombreArchivo)
{
	FILE *file;

	file = fopen(nombreArchivo, "wb");

	if (!file) {
		printf("No se pudo abrir el archivo para escribir: %s\n", nombreArchivo);
        system("PAUSE");
		exit(EXIT_FAILURE);
	}

	fwrite(archivoEnOctal->informacion, sizeof(char), archivoEnOctal->tamanio, file);

	fclose(file);
}


// Esta funcion se encarga de convertir a binario cada uno de los caracteres que se
// encuentran en la estructura datosOct->informacion y asignar los nuevos valores a la estructura datosBin->informacion.
// Deben desarrollar esta funcion en su totalidad.
void convertirABinario(Datos * datosOct, Datos * datosBin)
{
	// TODO: Esta funciÃ³n se debe realizar completamente en ensamblador dentro de la etiqueta __asm.
    // SE PUEDEN USAR VARIABLES SIMBÃ“LICAS (no es obligatorio acceder a las variables por pila).
    __asm
    {
         push ebp
         mov ebp, esp
         push esi
         push edi
         mov DWORD PTR [ebp-64], 0
         mov DWORD PTR [ebp-60], 1
         mov DWORD PTR [ebp-56], 10
         mov DWORD PTR [ebp-52], 11
         mov DWORD PTR [ebp-48], 100
         mov DWORD PTR [ebp-44], 101
         mov DWORD PTR [ebp-40], 110
         mov DWORD PTR [ebp-36], 111
         mov [ebp-8], [ebp-76]
         mov [ebp-16], 1

         mov esi, [ebp-76]
         while1:
         cmp [esi], 0
         jne finwhile
            mov eax, [esi]
            mov edx, 0
            mov ecx, 10
            idiv ecx
            mov [ebp-20], edx

            mov eax, [esi]
            mov edx, 0      
            mov ecx, 10
            div ecx  
            push eax      
            mov [esi], eax 


            mov ecx, [ebp-20]
            cdqe
            mov ecx, [ebp-64+eax*4]
            cdqe
            imul eax, [ebp-16]
            add [rbp-8], eax 
            mov rax, QWORD PTR [rbp-16]
            imul eax, eax, 1000
            mov [ebp-16], eax
        
        finwhile:
        mov eax, [ebp-8]
        pop ebp
        ret
    }
}

//-- Funcion main de la aplicacion
// No hay que completar nada en esta funcion.
int main()
{
	// Mensaje inicial
	printf("PROYECTO 1 - INFRATEC (ISIS-1304)");

	// Declaracion de todas las variables necesarias.
	int tamanio;
	int tamanioRepBinario;
	char nombreArchivo[200];
	char nombreArchivoBinario[200];
	Datos * archivoOctal = (Datos *)malloc(sizeof(Datos));
	Datos * archivoEnBinario = (Datos *)malloc(sizeof(Datos));

	printf("\n\nIngrese el nombre del archivo a leer (incluya el formato. i.e. archivo.txt): \n");
	scanf("%s", nombreArchivo);
	tamanio = readFile(archivoOctal, nombreArchivo);
	printf("\nEl tamanio del archivo es de %d bytes\n", tamanio);
	tamanioRepBinario = ((tamanio * 3) / 8) + (((tamanio*3) % 8 == 0)? 0 : 1);
	archivoEnBinario->informacion = (unsigned char *)calloc(tamanioRepBinario, sizeof(unsigned char));
	archivoEnBinario->tamanio = tamanioRepBinario;
	printf("\nIngrese el nombre del archivo para guardar la representacion en octales del archivo origen (incluya el .txt): \n");
	scanf("%s", nombreArchivoBinario);
	convertirABinario(archivoOctal, archivoEnBinario);
	writeFile(archivoEnBinario, nombreArchivoBinario);
	printf("\nEl archivo se transformo en su representacion a octal exitosamente!\n\n");
	printf("Revisa el archivo con nombre '%s' para ver el resultado!\n", nombreArchivoBinario);

	// Terminar
	system("PAUSE");
	return 0;
}
