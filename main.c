/*
AUTOR: Dominguez Moran Joaquín, García Ibañez Diego, Rosas Sánchez Paloma. Agosto 2017.
VERSIÓN: 1.0.

DESCRIPCIÓN: Programa que valida y evalua una expresión infija.

OBSERVACIONES: El programa utiliza 20 funciones para realizar las operaciones que poco a poco modifican la matriz original.
El formato de los archivos debe ser el siguiente: 
														palabra1: definicion1 \n
														palabra2: definicion2 \n
														.
														.
														.
														palabraN: defincionN \n

COMPILACIÓN: 
			Windows: gcc main.c Lista.c
			Linux: gcc main.c Lista.c

EJECUCIÓN: 
			Windows: a.exe
			Linux: ./a.out
*/  
    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "TADLista.h"
  
#define TAMHASH 97
char nombreArchivo[50];
bool archivoCargado = false;
  
/*
**int mod (int a, int b);**
DESCRIPCIÓN: Función que obtiene el modulo de dos numeros positivo.
ENTRADA: Dos numeros enteros positivos.
SALIDA: Un valor numerico positivo que es el modulo.
*/ 
  int
mod (int a, int b)
{
  int r = a % b;
  if (r < 0)
    r += b;
  return r;
}

  
/*
**int hash (char *key);**
DESCRIPCIÓN: Función Hash en la que se emplea la primera letra de la palabra para generar el valor de hash.
ENTRADA: Un puntero a un arreglo de char.
SALIDA: Un clave hash.
*/ 
   int
hash (char *key) 
{
  return mod (key[0] - 'A', TAMHASH);
 }

  
/*
**int hash (char *key);**
DESCRIPCIÓN: Función Hash en la que emplea  dos multiplicaciones de dos numeros primos para  generar  el valor  de  hash,
ENTRADA: Un puntero a un arreglo de char.
SALIDA: Un clave hash.
*/ 
   
/*int hash(char *key )
{ 
	int a = 63689;
	int b = 378551;
	int valorHash = 0;
	int i = 0;
	for(i = 0;*key; key++, i++)
	{ 
		valorHash = valorHash * a + (*key);
		a= a * b;
	}
	return mod(valorHash,TAMHASH);
}

/*

/*
**voidstrscan (char *s, int lim)**
DESCRIPCIÓN: Lee una cadena uno a uno.
ENTRADA: Un puntero de un arreglo de caracteres y un numero de elementos a leer.
SALIDA: 
*/ 
 void 
strscan (char *s, int lim)
{
  int i = 0, c = '0';
   while (i < lim && (c = getchar ()) != '\n')
    
    {
      *(s + i) = c;
      i++;
    }
   *(s + i) = '\0';
}

 
/*
**void showCollisions (lista *t)**
DESCRIPCIÓN: Muestra las colisiones.
ENTRADA: Una lista
SALIDA: 
*/ 
  void
showCollisions (lista * t) 
{
  int i, j, l = 0;
  int k = 0;
  nodo * ptr;
   puts ("\tEstadisticas\t");
  for (i = 0; i < TAMHASH; i++)
    {
      ptr = t[i].frente;
      j = 0;
      while (ptr)
	{
	  j++;
	  ptr = ptr->siguiente;
	}
      printf ("%d colisiones en %d.", j, k);
      k++;
      l++;
      if (l % 3 == 0)
	{
	  printf ("\n");
	  l = 0;
	}
      else
	printf ("\t");
    }
  printf ("\n");
}

 
/*
**void fillElement (elemento *e, char nombre[], char definicion[];**
DESCRIPCIÓN: Asigana a un elemento de la lista una palbra y su definicion.
ENTRADA: Un elemento, una cadena de caracteres con la palabra y una cadena de caracteres con la definicion
SALIDA: 
*/ 
void 
fillElement (elemento * e, char nombre[], char definicion[])
{
  strncpy (e->nombre, nombre, TAMNOM);
  strncpy (e->definicion, definicion, TAMDEF);
}  

