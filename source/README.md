# MAVI II - Unidad 2
**Gomez Viera Emilio Leandro**

## 
Simulación física básica con Raylib + Box2D. Se spawnea un proyectil inicial se orienta el angulo de disparo y se acumula impulso.

## Controles
- `SPACE` — acumula impulso. Al soltar se aplica el impulso al proyectil

- `T` / `Q` — rotar ángulo de tiro

## ESTRUCTURA

├── main.cpp           —  Crea entidades, corre el loop.
├── Init.h/.cpp     — Inicialización y cierre de ventana (raylib).
├── loopDeJuego.h/.cpp — Lógica de input y dibujo por frame.
├── Proyectil.h/.cpp   — Entidad proyectil con física box2d.
├── ground.h           — Suelo estático con física box2d.
├── OtrosCuerpos.h/.cpp— StaticBodys a modo de edificios con los que choca el proyectil*

*Acá me tenté de hacer una clase ContactListener para ver como funciona y reflejar visualmente como funciona. Pero tal vez se sale del scope del TP

## Problemas que surgieron

Sigo sin saber hasta donde no tocar la estructura del template y cumplir con los requerimientos POO. En el TP anterior descontaron puntos por eso pero aún no hay claridad al respecto. Tampoco sabía que gitHUB ignoraba ciertas librerías.

En concreto: reciclé el TP anterior, modularicé y encapsule un poco mas. Aun está a medio camino porque la inicialización de variables sigue viviendo en main, pero no quise agrandar mucho la firma de las declaraciones y llamadas.

##Notas

#Init es mas bien una inicialización de ventana, típica de raylib, pero también pensada para inicializar audio y tal vez otras cosas.

## Detalles
- Mover lógica de carga y color al `Proyectil` (peeero rompe el encapsulamiento actual).

- Unificar Ground::Draw() y Ground::Drawground(): que los puse separados solo para probar unas cosas visuales. Que al final no llegaron a buen puerto, pero tampoco complica en nada el esquema ni la ejecuciónm






