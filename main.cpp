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
#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;
//set size of the screen
#define ScreenWidth 1200		
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
	al_set_window_position(display, 100, 100);


	// set varaible

	bool done = false, draw = true, active = false;
	int x= 0, y = 0, moveSpeed = 50;
	int dir = DOWN;
	int score = 0;
	int questNumb=0;
	int answerNumb = 0;
	int count = 0;
	int chapNumb = 1;
	char playerAnswer;
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
	ALLEGRO_FONT *font18 = al_load_font("arial.ttf",16, 0);
	ALLEGRO_COLOR green = al_map_rgb(0, 255, 0);

	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_register_event_source(event_queue, al_get_display_event_source(display));

	// text file to array of strings
	
	string questArray[1105];
	short loop = 0;
	string line;
	ifstream inFile("questions.txt");
	
	if (inFile.is_open())
	{
		while (!inFile.eof())
		{
			getline(inFile, line);
			questArray[loop] = line;

			cout << questArray[loop] << endl;
			loop++;
		}
		inFile.close();
		inFile.clear();
	}
	else cout << "Can't open the file" << endl;

	// answer file to array of strings

	string answer[1100];
	short loop2 = 0;
	string line2;
	ifstream inFile2("answers.txt");

	if (inFile2.is_open())
	{
		while (!inFile2.eof())
		{
			getline(inFile2, line2);
			answer[loop2] = line2;

			cout << answer[loop2] << endl;
			loop2++;
		}
		inFile.close();
		inFile.clear();
	}
	else cout << "Can't open the file" << endl;

	// start screen
	al_draw_textf(font18, green, 70, 150, 0, "Welcome to My Trivia, please press Space to start the game");

	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));
	
	

	while (!done)
	{
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events);

		al_get_keyboard_state(&keyState);
		if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE | al_key_down(&keyState, ALLEGRO_KEY_ESCAPE))
		{
			done = true;
		}
		
			switch (y) {
			case 0:playerAnswer = 'A'; break;
			case 50:playerAnswer = 'B'; break;
			case 100:playerAnswer = 'C'; break;
			case 150:playerAnswer = 'D'; break;
			}

			if (draw)
			{
				al_draw_triangle(100, 200 + y, 100, 220 + y, 120, 210 + y, green, 2.0);

				al_draw_textf(font18, green, 70, 150, 0, (char*)questArray[questNumb].c_str());


				al_draw_textf(font18, green, 125, 200, 0, (char*)questArray[questNumb + 1].c_str());


				al_draw_textf(font18, green, 125, 250, 0, (char*)questArray[questNumb + 2].c_str());


				al_draw_textf(font18, green, 125, 300, 0, (char*)questArray[questNumb + 3].c_str());


				al_draw_textf(font18, green, 125, 350, 0, (char*)questArray[questNumb + 4].c_str());

				al_draw_textf(font18, green, 500, 500, 0, "Score: %i/%i", score, questNumb / 5);

				al_draw_textf(font18, green, 50, 50, 0, "Chapter: %i", chapNumb);



				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
				draw = false;

			}

			
		
			if (events.type == ALLEGRO_EVENT_KEY_DOWN){
				switch (events.keyboard.keycode)
				{
				case ALLEGRO_KEY_DOWN:
				{if (y < 150)
				{
					y += moveSpeed;
					al_play_sample(soundEffect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

				}};
				break;
				case ALLEGRO_KEY_UP:
				{if (y > 0)
				{
					y -= moveSpeed;
					al_play_sample(soundEffect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

				}};
				break;
				case ALLEGRO_KEY_ENTER:
				{
					

					if (answer[answerNumb].at(0) == playerAnswer)
					{
						score++;
						al_draw_textf(font18, green, 400, 400, 0, "Good answer!");
					}
					else al_draw_textf(font18, green, 400, 400, 0, "Wrong answer!");

					questNumb = questNumb + 5;
					answerNumb = answerNumb + 1;
					count++;
					if (count == 10){
						chapNumb++;
						count = 0;
					}
					
				};
				break;

				}

		draw = true;
			}
			
	}
	//destroy all pointers to avoid memory leaks
	al_destroy_display(display);
	al_destroy_sample(soundEffect);
	al_destroy_font(font18);
	al_destroy_sample(song);
	al_destroy_sample_instance(songInstance);
	al_destroy_event_queue(event_queue);



}
