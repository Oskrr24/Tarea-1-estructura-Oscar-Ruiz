# README.md
## Descripción

**Sistema de Gestión de Pacientes en Hospital**
Este sistema permite a los usuarios gestionar la atención de pacientes en un hospital. Los usuarios pueden registrar nuevos pacientes, asignar prioridades, ver la lista de espera, y más. Esta herramienta está diseñada para mejorar la eficiencia en la atención de los pacientes, asegurando que aquellos en situaciones críticas reciban atención lo más pronto posible.

---
## Cómo compilar y ejecutar

Dado que el sistema está diseñado para ser accesible y fácil de probar, recomendamos usar [Repl.it](http://repl.it/) para una rápida configuración y ejecución. Sigue estos pasos para comenzar:

1. Visita [Repl.it](https://repl.it/).
2. Usa el link de abajo que te llevará directamente a la aplicación
3. [Repl.it](https://replit.com/@oscarruizf/Tarea-1-estructura).
4. Presiona el botón "Run" para compilar y ejecutar la aplicación.

## Funcionalidades

### Funcionando correctamente:

- Registrar pacientes con sus datos básicos y una prioridad inicial.
- Asignar o modificar la prioridad de los pacientes.
- Ver la lista de espera de pacientes, ordenada por prioridad y hora de registro.
- Atender al siguiente paciente, respetando el orden de prioridad.
- Mostrar pacientes filtrando unicamente por su orden de prioridad, manteniendo el orden de llegada.

### Problemas conocidos:
- Si se coloca en el apartado "edad del paciente" una edad no numerica, se saltará el síntoma preguntando directamente si se desea ingresar otro paciente, esto se vera reflejado luego como edad del paciente 0.
- Si en las preguntas de "¿Desea ingresar más datos?" se coloca una respuesta diferente a si o no, el programa seguirá independiente de a repuesta, se ruega colocar solamente si o no.
- Cuando se ingresa nombre o enfermedad, solo se puede leer una palabra.

### A mejorar:
- Se podria mejorar la eficiencia del programa.
- Implementar sistema para leer una frase y no una palabra.
- Implementar soluciones para aquellos casos nombrados en los Problemas Conococidos.

### Ejemplo de uso:
  **Paso 1: Registrar un Nuevo Paciente**

Se comienza registrando un nuevo paciente que acaba de llegar al hospital.

````c
Ingrese su opción: 1
Ingrese nombre del paciente: 
Juan
Ingrese edad del paciente: 
12
Ingrese sintoma del paciente: 
Gripe
Hora de ingreso del paciente: 
23:11:29
````
El sistema registra a Juan con una prioridad inicial "Bajo" y guarda la hora actual de registro. La prioridad inicial puede ser ajustada más tarde basada en una evaluación médica más detallada.

**Paso 2: Asignar Prioridad a un Paciente**

Tras una evaluación inicial, el médico determina que el estado de Juan requiere atención prioritaria.
````c
Ingrese su opción: 2
ASIGNAR PACIENTES POR PRIORIDAD:
N°1) Juan --> Baja
Ingrese nombre del paciente para asignar prioridad: 
Juan
Asigne o mantega prioridad del paciente: 
'1' Baja
'2' Media
'3' Alta
3
Paciente Juan con nueva prioridad: Alta
````
El sistema actualiza la prioridad de Juan a "Alto", asegurando que será uno de los pacientes próximos a ser atendido.
**Paso 3: Ver la Lista de Espera**

El usuario revisa la lista de espera para ver todos los pacientes y sus prioridades.
````c
Pacientes en espera:

Paciente Nº 1
Nombre: Juan
Edad: 12
Síntoma: Gripe
Prioridad: ALTA
Hora de llegada: 23:11:29
````
La lista muestra a Juan en la parte superior, mostrando edad, síntoma y se indica su prioridad alta, y que es él siguiente en línea para recibir atención.
**Paso 4: Atender al Siguiente Paciente**

Juan es llamado para ser atendido basándose en su prioridad.
````c
Ingrese su opción: 4
Paciente por atender:
Nombre: Juan
Edad: 12
Síntoma: Gripe
Prioridad: BAJA
````
El sistema muestra que Juan está siendo atendido y se elimina de la lista de espera.

**Paso 5: Mostrar pacientes por prioridad**
````c
Ingrese su opción: 5
Ingrese prioridad a mostrar:
'1' Baja
'2' Media
'3' Alta
2
Paciente Nº 1
Nombre: juan
Edad: 12
Síntoma: Gripe
Prioridad: MEDIA

Paciente Nº 2
Nombre: Marcelo
Edad: 18
Síntoma: Fiebre
Prioridad: MEDIA
````
El sistema muestra la lista de pacientes filtrada por la prioridad escogida por el usuario, viendo así los pacientes que están por esa prioridad.

### Contribuciones
## Oscar Ruiz:
- Diseño de la interfaz.
- Diseño funciones.
- Etc.
- Desarrollo de todo el programa.
- **Auto-evaluación**: 3 (Aporte excelente)
