# Proyecto de PDI
## Implementación de filtros de máximos/mínimos con SIMD AVX2

### Introducción

Los filtros basados en los operadores de mínimos o máximos están directamente asociados con los operadores morfológicos de dilatación y erosión. La definición matemática  del filtro es

![](https://github.com/manchii/PDI/blob/master/Proyecto/imgs/filtereq.png)

Donde _S(x,y)_ es la imagen fuente y _D(x,y)_ la imagen destino. La regla de la operación asigna para cada pixel _(x,y)_ de la imagen _D_ el píxel mayor alrededor de la localidad del píxel _(x,y)_ de la imagen fuente _S_ de acuerdo a una máscara T(x,y).

### Comparación 

![](https://github.com/manchii/PDI/blob/master/Proyecto/src/tools/execution_time.png)

### Requisitos

* OpenCV
* ltilib2

### Ejecución

Primero asegurese que los ``Makefile`` de ``src/seq/``, ``src/dokladal/`` y ``src/vectorized/`` estén correctamente con el link a la biblioteca de ltilib2 instalada. Si es afirmativo, puede ejecutar el test de regresión con

```bash
cd src/tools/
./regression_run.sh
```
