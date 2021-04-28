# Tarea 1 2021-1-La Portada de Gepe 💽 📸 🍎 🥖 ☕️

> Carlos Jouanne, 17642701

## Contenidos
* Requerimientos
* Ejecución
  * Ejemplos
  * Resultados
* Analisis

## Requerimientos
Debes tener instalada la librería `libpng` para poder leer las imágenes cómo matrices.  
Esta la puedes instalar con el comando:
```sudo apt install libpng-dev```

## Compilar y ejecutar
Compilar:
```make```

Ejecutar:
```./filters <input.png> <output.png> <tipo_de_filtro> <A G | D>```

### Ejemplos:
Filtrar nodos con area mayor a 100 pixeles y grisáceo mayor a 50:
```./filters tests/img1 out.png area 100 50```

Filtrar nodos con delta menor a 0.25:
```./filters tests/img1 out.png delta 0.25```
### Resultados
Al *testear* el programa con las Imagenes de prueba provistas por el curso en los niveles *Easy*, *Medium* y *Hard* se obtuvieron resultados **correctos** de manera **eficiente** (menos de 10 segundos sin usar Valgrind, y alrededor de 15 segundos en la imagen más grande utilizando Valgrind). Además, **_Valgrind_ indicó que el programa no tiene errores de memoria**, y que **no hay _memory leaks_**. El programa fue desarrollado y ejecutado con un procesador Intel® Core i5 2da generación, 4GB de RAM, GPU NVIDIA® GEFORCE 2GB, utilizando el sistema operativo Kali Linux.

`./filters ./imagenes\ T1/image.png output.png area 200 0`

| Test   | Versión           | user     | system  | cpu    | total  |
|--------| :---------------: |:--------:| :------:|:------:|-------:|
| moon.png (143.794 bytes) | sin Valgrind            | 4.09s    | 0.03s   | 99%    | 4.122  |
|        | con Valgrind                 | 12.3s    | 0.08s.  | 99%    | 12.40  |
| plate.png (291.560 bytes) | sin Valgrind            | -     | -   | -    | -  |
|        | con Valgrind                 | 8.41s    | 0.10s.  | 99%    | 8.513  |
| campus.png (324.468 bytes) | sin Valgrind            | 4.06s    | 0.02s  | 99%    | 4.092  |
|        | con Valgrind                 | 17.07s    | 0.10s.  | 99%    | 17.84  |

`./filters ./imagenes\ T1/hard/image.png output.png delta 0.01`

| Test   | Versión           | user     | system  | cpu    | total  |
|--------| :---------------: |:--------:| :------:|:------:|-------:|
| moon.png (143.794 bytes)  | sin Valgrind            | 4.13s    | 0.03s   | 99%    | 4.166  |
|        | con Valgrind                 | 12.36s    | 0.10s.  | 99%    | 12.48  |
| plate.png (291.560 bytes)  | sin Valgrind            | -     | -   | -    | -  |
|        | con Valgrind                 | 8.31s    | 0.13s.  | 99%    | 8.448  |
| campus.png (324.468 bytes)  | sin Valgrind            | 4.00s    | 0.02s  | 99%    | 4.029  |
|        | con Valgrind                 | 16.69s    | 0.10s.  | 99%    | 16.80  |

> ⚠️ Para ejecutar el programa utilizando la imagen `plate.png`(291.569 bytes) con **Valgrind** es necesario agregar el **flag** `--main-stacksize=12000000`

## Analisis

Un _*Component Tree*_ es similar a un _*Max Tree*_, pero se diferencia de este último en que cada nodo guarda todos los pixeles que tienen sus descendientes. En esta tarea, por ejemplo, un nodo guardaría todos los pixeles del vecindario, en vez de gurdar solo los pixeles cuyo grisaseo es igual al umbral del nodo.

### Eficiencia

En términos de eficiencia, se dice que el _Max Tree_ es una versión más compcta y eficiente del _Component Tree_, puesto que el _Component Tree_ presenta una representación redundante de la imagen, ya que la mayoría de los píxeles pertenecerán a más de un nodo. Además, hay vecindarios que no cambian de un umbral a otro, por lo que es redundante utilizar más de un nodo para representarlos. El _Max Tree_ es más compacto que el _Component Tree_, ya que sus nodos almacenan sólo la píxeles que son visibles en la imagen en el nivel de gris correspondiente, por lo tanto, los vecindarios que permanecen iguales durante una secuencia de umbrales están representados en un solo nodo.

De esta forma, evidentemente en términos de uso memoria es más eficiente un _Max Tree_ en relacion al _Component Tree_. Por otro lado, en términos de complejidad a la hora de realizar operaciones pueden existir operciones en las que sea más eficiente utilizar un _Component Tree_, como por ejemplo si se quiere realizar una opreción sobre todo un vecindario solo habría que buscar el primer nodo que contenga todo ese vecindario y aplicar la operación sobre ese nodo, mientras que en un _Max Tree_ habría que hacer una llamada recursiva para acceder a todos los nodos hijos y realizar la opreción en cada uno de estos nodos. Sin embargo, para la mayoría de las operaciones es más eficiente utilizar un _Max Tree_ ya que al ser un arbol más pequeño, es más facil de recorrer. Además, operaciones de filtro de area, filtros de apertura, filtros de atributos estadísticos, y otros, son más eficientes de implementar en un _Max Tree_. En terminos de eficiencia de CPU dependería del caso, puesto que para imagenes grandes un _Component Tree_ es muy ineficiente y lento de recorrer, sobre todo comparado con un _Max Tree_, pero para imagenes de menor tamaño, donde el porte del árbol no es tan diferente, podría ser más eficiente el uso de un _Component Tree_ puesto que al almacenar más información en cada nodo, no se utiliza tanta recursividad como en un _Max Tree_ y podría recquerir un menor uso de CPU el realizar estas operaciones específicas.

Debido a su estructura compacta y eficiente, creo que es correcto decir que para la mayoría de los casos es más conveniente utilizar un _Max Tree_, debido a que en términos de recursos totales suele ser más eficiente. Esto no quiere decir que no haya casos en que talez sea más conveniente utilizar un _Component Tree_, sin emargo, creo que estos casos son la minoría.


> ###### [1. Souza, R., Tavares, L., Rittner, L., Lotufo, R. (2016) An overview of max-tree principles, algorithms and applications](http://sibgrapi.sid.inpe.br/col/sid.inpe.br/sibgrapi/2016/08.17.11.54/doc/overview-max-tree.pdf)
