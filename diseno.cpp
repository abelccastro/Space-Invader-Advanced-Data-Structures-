#include "diseno.h"
#include <allegro.h>

void Menu::PORTADA(BITMAP* _p){
        parpadeo = 0;
        y = 0;
        cont = 0;
        salida = false;
        carga = false;
        p=_p;

        //ini_portada();

        clear_to_color(screen, 0x000000);
}
void imprimir_fondo(BITMAP*fondo, BITMAP* buffer){
    masked_blit(fondo,buffer,0,0,0,0,600,600);///esto es para cargar una pantalla rosa de los bitmaps que les otorga una propiedad k no se pero se necesita
}
void Menu::ini_portada(){
    while(!salida){
              if(parpadeo < 25) blit(p , screen , 0 , y , 0 , 100 , 600 , 400);
              else blit(p , screen , 600 , y , 0 , 100 , 600 ,400);

              if(key[KEY_ENTER]){
                  y = 400;
                  carga = true;
              }

              if(carga) cont++;
              if(cont > 100) salida = true;

              rest(5);
              if(++parpadeo == 50) parpadeo = 0;

        }
}
