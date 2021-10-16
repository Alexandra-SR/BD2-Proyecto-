# BD2-Proyecto
## Introducción  
***Objetivo:*** Implementar dos técnicas de organización de archivos que almacenen la información y permitan el manejo de los registros de manera eficaz. En este caso, nos permitirá encontrar los precios de venta y las características de determinados autos usados. Para lograr esto implementaremos *Sequential File y Extentible Hashing*. 

***Descripción del dominio:*** Usaremos una base de datos que cuenta con la información de [carros usados de la marca Audi](https://www.kaggle.com/mysarahmadbhat/audi-used-car-listings). Existen más de 10 mil registros y por cada uno tenemos la siguiente información:  

  - **Id**: Número de identificación.
  - **Model**: Modelo Audi.  
  - **Year**: Año de registro.  
  - **Price**: Precio en euros.  
  - **Transmission**: Tipo de cambios.  
  - **Mileage**: Distancia usada.  
  - **FuelType**: Tipo de combustible.  
  - **Tax**: Impuesto por uso.  
  - **Mpg**: Millas por galon.  
  - **EngineSize**: Cilindrada.  

***Resultados esperados:*** Se espera poder hacer inserción de registros, búsqueda por rango, búsqueda específica y eliminación de acuerdo al id.  

## Descripción de las técnicas  

