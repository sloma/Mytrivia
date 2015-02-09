//============================================================================
// Name        : MyTriviacpp
// Author      : Salim Bouassida
// Description : Assignment 1 for COMP 369
//============================================================================
#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include<allegro5/allegro_audio.h>
#include<allegro5/allegro_acodec.h>
#include<string>

#include "questions.h"
using namespace std;
//set size of the screen
#define ScreenWidth 800
#define ScreenHeight 600

int main()
{

	

	enum Direction { DOWN,UP };

	

	if (!al_init())
		al_show_native_message_box(NULL, NULL, NULL, "failed to initialize allegro!", NULL, NULL);

	// create display

	ALLEGRO_DISPLAY*display;
	display = al_create_display(ScreenWidth, ScreenHeight);
	if (!display)
	al_show_native_message_box(display, NULL, NULL, "failed to create display!\n", NULL, NULL);
	al_set_window_position(display, 200, 200);


	// set varaible

	bool done = false, draw = true, active = false;
	const float FPS = 60.0;
	float x= 0, y = 0, moveSpeed = 50;
	int dir = DOWN;
	

	//install al
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_audio();
	al_init_acodec_addon();

	//sound
	ALLEGRO_SAMPLE *song= al_load_sample("gameMusic.wav");
	ALLEGRO_SAMPLE *soundEffect = al_load_sample("select.wav");
	
	al_reserve_samples(2);
	
	ALLEGRO_SAMPLE_INSTANCE *songInstance = al_create_sample_instance(song);

	al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());
	al_play_sample_instance(songInstance);
	
	//setup
	ALLEGRO_KEYBOARD_STATE keyState;
	//ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
	ALLEGRO_FONT *font18 = al_load_font("arial.ttf", 18, 0);
	ALLEGRO_COLOR green = al_map_rgb(0, 255, 0);

	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	//al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));

	// start screen
	al_draw_triangle(200, 200 + y, 200, 220 + y, 220, 210 + y, green, 2.0);

	al_draw_textf(font18, green, ScreenWidth / 2, 150, ALLEGRO_ALIGN_CENTER, char13);


	al_draw_textf(font18, green, 225, 200, 0, char13a);


	al_draw_textf(font18, green, 225, 250, 0, char13b);


	al_draw_textf(font18, green, 225, 300, 0, char13c);


	al_draw_textf(font18, green, 225, 350, 0, char13d);

	

	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));
	
	
	
//	al_start_timer(timer);
	while (!done)
	{
		
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events);

		al_get_keyboard_state(&keyState);
		if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE | al_key_down(&keyState, ALLEGRO_KEY_ESCAPE))
		{	
			done = true;
		}
		//else if (events.type == ALLEGRO_EVENT_TIMER)
	//	{
		if (events.type == ALLEGRO_EVENT_KEY_DOWN){ 
			switch (events.keyboard.keycode)
		{
		case ALLEGRO_KEY_DOWN:
		{if (y < 150)
		{
			y += moveSpeed;
			al_play_sample(soundEffect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
			draw = true;
		}};
		break;
		case ALLEGRO_KEY_UP:
		{if (y > 0)
		{
			y -= moveSpeed;
			al_play_sample(soundEffect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
			draw = true;
		}};
		break;

		}}
		
		
		//	draw = true;
	//	}
			if (draw)
			{
				al_draw_triangle(200, 200 + y, 200, 220 + y, 220, 210 + y, green, 2.0);

				al_draw_textf(font18, green, ScreenWidth / 2, 150, ALLEGRO_ALIGN_CENTER, char13);

				
				al_draw_textf(font18, green, 225, 200, 0, char13a);

				
				al_draw_textf(font18, green, 225, 250, 0, char13b);

				
				al_draw_textf(font18, green, 225, 300, 0, char13c);

				
				al_draw_textf(font18, green, 225, 350, 0, char13d);

				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
				draw = false;
				
			}
		
	}

	al_destroy_display(display);
	//al_destroy_timer(timer);
	al_destroy_sample(soundEffect);
	al_destroy_sample(song);
	al_destroy_sample_instance(songInstance);
	al_destroy_event_queue(event_queue);



}
