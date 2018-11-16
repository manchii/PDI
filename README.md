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

## Tarea5 / Filtros en OpenCV
En este programa, se realizó una comparación directa en el tiempo de ejecución de un filtro gaussiano utilizando 3 métodos de la biblioteca de openCV (filter2d,sepFilter y dft). Los resultados obtenidos se muestran en la figura debajo. El tiempo de ejecución se comparo en función del tamaño del kernel del filtro. Bajo la implementación naive de la convolución del filtro2d, se espera un orden 2 de crecimiento y de orden lineal para el del filtro separable. Sin embargo, la bilioteca implementa el filtro2d por medio de optimizaciones donde la versión naive se observa para un tamaño del kernel menor a 8 y una en frecuencia después de 8. Para el filtro separable, este crece linealmente y es hasta para un filtro de tamaño 29, que este método resulta superado por el filtro realizado en el dominio de la frecuencia.

![exectime](https://github.com/manchii/PDI/blob/master/Tarea5/execution_time.png)
