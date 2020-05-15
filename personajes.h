#include <allegro.h>
#ifndef PERSONAJES_H_INCLUDED
#define PERSONAJES_H_INCLUDED
struct NAVE{
     int x,y;
     int n_disp;///numero de disparos
     int max_disp;///maximo de disparos
     int tick;///tiempo de creacion de a bala
     int ancho_b,alto_b;///ancho y alto de la bala
     int ancho_p,alto_p;
     int dir_bala;
     int tipo;
     int vida;

     BITMAP* img_nav;
     BITMAP* img_bala;
     BITMAP* exp_enem;

     void inicia(char* ruta_nave , char* ruta_bala,int _ancho_b,int _alto_b,int _ancho_p,int _alto_p, int _x,int _y,int _dir_bala,int _tipo,int _vida);
     bool temporizador(int tiempo);///tiempo de retraso entre balas
     void pinta(BITMAP* buffer,int ix,int iy);///para pintar la nave recib buffer con bitmap
     //void pintaoscuro(BITMAP* buffer,int ix,int iy);///para pintar la nave recib buffer con bitmap
     void mueve();///movimiento de la nave
     void dispara(struct Balas disparos[],BITMAP* buffer);
};
void acomoda_enemigos(struct NAVE E[]);
void pintar_enemigos(struct NAVE E[],BITMAP* buffer,int mov);
void explosion1(struct NAVE &E, BITMAP* buffer);///explosion del enemigo
void explosion2(struct NAVE N, BITMAP* buffer,BITMAP* fondo);///explosion de la nave fondo para actualizar fondo x problemade pintado

#endif // PERSONAJES_H_INCLUDED
