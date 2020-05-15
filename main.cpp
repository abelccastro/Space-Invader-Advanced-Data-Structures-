#include <allegro.h>
#include <stdlib.h>
#include <time.h>
#include "inicia.h"
#include "disparos.h"
#include "personajes.h"
#include "diseno.h"
#define ANCHO 600
#define ALTO  600

#include <iostream>

using namespace std;
int main(){
    srand(time(NULL));
    inicia_allegro(ANCHO,ALTO); // fuciones del include inicia.h
	inicia_audio(70,70);        //

    BITMAP *buffer = create_bitmap(ANCHO, ALTO);
    BITMAP* portada=load_bitmap("Recursos/portada.bmp",NULL);
    BITMAP* fondo=load_bitmap("Recursos/fondo.bmp",NULL);
    Menu principal;

    principal.PORTADA(portada);
    principal.ini_portada();


    NAVE N;
    N.inicia("Recursos/nave.bmp" , "Recursos/Bala2.bmp",6,12,30,20,ANCHO/2,ALTO-70,-20,0,3);///carga de parametros de la nave imagenes y dimensiones.,final direccion de la bala,utlimo es 0 porque es el tipo nave 1 es enemigo,vida
    NAVE E[60];
    acomoda_enemigos(E);
    Balas disparos[N.max_disp];///arreglo de disparos con maximo de balas permitidas
    Balas disp_E[E[0].max_disp];///disparos de los enemigos

    int azar =rand()%55;///para que cualquier enemigo dispare al azar
    int mov=0;///para simular el movimiento de los enemigos en su misma posicion

    while(!key[KEY_ESC]){

        cout<<"bucle"<<endl;

           clear_to_color(buffer,0x000000);///funcion de alegro para pintar bitmap de un color negro


           N.pinta(buffer,0,0);
           N.mueve();
           ///para nave
           if(key[KEY_SPACE] && N.temporizador(5))
           crear_bala(N.n_disp,N.max_disp,disparos,N.x,N.y,N.dir_bala);
           N.dispara(disparos,buffer);
            ///disparos para enemigos ACA VA LA ESTRUCTURA DEL QUAD EN VEZ DE REAZLIAR BUSQUEDA SECUENCIAL
           for(int i=0;i<55;i++){
                elimina_bala_objeto(N,E[i],disparos);
                /*if(elimina_bala_objeto(N,E[i],disparos)&&(E[i].vida==0)){
                    explosion1(E[i],buffer);
                }*/
           }
           pintar_enemigos(E,buffer,mov);
           if(E[azar].n_disp==0)azar=rand()%55;
           E[azar].dispara(disp_E,buffer);
           if(E[0].temporizador(30)){
                if(++mov==2)mov=0;
           }
           if(elimina_bala_objeto(E[azar],N,disp_E) ){
                explosion2(N,buffer,fondo);
           }
           imprimir_fondo(fondo,buffer);
           blit(buffer, screen , 0,0 ,0,0 ,ANCHO, ALTO);///imprimir buffer sobre pantalla,buffer,pnatalla, coordenandas0000,ancho y alto.

           rest(15);///pausa para iteracion equivalente fps para no sobrecargar procesador
           if(N.vida==0){
            principal.PORTADA(portada);
            principal.ini_portada();
            N.vida=3;
            cout<<"dentrooooooo"<<endl;
        }

    }



	return 0;
}
END_OF_MAIN();

