# Repositorio de procesamiento digital de imágenes


## Tarea2 / Webcam con LTILIB-2
Implementación desarrollada con la biblioteca LTILIB-2. Hace lectura del _scroll_ y flechas del teclado.

![ltilib2-webcam](https://github.com/manchii/PDI/blob/master/Tarea2/tarea2.gif)

## Tarea2-ocv / Webcam con OpenCV
Implementación desarrollada con la biblioteca OpenCV. Hace lectura del _scroll_ y flechas del teclado.

![opencv-webcam](https://github.com/manchii/PDI/blob/master/Tarea2-ocv/Tarea2-ocv.gif)


## Tarea3 / Trazado de líneas con LTILIB-2
Implementación del algoritmo Bresenham para trazar líneas sobre una imagen.
La líneas son trazadas al seleccionar un píxel del cuadro. Se inicia desde el píxel (0,0) y ahí en adelante
se va desplazando el inicio de cada línea por final de la anterior.
En las teclas **w**, **a**, **s** y **d**, se tienen asignados casos de puntos ubicados fuera de las dimensiones dentro del cuadro.
El programa decide detener el _plot_ en los límites del cuadro, pero continua el algoritmo continua normalmente.

![ltilib2-lines](https://github.com/manchii/PDI/blob/master/Tarea3/tarea3.gif)

## Tarea3-ocv / Trazado de líneas con OpenCV
Trazado de líneas basado en el algoritmo Bresenham sobre una imagen.
La líneas son trazadas al seleccionar un píxel del cuadro. Se inicia desde el píxel (0,0) y ahí en adelante
se va desplazando el inicio de cada línea por final de la anterior.
En las teclas **w**, **a**, **s** y **d**, se tienen asignados casos de puntos ubicados fuera de las dimensiones dentro del cuadro.
El programa decide detener el _plot_ en los límites del cuadro, pero continua el algoritmo continua normalmente.

![opencv-lines](https://github.com/manchii/PDI/blob/master/Tarea3-ocv/tarea3-ocv.gif)

## Tarea4 / Mapeo bilineal con LTILIB-2
En este programa, él realiza la transformación de imágenes utilizando el método de mapeo bilineal. Este método se basa en el uso del conjunto de los números complejos. El procedimiento para la transformación sigue los pasos siguientes:

1. Los cuatro píxeles (0,0), (0,cols), (rows-1,0) y (rows-1,cols-1) son mapeados en las coordenadas de la imagen resultante. Esto permite estimar un _offset_ y la resolución de la imagen final para rellenarla.

2. Se realiza un _allocate_ de memoria para la imagen destino de acuerdo a la resolución estimada.

3. Se recorre cada píxel de la imagen destino y se le encuentra su píxel equivalente utilizando el mapeo inverso e interpolación bilineal.


![wesanderson](https://github.com/manchii/PDI/blob/master/Tarea4/wesanderson.jpg)
![wesandersonmapped](https://github.com/manchii/PDI/blob/master/Tarea4/wesanderson_mapped.png)
