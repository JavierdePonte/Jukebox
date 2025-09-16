# JUKEBOX


## Authors

* **Javier de Ponte Hernando** - email: [j.deponteh@alumno.es](mailto:j.deponteh@alumno.es)
* **Roberto Maldonado Macafee** - email: [roberto.maldonado.macafee@alumno.es](mailto:roberto.maldonado.macafee@alumno.es)


<!-- Ponga una breve descripción del proyecto **aquí** en castellano e inglés. -->
## DESCRIPCIÓN DEL PROYECTO
El proyecto Jukebox consiste en el desarrollo de un sistema básico de reproducción de melodías integrado en un núcleo STM32F446RE. Las melodías se reproducen por un zumbador conectado a la placa. El usuario puede seleccionar una canción de una lista, pausarla, reproducirla, detenerla, y cambiar su velocidad de reproducción a través de un sistema de comunicación serie USART. El proyecto está dividido en 4 diferentes secciones y una extra. El funcionamiento de las primeras 4 versiones se fundamenta en el uso de máquinas de estados.
## PROYECT DESCRIPTION

The Jukebox project involves the development of a basic melody playback system integrated into an STM32F446RE core. The melodies are played through a buzzer connected to the board. The user can select a song from a list, pause it, play it, stop it, and change its playback speed through a USART serial communication system. The project is divided into 4 different sections and an additional one. The operation of the first 4 versions is based on the use of state machines.

<!-- Puede añadir una imagen de portada **de su propiedad** aquí. Por ejemplo, del montaje final, o una captura de osciloscopio, etc. -->
## HARDWARE VIEW
**ESPAÑOL** \n
A continuación, podemos observar una imagen del montaje final del dispositivo. \n
**ENGLISH**  \n
Next, we can observe an image of the final assembly of the device.
![Montaje del dispositivo completo](docs\assets\imgs\hw_jukebox_v5.png)\n 

