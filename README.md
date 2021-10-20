# BASE DE DATOS 2 
## Proyecto 1 
--------
## Integrantes ✒️

- Juan Pablo Lozada [IWeseI] Participación: 100%
- Alexandra Shulca [Alexandra-SR] Participación: 100%
- Alex Loja Zumaeta [aljozu] Participación: 100%

## Profesor 🦾

- Heider Sanchez Enriquez

## Asistentes de docencia
- Juan Galvez Ccopa


## Introducción :dart:

**_Objetivo:_** Implementar dos técnicas de organización de archivos que almacenen la información y permitan el manejo de los registros de manera eficaz. En este caso, nos permitirá encontrar los precios de venta y las características de determinados autos usados. Para lograr esto implementaremos _Sequential File y Extentible Hashing_.

**_Descripción del dominio:_** Usaremos una base de datos que cuenta con la información de [carros usados de la marca Audi](https://www.kaggle.com/mysarahmadbhat/audi-used-car-listings). Existen más de 10 mil registros y por cada uno tenemos la siguiente información:

- **Id**: Número de identificación.
- **Model**: Modelo de Audi.
- **Year**: Año de registro.
- **Price**: Precio en euros.
- **Transmission**: Tipo de cambios.
- **Mileage**: Distancia usada.
- **FuelType**: Tipo de combustible.
- **Tax**: Impuesto por uso.
- **Mpg**: Millas por galon.
- **EngineSize**: Cilindrada.

**_Resultados esperados:_** Se espera poder hacer inserción de registros, búsqueda por rango, búsqueda específica y eliminación de acuerdo al id.


## Comenzando 🚀

### Pre-requisitos 📋
* [C++ 17](https://nuwen.net/mingw.html) 

### Despliegue 📦

**1.** Clonar el repositorio del proyecto.

**2.** Realizar el Build del proyecto en su IDE de preferencia.

**3.** Ejecutar el programa


## Descripción de las técnicas

**_Sequential file_**: En este método organizamos los registros de acuerdo a un valor de sus campos, para este caso usaremos el campo **Id** como key.

- **Búsqueda:**

  1.  Abrir el archivo de datos.
  2.  Iniciar búsqueda binaria.
  3.  Ubicar el puntero a la mitad del archivo de datos.
  4.  Comparar el id del regsitro encontrado con el id del registro entrante.
  5.  Mover el puntero de acuerdo al tamaño del id hasta encontrar una coincidencia.
  6.  Se lee el registro y tenemos 3 posibilidades:  
      6.1 El registro encontrado esta en el archivo principal entonces devolvemos el registro.  
      6.2 El registro encontrado ha sido eliminado, en este caso recorremos el archivo hasta encontrar el primer registro no borrado.  
      6.3 El registro se encuentra en el archivo auxiliar.
      - Se abre el archivo auxiliar.
      - Se recorre el archivo hasta encontrar una coincidencia.
      - Si se encuentra se devuelve el registro.
      - Si no se encuentra se devuelve el registro más cercano anterior al id del regsitro buscado.
      - Se cierra el archivo auxiliar.
  7.  Se cierra el archivo principal de datos.

- **Inserción:**

  1. Abrimos el archivo auxiliar.
  2. Comprobamos si hay espacio.  
     2.1 Si no hay espacio se leen todos los registros y se insertan al archivo principal.  
     2.2 Si hay espacio se busca el registro anterior en el archivo principal.  
     2.3 Se actualizan los punteros.  
     2.4 Se escribe el registro.
  3. Se cierra el archivo.

- **Eliminación:**

  1. Se busca el registro que va antes del registro actual.
  2. Se actualizan los punteros del registro anterior.
  3. Se marca el registro como eliminado.
  4. Se hace update a los registros modificados.

- **Búsqueda por rango:**

  1. Se busca el archivo registro inicial.
  2. Se itera añadiendo los registros hasta llegar al registro final.
  3. Retorna un vector de registros.

* **Ventajas:**
  - Al ser un arhivo ordenado la búsqueda de registros se realizará siempre en log(n).

**_Extendible Hashing:_** El hash extensible es una estructura que se actualiza dinámicamente y que implementa un esquema de hash utilizando un directorio. El índice se utiliza para encontrar consultas donde exista un registro con una key determinada.

- **Búsqueda:**

  1. Calculamos el hash de la key que queremos buscar.
  2. Verificamos la cantidad de bits(**n**) que se usan en el directorio.
  3. Tomar los n bits de la dirección hash.
  4. Usando este índice encontrar el bucket al que pertenece el registro.
  5. Leer todos los registros en ese bucket.
  6. Recorrer los registro leídos.
  7. Retornar el registro encontrado.
  8. Cerrar el archivo.

- **Inserción:**

  1. Calculamos el hash de la key que queremos buscar.
  2. Verificamos la cantidad de bits(**n**) que se usan en el directorio.
  3. Tomar los n bits de la dirección hash.
  4. Usando este índice encontrar el bucket al que pertenece el registro.
  5. Comprobamos que la key no se encuentre en el Bucket.
  6. Tenemos dos casos:
     - El bucket aún no esta completo.
       - Insertamos el registro.
     - El bucket está completo.
       - Creamos el nuevo bucket.
       - Reinsertamos todos los registros.
       - Se crean los nuevos buckets con la nueva profundidad local.
       - Se actualiza el directorio.

- **Eliminación:**

  1. Calculamos el hash de la key que queremos buscar.
  2. Verificamos la cantidad de bits(**n**) que se usan en el directorio.
  3. Tomar los n bits de la dirección hash.
  4. Usando este índice encontrar el bucket al que pertenece el registro.
  5. Leer los datos del registro.
  6. Eliminar el registro.
  7. Si el bucket queda vacio, liberar la memoria.
  8. Actualizar el directorio.
  9. Leer el directorio.
     - Si existen dos buckets con pocos elementos y el mismo prefijo en la profundidad anterior se puden mezclar.
     - Crear un nuevo bucket.
     - Leer los registros de los dos buckets.
     - Liberar los dos buckets pasados.
     - Escribir los registros en el nuevo bucket.
     - Actualizamos el directorio.
     - Cerrar el directorio.

* **Ventajas:**
  - Es eficaz mientras la memoria principal soporte el directorio.
  - La eficiencia se mantiene con el crecimiento del archivo de datos.
  - La cantidad de reescrituras no es tan grande.  

## Resultados Experimentales  
  
  ***Sequential File***  
  
  ![Tiempo vs Operación por registro](/Imagenes/SF_ExecutionTimes.png)  
  - Podemos observar como los tiempos de inserción aumentan cada cierta cantidad de operaciones, ya que al acabarse el espacio auxiliar los registros son escritos en memoria secundaria y ordenados de acuerdo a su key.
  - Los tiempos de búsqueda y eliminación solo aumentan cuando el registro se encuentra en el archivo auxiliar, caso contrario su tiempo de ejecución se mantiene constante.

  ***Extendible Hashing***
  
  ![Tiempo vs Operación por registro](/Imagenes/EH_ExecutionTimes.png)
  - Los tiempos de búsqueda son constantes en cualquier moment.
  - Los picos de tiempo en insertar se dan porque en algún momento se necesita hacer split de algun bucket.
  - Los tiempos altos en eliminar se dan porque se necesita hacer merge entre dos buckets con cantidad baja de registros. 


## Evidencias 🚀

* [Video](https://drive.google.com/drive/folders/1FY2bS6usvtPjwruH39Gzagi8iZs4J8BQ?usp=sharing) 

  
