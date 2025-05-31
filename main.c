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
#define FPS 4 // frecuencia de parpadeo

#define ERROR_MESSAGE "\nInput is not valid: Enter a valid character\n" // Mensaje de error en caso de ingreso invalido


int main(void)
{
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;

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

    timer = al_create_timer(1.0 / FPS);
    if(!timer)
    {
    	fprintf(stderr, "failed to create timer!\n");
    	return -1;
    }



    display = al_create_display(SCREEN_W, SCREEN_H);
    if (!display) {
        fprintf(stderr, "failed to create display!\n");
        al_destroy_event_queue(event_queue);
        return -1;
    }

    al_set_target_bitmap(al_get_backbuffer(display));

    al_register_event_source(event_queue, al_get_display_event_source(display)); // Registra el display como fuente de eventos
    al_register_event_source(event_queue, al_get_keyboard_event_source()); // Registra el teclado como fuente de eventos
    al_register_event_source(event_queue, al_get_timer_event_source(timer)); // Registra el timer como fuente de eventos

    bool running = true;
    bool blink_active = false;
    bool blink_state = true; // alterna entre mostrar u ocultar
    bool leds_to_blink[NUM_PORTS] = {false}; // cuáles parpadean

    int i;

    al_start_timer(timer);

    while(running)
    {
    	// Pinta los leds en el display
        al_clear_to_color(al_map_rgb(50, 50, 50));

        if (blink_active)
        {
            // guardar el estado de los LEDs al momento de activar parpadeo
            for (int i = 0; i < NUM_PORTS; i++)
            {
                leds_to_blink[i] = getLedStatus(i);
            }
        } else
        {
            // apagar todos los parpadeos
            for (int i = 0; i < NUM_PORTS; i++)
            {
                leds_to_blink[i] = false;
            }
        }

        for (i = 0; i < NUM_PORTS; i++) {
            float x = 90 + i * 90;
            float y = 100;
            float radius = 30;

            bool led_on = getLedStatus(i);

            if (blink_active && leds_to_blink[i]) {
                if (!blink_state) continue; // si está oculto, no lo dibujamos
            }

            ALLEGRO_COLOR color = led_on ? al_map_rgb(0, 255, 0) : al_map_rgb(255, 0, 0);

            al_draw_filled_circle(x, y, radius, color);
            al_draw_circle(x, y, radius, al_map_rgb(255, 255, 255), 2);
        }

        al_flip_display();

        // Registra eventos

        ALLEGRO_EVENT ev;

        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) // Cuando se quiere cerrar el display
        {
        	running = false;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) // Cuando se presiona una tecla
        {
            switch (ev.keyboard.keycode)
            {
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
                case ALLEGRO_KEY_B:
                    blink_active = !blink_active;
                    break;
                default:
                    printf(ERROR_MESSAGE);
                    break;
            }
        }
        else if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            if (blink_active)
            {
                blink_state = !blink_state; // cambiar visibilidad de LEDs parpadeantes
            }
        }

    }

    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);

    return 0;

}


