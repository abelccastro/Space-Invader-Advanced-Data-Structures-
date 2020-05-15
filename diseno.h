#include <allegro.h>
#ifndef DISENO_H_INCLUDED
#define DISENO_H_INCLUDED
struct Menu{
        int parpadeo;
        int y;
        int cont;
        bool salida;
        bool carga;
        BITMAP* p;

        void ini_portada();

        //clear_to_color(screen, 0x000000);
        void PORTADA(BITMAP* _p);
};
//void PORTADA(BITMAP* p);
//void ini_portada();
void imprimir_fondo(BITMAP*fondo, BITMAP* buffer);

#endif // DISENO_H_INCLUDED
