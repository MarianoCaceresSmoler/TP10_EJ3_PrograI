#include "ports.h"
#include "leds.h"
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>

// Macros para configuracion de display allegro
#define NUM_PORTS 8
#define SCREEN_W  800
#define SCREEN_H  200

// Macros para manejo de entradas
#define TOGGLE 't'
#define TURN_ON  's'
#define TURN_OFF 'c'
#define EXIT 'q'

#define ERROR_MESSAGE "\nInput is not valid: Enter a valid character\n" // Mensaje de error en caso de ingreso invalido

#define CLEAN_BUFFER while(getchar() != '\n') // Macro para limpiar el buffer de entrada de datos

// Macros de estado del programa
#define PROGRAM_END -1
#define PROGRAM_ERROR 0
#define PROGRAM_CONTINUE 1


int main(void)
{
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;

    bool redraw = false;
    bool running = true;

    int i;

    // Inicializacion de allegro
    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    if (!al_install_keyboard()) {
        fprintf(stderr, "failed to initialize the keyboard!\n");
        return -1;
    }

    if (!al_init_primitives_addon()) {
        fprintf(stderr, "failed to init primitives addon!\n");
        return -1;
    }

    event_queue = al_create_event_queue();
    if (!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        return -1;
    }

    display = al_create_display(SCREEN_W, SCREEN_H);
    if (!display) {
        fprintf(stderr, "failed to create display!\n");
        al_destroy_event_queue(event_queue);
        return -1;
    }

    al_clear_to_color(al_map_rgb(255, 0, 255));
    al_set_target_bitmap(al_get_backbuffer(display));

    al_register_event_source(event_queue, al_get_keyboard_event_source());

    while(running)
    {
        ALLEGRO_EVENT ev;

        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) // Cuando se presiona una tecla
        {
            switch (ev.keyboard.keycode) {
				case ALLEGRO_KEY_1:
					turnOnLED(0);
					break;
				case ALLEGRO_KEY_2:
					turnOnLED(1);
					break;
				case ALLEGRO_KEY_3:
					turnOnLED(2);
					break;
				case ALLEGRO_KEY_4:
					turnOnLED(3);
					break;
				case ALLEGRO_KEY_5:
					turnOnLED(4);
					break;
				case ALLEGRO_KEY_6:
					turnOnLED(5);
					break;
				case ALLEGRO_KEY_7:
					turnOnLED(6);
					break;
				case ALLEGRO_KEY_8:
					turnOnLED(7);
					break;
                case ALLEGRO_KEY_T:
					toggleAllLEDs();
                    break;
                case ALLEGRO_KEY_S:
                	turnOnAllLEDs();
                    break;
                case ALLEGRO_KEY_C:
                    turnOffAllLEDs();
                    break;
                case ALLEGRO_KEY_Q:
                	running = false;
                    break;
                default:
                    printf("Otra tecla\n");
                    break;
            }

            redraw = true;

        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
        	running = false;
        }


        if (redraw && al_is_event_queue_empty(event_queue)) {

            al_clear_to_color(al_map_rgb(50, 50, 50));

        	for(i = 0; i < NUM_PORTS; i++)
        	{
                float x = 50 + i * 90;
                float y = 50;
                float w = 60;
                float h = 60;

                ALLEGRO_COLOR color = getLedStatus(i)? al_map_rgb(0, 255, 0) : al_map_rgb(255, 0, 0);

                al_draw_filled_rectangle(x, y, x + w, y + h, color);
                al_draw_rectangle(x, y, x + w, y + h, al_map_rgb(255, 255, 255), 2);
        	}
        	redraw = false;
        }

        al_flip_display();

    }

    al_destroy_event_queue(event_queue);
    al_destroy_display(display);

    return 0;

}


