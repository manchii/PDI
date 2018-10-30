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