/*
**int insertAlpha (lista *t, elemento e);**
DESCRIPCIÓN: Inserta de forma alfabetica en un arreglo de listas un elemento que contenga la palabra
ENTRADA: Un arreglo de listas y un elemento e.
SALIDA: Un valor numero que representa la posicion de inserccion.
*/ 
  int
insertAlpha (lista * t, elemento e)
{
  int i = 0, indice = hash (e.nombre);
  lista * subl = &t[indice];	// Sublista
  nodo *pos = t[indice].frente;
   while (i < Size (subl) && strncmp (e.nombre, pos->e.nombre, TAMNOM) > 0)	//Comparación de cadenas
    {
      pos = Following (subl, pos);
      i++;
    }
  if (pos != NULL)
    InsertBefore (subl, e, pos);
  
  else
    AddEnd (subl, e);
   return i;
}

 
/*
**void loadFile (lista *t);**
DESCRIPCIÓN: Carga el archivo y va llenando la tabla hash con base al mismo
ENTRADA:Un arreglo de listas.
SALIDA: 
*/ 
  void
loadFile (lista * t) 
{
  int c = 'n', i = 0;
  char *nombre, *def;
  elemento e;
   
    /*      Esta condicion sirve para saber si el usuario desea cargar otro archivo.        */ 
    if (archivoCargado)
    {
      char ans[9];
      printf ("\nParece ser que el archivo %s ya ha sido cargado\n",
	       nombreArchivo);
      printf ("Desea cargar otro? (s / n): ");
      fgets (ans, 9, stdin);
      if (ans[0] == 's' || ans[0] == 'S')
	{
	  for (i = 0; i < TAMHASH; i++)
	    Destroy (&t[i]);
	  
	    /*      Importante la declaracion lista *t, no basta con t = ...        */ 
	    lista * t = (lista *) calloc (TAMHASH, sizeof (lista));
	}
      else
	return;
    }
   printf ("Nombre del archivo (.txt): ");
  strscan (nombreArchivo, 40);
  sprintf (nombreArchivo, "%s.txt", nombreArchivo);
  FILE * fp = fopen (nombreArchivo, "rb");
   if (!fp)
    {
      printf ("El archivo %s no existe. \n", nombreArchivo);
      return;
    }
   
    /*      Recorremos el archivo con un ciclo while, mientras que c no sea EOF 
       (es decir, no lleguemos al final del archivo) vamos recorriendo el 
       archivo, caracter a caracter y vamos guardando en una cadena su nombre 
       y definicion por separado.   */ 
     while (!feof (fp))
    
    {
      nombre = (char *) calloc (TAMNOM, sizeof (char));
      def = (char *) calloc (TAMDEF, sizeof (char));
      i = 0;
      
	/*      Puesto que el archivo tiene el formato:
	   Palabra: definicion. \n
	   se sabe que la palabra abarca desde su primera letra hasta los dos puntos.   */ 
	while (i < TAMNOM && (c = fgetc (fp)) != ':' && c != '\n' && c != EOF)
	nombre[i++] = c;
      if (i > 0)
	{
	  nombre[i++] = '\0';
	  c = fgetc (fp);
	  i = 0;
	  
	    /*      De manera similar, la definicion abarca desde su primera letra hasta el salto 
	     *      de linea.       */ 
	    while (i < TAMDEF && (c = fgetc (fp)) != '\n' && c != EOF)
	    def[i++] = c;
	  def[i++] = '\0';
	  
	    /*      Insertamos la palabra a la tabla hash.  */ 
	    fillElement (&e, nombre, def);
	  
	    //AddEnd (&t[hash (nombre)], e);
	    insertAlpha (t, e);
	}
    }
  archivoCargado = true;
  fclose (fp);
  showCollisions (t);
}

  
/*
**void printAvailable (lista *l);**
DESCRIPCIÓN: Imprime todas las palabras de un archivo
ENTRADA:Una lista.
SALIDA: 
*/ 
void 
printAvailable (lista * l)
{
  bool b = false;
  int i = 0;
   
    /*      Se valida que exista una palabra        */ 
    for (i = 0; i < TAMHASH; i++)
    if (l[i].frente)
      {
	b = true;
	break;
      }
   if (b)
    {
      int i = 0, j = 0, tab = 0;
      nodo * ptr = NULL;
       for (i = 0; i < TAMHASH; i++)
	{
	  ptr = l[i].frente;
	   
	    /*      Imprimimos la palabra, si existe almenos una palabra 
	       con un caracter en la fila i, se entra al bucle, si no
	       no entra, asi nos aseguramos de evadir el error SIGSEGV.     */ 
	    tab = 0;
	  while (ptr)
	    {
	      printf ("%s \t", ptr->e.nombre);
	      ptr = ptr->siguiente;
	      tab++;
	      if (tab % 4 == 0)
		{
		  printf ("\n");
		  tab = 0;
		}
	    }
	  printf ("\n \n");
	}
    }
  
  else
    puts ("No se ha cargado ningun archivo");
}

 
/*
**void showDefinition (lista *t);**
DESCRIPCIÓN: Muestra la definicion de una palabra
ENTRADA:Una arreglo de listas.
SALIDA: 
*/ 
void 
showDefinition (lista * t)
{
  char comp[99];
  int indice = 0, i = 0, contador = 0;
  nodo * ptr = NULL;
   printf ("Escriba la palabra a buscar: ");
  strscan (comp, 99);
   
    /*      Obtenemos el indice correspondiente a la palabra.       */ 
    indice = hash (comp);
  ptr = t[indice].frente;
   
    /*      Se busca la palabra, si existe se imprimira la palabra
       con su correspondiente definicion, si no existe se muestra por 
       pantalla que no existe la palabra buscada.   */ 
    while (ptr)
    {
      if (!strcmp (comp, ptr->e.nombre))
	{
	  printf ("%s: %s \n", ptr->e.nombre, ptr->e.definicion);
	  printf ("Iteraciones para encontrar la palabra: %d. \n",
		   contador++);
	  return;
	}
      ptr = ptr->siguiente;
      contador++;
    }
   printf ("La palabra \"%s\" no se encuentra en el diccionario. \n", comp);
}

 
/*
**void searchLetter (lista *t);**
DESCRIPCIÓN: Imprime todas las palabras disponibles con la consonante propuesta.
ENTRADA:Una arreglo de listas.
SALIDA: 
*/ 
void 
searchLetter (lista * t)
{
  char ans[3];
  int i = 0, contador = 0;
   printf ("Letra (mayus): ");
  fgets (ans, 3, stdin);
   i = hash (ans);
   if (t[i].frente)
    {
      nodo * ptr = t[i].frente;
       while (ptr)
	{
	  printf ("%d.- %s \n", contador + 1, ptr->e.nombre);
	  ptr = ptr->siguiente;
	  contador++;
	}
    }
  
  else
    puts ("No se encuentra ninguna palabra con esa letra");
}

 
/*
**void addWord (lista *l);**
DESCRIPCIÓN: Agregamos una palabra, tanto a el archivo como a la lista.
ENTRADA:Una lista.
SALIDA: 
*/ 
void 
addWord (lista * l)
{
  char nombre[TAMNOM], definicion[TAMDEF], parrafo[TAMNOM + TAMDEF + 10];
  elemento e;
  int iteraciones;
  FILE * fp = fopen (nombreArchivo, "ab+");
  if (!fp)
    {
      printf ("\n El archivo %s no existe. \n", nombreArchivo);
      return;
    }
  printf ("Palabra nueva: ");
  strscan (nombre, TAMNOM);
   printf ("Definicion: ");
  strscan (definicion, TAMDEF);
   
    /*      Hacemos que el primer caracter sea mayus. si la primera letra es alfabetica.    */ 
    nombre[0] = toupper (nombre[0]);
  sprintf (parrafo, "%s: %s", nombre, definicion);
  
    /*      Escribimos nuestra palabra al final de nuestro archivo, si cambiar la palabra 
       anterior.    */ 
    fprintf (fp, "\n%s", parrafo);
  fillElement (&e, nombre, definicion);
  
    //AddEnd (&l[hash (nombre)], e);
    iteraciones = insertAlpha (l, e);
  printf ("Se usaron %d iteraciones. \n", iteraciones);
   fclose (fp);
}

 
/*
**bool existWord (lista *t, char s[]);**
DESCRIPCIÓN: Verifica si exste una palabra
ENTRADA:Una lista y un cadena de caracteres
SALIDA: 
*/ 
  bool  existWord (lista * t, char s[])
{
  int indice = 0;
   
    /*      Se obtiene el indice de s[0]. Se sabe que existe un valor correspondiente puesto que ya paso
       la condicion anterior.       */ 
    indice = hash (s);
  nodo * ptr = t[indice].frente;
   
    /*Se busca en la fila i-esima de nuestra tabla, si existe, retornamos true      */ 
    while (ptr)
    {
      if (!strncmp (s, ptr->e.nombre, TAMNOM))
	return true;
      ptr = ptr->siguiente;
    }
   return false;
}

 
/*
**void deleteWord (lista *t)**
DESCRIPCIÓN: Elmina una palabra
ENTRADA:Un arreglo de lsitas
SALIDA: 
*/ 
void 
deleteWord (lista * t)
{
  char pbuscada[TAMNOM];
   printf ("\nIngrese la palabra a borrar: ");
  strscan (pbuscada, TAMNOM);
   
    /*      Comprobamos que exista la palabra y, si existe, procedemos borramos y 
       escribimos el archivo, saltandonos la palabra no deseada.    */ 
    if (existWord (t, pbuscada))
    {
      FILE * fp = fopen (nombreArchivo, "wb");
      nodo * ptr = NULL;
      int i = 0;
      for (i = 0; i < TAMHASH; i++)
	{
	  ptr = t[i].frente;
	  while (ptr)
	    {
	      if (strncmp (ptr->e.nombre, pbuscada, TAMNOM))
		fprintf (fp, "%s: %s\n", ptr->e.nombre, ptr->e.definicion);
	      
	      else
		Remove (&t[hash (ptr->e.nombre)], ptr);
	      ptr = ptr->siguiente;
	    }
	}
      fclose (fp);
    }
  
  else
    puts ("No se encuentra la palabra ingresada.");
}

 
/*
**changeDefinition (lista *t) **
DESCRIPCIÓN: Cambia la definicion de una palabra
ENTRADA:Un arreglo de lsitas
SALIDA: 
*/ 
void 
changeDefinition (lista * t)
{
  char nuevaDef[TAMDEF], pBuscada[TAMNOM];
  int i = 0, contador = 0;
   printf ("\nIngrese la palabra a cambiar: ");
  strscan (pBuscada, TAMNOM);
   
    /*      Comprobamos si existe la palabra        */ 
    if (existWord (t, pBuscada))
    {
      FILE * fp = fopen (nombreArchivo, "wb");
      if (!fp)
	{
	  printf ("\nEl archivo %s no existe. \n", nombreArchivo);
	  return;
	}
      nodo * ptr;
      
	/*      Obtenemos la nueva definicion.  */ 
	printf ("Nueva definicion: ");
      strscan (nuevaDef, TAMDEF);
       
	/*      Recorremos las palabras y reescribimos todo el archivo, cuando nos 
	   encontremos con la palabra a cambiar, escribimos la nueva palabra y nos
	   saltamos la sobreescritura de la palabra anterior, asi como su definicion. */ 
	for (i = 0; i < TAMHASH; i++)
	{
	  ptr = t[i].frente;
	  while (ptr)
	    {
	      if (!strncmp (pBuscada, ptr->e.nombre, TAMNOM))
		{
		  sprintf (ptr->e.definicion, "%s", nuevaDef);
		  fprintf (fp, "%s: %s\n", pBuscada, nuevaDef);
		  strncpy (ptr->e.definicion, nuevaDef, TAMDEF);
		  printf
		    ("\nSe realizaron %d iteraciones para localizar la palabra",
		     contador + 1);
		}
	      else
		fprintf (fp, "%s: %s\n", ptr->e.nombre, ptr->e.definicion);
	      ptr = ptr->siguiente;
	      contador++;
	    }
	}
       fclose (fp);
    }
  
  else
    printf ("La palabra \"%s\" no se encuentra", pBuscada);
  printf ("\n");
}

 
/*
**void exportList (lista *t) **
DESCRIPCIÓN: Exporta las palabras diccionario con el nombre que el usuario desee
ENTRADA:Un arreglo de listas
SALIDA: 
*/ 
void 
exportList (lista * t)
{
  int i, cont = 1;
  nodo * ptr = NULL;
  char nombre[50];
   printf ("\nNombre del archivo (.txt): ");
  strscan (nombre, 40);
  sprintf (nombre, "%s.txt", nombre);
   FILE * fp = fopen (nombre, "wb");
  if (!fp)
    {
      printf ("\nEl archivo %s no existe. \n", nombre);
      return;
    }
   for (i = 0; i < TAMHASH; i++)
    {
      ptr = t[i].frente;
      while (ptr)
	{
	  fprintf (fp, "%s: %s\n", ptr->e.nombre, ptr->e.definicion);
	  ptr = ptr->siguiente;
	  cont++;
	}
    }
  printf ("Se exportaron %d palabras a %s. \n", cont, nombre);
   fclose (fp);
}

  
/*
**void exportDefinition  (lista *t) **
DESCRIPCIÓN: Exporta una palabra coon su defnicion diccionario con el nombre que el usuario desee
ENTRADA:Un arreglo de listas
SALIDA: 
*/ 
void 
exportDefinition (lista * t)
{
  char nombre[TAMNOM];
   printf ("\nNombre de la palabra a exportar: ");
  strscan (nombre, TAMNOM);
   if (existWord (t, nombre))
    {
      char nombreArchivoNuevo[50];
      nodo * ptr = t[hash (nombre)].frente;
      int cont = 1;
       printf ("Nombre del archivo (.txt): ");
      strscan (nombreArchivoNuevo, 40);
      sprintf (nombreArchivoNuevo, "%s.txt", nombreArchivoNuevo);
      FILE * fp = fopen (nombreArchivoNuevo, "wb");
      if (!fp)
	{
	  printf ("\nEl archivo %s no existe.\n", nombreArchivoNuevo);
	  return;
	}
      while (ptr)
	{
	  if (!strncmp (nombre, ptr->e.nombre, TAMNOM))
	    {
	      fprintf (fp, "%s: %s", ptr->e.nombre, ptr->e.definicion);
	      puts ("Palabra exportada exitosamente :D. ");
	      printf
		("Se requirieron %d iteraciones para localizar la palabra %s. \n",
		 cont, nombre);
	      break;
	    }
	  ptr = ptr->siguiente;
	  cont++;
	}
      fclose (fp);
    }
  else
    printf ("la palabra %s no se encuentra en el diccionario. ", nombre);
}

 
/*
**void searchSubstring (lista *t); **
DESCRIPCIÓN: Busca todas las palabras disponibles, con su respectiva definicion que contengan una subcadena dada (si existe).
ENTRADA:Un arreglo de listas
SALIDA: 
*/ 
void 
searchSubstring (lista * t)
{
  char substr[TAMNOM];
  int i, n, N, cont = 1;
  bool hayUna = false;
  nodo * ptr = NULL;
   printf ("\nEscriba la subcadena: ");
  strscan (substr, TAMNOM);
  n = strlen (substr);
   
    /*      Con un bucle recorremos las 26 listas que como maximo puede tener la tabla.     */ 
    for (i = 0; i < TAMHASH; i++)
    {
      ptr = t[i].frente;
      while (ptr)
	{
	  N = strlen (ptr->e.nombre);
	  if (n <= N)
	    
	      /*      La funcion char *strstr (char *A, char *B) retorna true si la subcadena B esta en A     */ 
	      if (strstr (ptr->e.nombre, substr))
	      {
		printf ("%s: %s \n", ptr->e.nombre, ptr->e.definicion);
		printf ("Iteraciones para localizar la subcadena %s: %d \n",
			 substr, cont);
		hayUna = 1;
	      }
	  ptr = ptr->siguiente;
	  cont++;
	}
    }
  if (!hayUna)
    printf ("No se encuentra ninguna palabra con la subcadena %s. ", substr);
}

 
/*
**void searchSubstring (lista *t); **
DESCRIPCIÓN: Pregunta alguna frase y muestra las palabras disponibles en el diccionario tales que su definicion contengan a la frase.
ENTRADA:Un arreglo de listas
SALIDA: 
*/ 
void 
searchSentence (lista * t)
{
  char frase[TAMNOM];
  nodo * ptr;
  int i, j, noHay = true, cont = 1;
   printf ("\nFrase: ");
  strscan (frase, TAMNOM);
  for (i = 0; i < TAMHASH; i++)
    {
      ptr = t[i].frente;
      while (ptr)
	{
	  if (strstr (ptr->e.definicion, frase))
	    {
	      printf ("%s: %s \n", ptr->e.nombre, ptr->e.definicion);
	      printf ("Encontrada despues de %d pasos \n", cont);
	      noHay = 0;
	    }
	  ptr = ptr->siguiente;
	  cont++;
	}
    }
  if (noHay)
    printf ("La frase \" %s \" no se encuentra en el diccionario.", frase);
}

 
/*
**void wait();**
DESCRIPCIÓN: Función que detiene el programa hasta que el usurio presione Enter
ENTRADA: 
SALIDA:
*/ 
  void