## VIDEO-DEMO
**ESPAÑOL**
Para ver el funcionamiento de las mejoras añadidas al dispositivo en la versión 5, [pinche aquí](https://youtu.be/4-Lfzsa3KZw). 
<!-- **Las imágenes se deben guardar en la carpeta `docs/assets/imgs/` y se pueden incluir en el documento de la siguiente manera:**
```markdown
![Texto alternativo](docs/assets/imgs/imagen.png)
``` 

**Añada un enlace a un vídeo público de su propiedad aquí con la demostración del proyecto explicando lo que haya hecho en la versión V5.** -->

<!-- Para añadir un enlace a un vídeo de Youtube, puede usar el siguiente código: -->

<!-- ```markdown -->
<!-- ## VIDEO-DEMO
Aquí se pueden ver las mejoras adicionales implementadas en la última versión del proyecto Jukebox.
<!-- (https://youtu.be/4-Lfzsa3KZw "Demostración: version 5 del proyecto Jukebox.") -->
<!-- ``` --> 

**ENGLISH** \n
To see the functionality of the enhancements added to the device in version 5, [click here](https://youtu.be/4-Lfzsa3KZw).
## Version 1

**ESPAÑOL** \n
La primera versión del proyecto Jukebox se centra en el desarrollo de la base del sistema. Desarrollamos lo relacionado con la interacción del usuario con el dispositivo, para ello utilizamos un botón de usuario. Para su correcto funcionamiento, implementamos una máquina de estados con los posibles estados del botón. El botón nos dará la información de si se ha pulsado o no y, si se ha pulsado cuánto tiempo ha durado esa pulsación. En función de esta duración el jukebox se encenderá o apagará, reproducirá o pausará una melodía. Es necesario implementar una interrupción del sistema para interactuar con el reproductor.

**ENGLISH** \n
The first version of the Jukebox project focuses on developing the system's foundation. We developed user interaction with the device using a user button. For proper operation, we implemented a state machine with the possible states of the button. The button will provide information on whether it has been pressed and, if so, how long the press lasted. Depending on this duration, the jukebox will turn on or off, play or pause a melody. A system interrupt will be necessary to interact with the player.

<!-- - Para poner un texto en negrita se usa el símbolo `**` de manera consecutiva. Por ejemplo: **Texto en negrita**
- Para poner un texto en cursiva se usa el símbolo `*` de manera consecutiva. Por ejemplo: *Texto en cursiva*
- Para poner un texto en cursiva y negrita se usa el símbolo `***` de manera consecutiva. Por ejemplo: ***Texto en cursiva y negrita***

Para añadir subsecciones se usa el símbolo `#` de manera consecutiva. Por ejemplo:

### Subsección 1
```markdown
Breve descripción de la subsección 1.

Para añadir una lista de elementos se usa el símbolo `-` de manera consecutiva. Por ejemplo:

- Elemento 1
- Elemento 2
- Elemento 3

Para añadir una lista de elementos numerados se usa el símbolo `1.` de manera consecutiva. Por ejemplo:

1. Elemento 1
2. Elemento 2
3. Elemento 3

Para añadir un enlace a una página web se usa el siguiente código:

```markdown
Enlace a [Google](https://www.google.com).
```

Puede añadir tablas de la siguiente manera:

| Columna 1 | Columna 2 | Columna 3 |
| --------- | --------- | --------- |
| Valor 1   | Valor 2   | Valor 3   |
| Valor 4   | Valor 5   | Valor 6   |

Para añadir un enlace a un fichero `.c` o `.h` puede usar el siguiente código. Se trata de enlaces a ficheros `.html` que se generan automáticamente con la documentación del código al ejecutar Doxygen y que se encuentran en la carpeta `docs/html/`.

```markdown
Enlace a la [FSM de Version 1](fsm__button_8c.html).
```
 -->


## Version 2

**ESPAÑOL** \n
En el segundo apartado del proyecto nos enfocamos en la comunicación entre el ordenador y nuestro dispositivo mediante la comunicación serial USART. Para ello tendremos que definir los posibles estados, esperar un envío de datos o enviar datos y montar el hardware necesario con la ayuda de un conversor USB-USART.

**ENGLISH** \n
In the second part of the project, we focus on communication between the computer and our device using USART serial communication. To do this, we will have to define the possible states, wait for data transmission, or send data and set up the necessary hardware with the help of a USB-USART converter.

## Version 3

**ESPAÑOL** \n
En el tercer módulo, desarrollamos el subsistema de reproducción de melodías. Para ello integramos el zumbador en nuestro aparato y definimos sus posibles estados para reproducir una nota, esperar la siguiente nota, esperar una melodía... Tendremos que añadir interrupciones en los temporizadores para la generación de Pulse Width Modulation y poder generar distintos tonos con el zumbador, es decir, poder reproducir las distintas notas. Básicamente, nos centraremos en la duración y frecuencia de las notas que se reproducirán.

**ENGLISH** \n
In the third module, we developed the melody playback subsystem. To do this, we integrated the buzzer into our device and defined its possible states to play a note, wait for the next note, wait for a melody... We will need to add timer interrupts for Pulse Width Modulation generation to produce different tones with the buzzer, i.e., play the various notes. Basically, we will focus on the duration and frequency of the notes to be played

## Version 4

**ESPAÑOL** \n
En la versión 4 integramos la máquina de estados final del sistema. Implementamos los modos de bajo consumo, importantes para una mayor eficiencia energética y completaremos el fichero ejecutable de nuestro programa. Al terminar de implementar lo ya mencionado, tenemos un jukebox completamente funcional.

**ENGLISH** \n
In version 4, we integrated the system's final state machine. We implemented low-power modes, important for greater energy efficiency, and completed the executable file of our program. After implementing the aforementioned features, we have a fully functional jukebox.

## Version 5

**ESPAÑOL** \n
La última versión de este proyecto la hemos aprovechado para añdir algunas melodías extra al dispositivo y, así gozar de una mayor variedad musical. Añadimos la reproducción de una melodía final cuando se procede a apagar el dispositivo.

**ENGLISH** \n
In the last version of this project, we took the opportunity to add some extra melodies to the device to enjoy a greater musical variety. We added the playback of a final melody when the device is turned off.




