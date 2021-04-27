# Tarea 1 2021-1-La Portada de Gepe 💽 📸 🍎 🥖 ☕️

> Carlos Jouanne, 17642701

## Contenidos
* Requerimientos
* Ejecución
  * Ejemplos
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

## Analisis

Un _*Component Tree*_ es similar a un _*Max Tree*_, pero se diferencia de este último en que cada nodo guarda todos los pixeles que tienen sus descendientes. En esta tarea, por ejemplo, un nodo guardaría todos los pixeles del vecindario, en vez de gurdar solo los pixeles cuyo grisaseo es igual al umbral del nodo.

### Eficiencia

En términos de eficiencia, se dice que el _Max Tree_ es una versión más compcta y eficiente del _Component Tree_, puesto que el _Component Tree_ presenta una representación redundante de la imagen, ya que la mayoría de los píxeles pertenecerán a más de un nodo. Además, hay vecindarios que no cambian de un umbral a otro, por lo que es redundante utilizar más de un nodo para representarlos. El _Max Tree_ es más compacto que el _Component Tree_, ya que sus nodos almacenan sólo la píxeles que son visibles en la imagen en el nivel de gris correspondiente, por lo tanto, los vecindarios que permanecen iguales durante una secuencia de umbrales están representados en un solo nodo. De esta forma, evidentemente en términos de uso memoria es más eficiente un _Max Tree_ en relacion al _Component Tree_. Por otro lado, en términos de complejidad a la hora de realizar operaciones pueden existir operciones en las que sea más eficiente utilizar un _Component Tree_, como por ejemplo si se quiere realizar una opreción sobre todo un vecindario solo habría que buscar el primer nodo que contenga todo ese vecindario y aplicar la operación sobre ese nodo, mientras que en un _Max Tree_ habría que hacer una llamada recursiva para acceder a todos los nodos hijos y realizar la opreción en cada uno de estos nodos. Sin embargo, para la mayoría de las operaciones es más eficiente utilizar un _Max Tree_ ya que al ser un arbol más pequeño, es más facil de recorrer. Además, operaciones de filtro de area, filtros de apertura, filtros de atributos estadísticos, y otros, son más eficientes de implementar en un _Max Tree_.
> ###### [1. Souza, R., Tavares, L., Rittner, L., Lotufo, R. (2016) An overview of max-tree principles, algorithms and applications](http://sibgrapi.sid.inpe.br/col/sid.inpe.br/sibgrapi/2016/08.17.11.54/doc/overview-max-tree.pdf)
