# MAVI II - Unidad 1
**Gomez Viera Emilio Leandro**

## 
Simulación física básica con Raylib + Box2D. Se spawnean cajas dinámicas con el mouse, con ángulo ajustable por teclado.

## Controles
- `SPACE` — spawnear cajas en posición del mouse. 
La cajita verdeclaro es para previsualizar la rotación de la caja. De todos modos tambien esta en el HUD el ángulo
- `T` / `Q` — rotar ángulo de spawn
- `ESC` — salir

## Problemas que surgieron

### Hay un Gap visual entre cajas y suelo
`DrawRectanglePro` y `DrawRectangleLinesEx` interpretan la posición de forma distinta. El primero usa el rect + origin como pivote, el segundo dibuja desde la esquina tal cual. Entonces calculo() el centro directo a `DrawRectanglePro` y dejar que el origin haga el offset ( que antes era una resta).

### Las cajas que caen a 45° justos se quedan "clavadas" en el piso. Solución: no tengo idea, supongo que es cosa de box2D de como discretiza en lo chiquito. 

## Notas 

### POO vs plantilla
La consigna pide POO pero la plantilla tiene un struct y sin metodos(physicsBox). 

### Velocidad de simulación vs FPS
El worldstep y el setFPS:que pasa si los fps fluctuan, la simulación se desfasa del dibujado. Tendré que usar getframetime?

PD: Yo sé que me pongo neurótico con esto, pero documentar acá las dudas que me aparecen es mi mejor herramienta para ir aprendiendo.

