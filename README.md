# Anotaciones de Tp 4

## Punto 2
*Empece haciendo punteros cuando en el campo no lo sugería, por lo tanto de recomendación general es respectar con la naturaleza que fue asignado ese "producto" que llevo dentro del nodo con su enlace*

**Las listas se inicializan afuera de los whiles por que si no siempre es pisada por null, entonces no sirve porque no se llena con nuevos datos dentro del bucle**

*Usualmente cuando se usa el puntero en la estructura ahi si trato de poner que lo que se retorne son punteros de tipo nodo pero si no trabajo todo dentro del mismo tipo de dato. Lo que acabo de decir incluye dentro de las funciones definir mallocs que se usaran como yo use Tnueva.*

_static int proximoID: Al ser static, la primera vez vale 1000, la segunda 1001, y así sucesivamente sin necesidad de pasarle parámetros extras._

**strcmp es una función de la biblioteca estándar de C (<string.h>) que compara dos cadenas de caracteres (strings) carácter por carácter, basándose en sus valores ASCII. Devuelve un entero: 0 si son iguales, un valor negativo si la primera cadena es menor, o positivo si es mayor**

## anotaciones 03/05/26
*No eliminar un nodo luego de haberlo cambiado de lugar de una lista a otra(de pendientes a realizadas), pero por una cuestión de que si se elimina es de forma definitiva y la lista nueva que contiene ese valor accede a valor basura. Solo eliminar cuando no se usa en ninguna lista, no cuando el valor sigue "viviendo" en una.*

**La lista que paso como parámetro para sacar al nodo es la que ya estaba llena, no la nueva a la que quiero agregarle esos nodos por mas que en esa es en la que me focalizo para trabajar.**
**A la que si cambio de parámetro segun a la lista a la que le estoy insertando cosas es a la función insertarEnLista**

**strstr no compara bien si no limpio /0 al final del string**
**strstr(cadenaAcomparar, palabraIngresada): devuelve null si no encuentra nada o devuelve un puntero desde el primer elemento encontrado con coincidencias**