wait () 
{
  printf ("Presiona ENTER para continuar.\n");
  while (getchar () != '\n');
}

  
/*
**void menu (lista *dicc);**
DESCRIPCIÓN: Función que presenta las opciones del programa
ENTRADA: Una lista.
SALIDA:
*/ 
  void
menu (lista * dicc) 
{
  char aux[9];
  int opcion;
   
  do
    {
      puts ("\nDiccionario Hash \n");
       puts ("0.-  Mostrar estadisticas \n");
       puts ("1.-  Cargar archivo y sus definiciones ");
      puts ("2.-  Agregar una palabra y su definicion");
      puts ("3.-  Mostrar la definicion de una palabra");
      puts ("4.-  Modificar una palabra");
      puts ("5.-  Eliminar una palabra");
       puts ("\nOpciones de busqueda ");
      puts ("6.-  Buscar por subcadena ");
      puts ("7.-  Buscar palabras por su primer letra ");
      puts ("8.-  Buscar por una frase ");
       puts ("\nOpciones de exportacion ");
      puts ("9.-  Exportar lista a un archivo de texto ");
      puts ("10.- Exportar una palabra con su definicion a un archivo ");
       puts ("\nOpciones extra ");
      puts ("11.- Imprimir palabras disponibles ");
       puts ("\n12.- Salir");
       printf ("\nOpcion: ");
      fgets (aux, 9, stdin);
      sscanf (aux, "%d", &opcion);
       switch (opcion)
	{
	case 0:
	  showCollisions (dicc);
	  break;
	case 1:
	  loadFile (dicc);
	  break;
	case 2:
	  addWord (dicc);
	  break;
	case 3:
	  showDefinition (dicc);
	  break;
	case 4:
	  changeDefinition (dicc);
	  break;
	case 5:
	  deleteWord (dicc);
	  break;
	case 6:
	  searchSubstring (dicc);
	  break;
	case 7:
	  searchLetter (dicc);
	  break;
	case 8:
	  searchSentence (dicc);
	  break;
	case 9:
	  exportList (dicc);
	  break;
	case 10:
	  exportDefinition (dicc);
	  break;
	case 11:
	  printAvailable (dicc);
	  break;
	case 12:
	  puts ("By :D");
	default:
	  puts ("Opcion no valida");
	  break;
	}
      wait ();
    }
   while (opcion != 12);
}

 
/*	Raiz del programa	*/ 
int 
main (int argc, char *argv[])
{
  lista * dicc = (lista *) calloc (TAMHASH, sizeof (lista));
  int i;
   menu (dicc);
  for (i = 0; i < TAMHASH; i++)
    Destroy (&dicc[i]);
   return 0;
}


