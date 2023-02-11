# Calculo de números primos con OpenMP y MPI / Prime numbers with OpenMP and MPI

# Obetivo
El objetivo de este trabajo final es realizar un software para obtener números primos utilizando técnicas de programación paralela. Se deberá implementar el software utilizando la Interfaz de paso de mensajes – MPI y la interfaz de hilos paralelos OpenMP. Además, se debe realizar una serie de mediciones de tiempo de ejecución para comparar el programa secuencial, el comportamiento del programa paralelizado con múltiples hilos y con múltiples procesos. 

# Consigna principal
En este trabajo se deben desarrollar diversas versiones de un programa, tanto para su implementación con la biblioteca OpenMP y con MPI, para realizar la búsqueda de los primeros n números primos. La cantidad la indica el usuario como argumento al programa.
El objetivo es dividir el espacio de búsqueda entre todos los procesos/hilos que se vayan a ejecutar (no considerar los valores pares porque no son primos, excepto el 2). De esta forma, la cantidad de procesos/hilos dependerá de los recursos disponibles o la configuración de inicio, y cada proceso buscará sólo en el rango que le corresponde.
La primera versión del programa debe ejecutar la búsqueda de los números primos de forma secuencial sobre los números candidato.
Implementar una versión en la que todos se sincronizan (barrera) antes de avanzar sobre el siguiente número y otra donde trabajan de forma independiente. Comparar los tiempos de ejecución.
La segunda versión debe proveer algún mecanismo para que los hilos/procesos tomen el próximo valor a verificar. De esta forma, el proceso o hilo no debería estar ocioso esperando a que otros terminen. Sin embargo, se necesita sincronización o comunicación (según corresponda) para poder avanzar.
Compare los tiempos de ejecución contra los observados para la primera versión.
Finalmente, busque en Internet algoritmos eficientes, implemente el mejor en forma secuencial y en los programas anteriores. Compare los resultados de tiempo entre todas las versiones de los programas utilizados.

