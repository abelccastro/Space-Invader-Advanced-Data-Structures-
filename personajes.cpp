#include "personajes.h"
#include "disparos.h"
#include "diseno.h"
#include <allegro.h>

#define ANCHO 600
#define ALTO  600

void NAVE::inicia(char* ruta_nave , char* ruta_bala,int _ancho_b,int _alto_b,int _ancho_p,int _alto_p,int _x,int _y,int _dir_bala,int _tipo,int _vida){
     x = _x; y = _y;///posicion de la nave mitad y 50 para abajo
     n_disp = 0; max_disp = 2;
     img_nav = load_bitmap(ruta_nave,NULL);
     img_bala = load_bitmap(ruta_bala,NULL);
     tick = 0;
     ancho_b=_ancho_b;alto_b=_alto_b;
     ancho_p=_ancho_p;alto_p=_alto_p;
     dir_bala=_dir_bala;
     tipo=_tipo;
     vida=_vida;///cuando tiene k desparecer el enemigo
     exp_enem=load_bitmap("Recursos/pum_enemigo.bmp",NULL);///bitmap con la explosion del enemigo


}

bool NAVE::temporizador(int tiempo){///control de tiempo para lograr efecto separacion balas
     tick++;
     if(tick == tiempo){
         tick = 0;
         return true;
     }
     return false;

}

void NAVE::pinta(BITMAP* buffer,int ix, int iy){
    masked_blit(img_nav,buffer,ix*ancho_p,iy*alto_p,x,y,ancho_p,alto_p);///pinta nave sobre el buffer cordenadas xy y dimensiones los 2 ceros son para indicar desde donde agarra la imagen en k punto la agarra

}
/*void NAVE::pintaoscuro(BITMAP* buffer,int ix, int iy){
    masked_blit(img_nav,buffer,ix*ancho_p,iy*alto_p,x,y,ancho_p,alto_p);///pinta nave sobre el buffer cordenadas xy y dimensiones los 2 ceros son para indicar desde donde agarra la imagen en k punto la agarra

}*/

void NAVE::mueve(){///movimiento de nave se puede acoplar para diagonales presion de teclas
     if(key[KEY_LEFT]) x -= 5;
     if(key[KEY_RIGHT]) x += 5;

}
void NAVE::dispara(struct Balas disparos[],BITMAP* buffer){
           ///tipo 0 para la nave y 1 para el enemigo
           if(tipo)
           crear_bala(n_disp , max_disp , disparos , x , y, dir_bala);///numero de disparos realizados numero de disparos permitidos,structdisparos, coordeadasde la nave, direccion y velcoidad de los disparos
           pintar_bala(n_disp , max_disp , disparos , buffer , img_bala,ancho_b,alto_b);///numero de disparos,maximo de disparos,disparos,buffer y imagen de bala
           elimina_bala(n_disp , max_disp , disparos , ANCHO , ALTO);///quita balas del arreglo que salen de las dimensiones de pantalla, ancho alto dimensiones

}
void acomoda_enemigos(struct NAVE E[]){
    int indice = -1;
    int _tipo=0;//algo para acomodoar el tipo de enemigo
    for(int i=0;i<5;i++){
        _tipo++;
        if(_tipo==4)_tipo=1;///4para intercalar los tipos de enemigos
        for(int j=0; j<11;j++){
            indice++;
            E[indice].inicia("Recursos/enemigos.bmp","Recursos/Bala_enem.bmp",6,12,25,20,140+j*30,130+i*24,12,_tipo,1);///*30 y*24 es para k no aparescan en el origen posicionmaineto de los enemigos
        }
    }
}
void pintar_enemigos(struct NAVE E[],BITMAP* buffer,int mov){
    BITMAP* parche=create_bitmap(30,20);///crea bitmap y manda dimensiones del enemigo
    clear_to_color(parche,0x000000);
    int indice = -1;
    for(int i=0;i<5;i++){
        for(int j=0; j<11;j++){
            indice++;
            if(E[indice].vida>0){
                E[indice].pinta(buffer,mov,E[indice].tipo-1);///pinta los enemigos en el buffer mov es para k se simule el movimieto de los enemigos es decir que se muevan en su posicion
            }
            /*else(
                //E[indice].pinta(buffer,mov,E[indice].tipo-1);
                masked_blit(parche,buffer,ix*ancho_p,iy*alto_p,x,y,ancho_p,alto_p);
            )*/
        }
    }
}
void explosion1(struct NAVE &E, BITMAP* buffer){
    BITMAP* parche=create_bitmap(30,20);///crea bitmap y manda dimensiones del enemigo
    clear_to_color(parche,0x000000);
    blit(parche,buffer,0,0,E.x,E.y,25,20);///imprimir un parche negro para crear el efecto
    masked_blit(E.exp_enem,buffer,0,0,E.x-10,E.y,41,34);

    //clear_to_color(parche,0x000000);
    //blit(parche,buffer,0,0,E.x-2,E.y+5,41,34);///imprimir un parche negro para crear el efecto
    //masked_blit(parche,buffer,0,0,E.x-2,E.y+5,41,34);
}
void explosion2(struct NAVE N, BITMAP* buffer,BITMAP* fondo){
    BITMAP* parche=create_bitmap(30,20);///crea bitmap y manda dimensiones de nave
    clear_to_color(parche,0x000000);
    for(int j=0;j<6;j++){
        for(int i=0;i<=2;i++){
            blit(parche,buffer,0,0,N.x,N.y,30,20);
            masked_blit(N.img_nav,buffer,i*30,0,N.x,N.y,30,20);///PINTA LA EXPLOSION
            imprimir_fondo(fondo,buffer);
            blit(buffer,screen,0,0,0,0,ANCHO,ALTO);
            //rest(50);
        }
    }
}
