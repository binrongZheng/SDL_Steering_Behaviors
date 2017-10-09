#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "SDL_SimpleApp.h"
#include "SceneKinematicSeek.h"
#include "SceneKinematicFlee.h"
#include "SceneSeek.h"
#include "SceneFlee.h"
#include "SceneArrival.h"
#include "SceneWander.h"
#include "ScenePursue.h"
#include "SceneEvade.h"
#include "ScenePathFollowing.h"
#include "SceneCombination.h"
#include "SceneCollisionAvoidance.h"

using namespace std;

int main(int argc, char ** argv)
{
	bool quit = false;
	SDL_Event event;

	SDL_SimpleApp *app = SDL_SimpleApp::Instance();

	Scene *curr_scene = new SceneKinematicSeek;
	app->setWindowTitle(curr_scene->getTitle());

	while (!quit)
	{
		// run app frame by frame
		event = app->run(curr_scene);

		/* Keyboard events */
		switch (event.type)
		{
		case SDL_KEYDOWN:
			if (event.key.keysym.scancode == SDL_SCANCODE_1)
			{
				delete(curr_scene);
				curr_scene = new SceneKinematicSeek;
				app->setWindowTitle(curr_scene->getTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_2)
			{
				delete(curr_scene);
				curr_scene = new SceneKinematicFlee;
				app->setWindowTitle(curr_scene->getTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_3)
			{
				delete(curr_scene);
				curr_scene = new SceneSeek;
				app->setWindowTitle(curr_scene->getTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_4)
			{
				delete(curr_scene);
				curr_scene = new SceneFlee;
				app->setWindowTitle(curr_scene->getTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_5)
			{
				delete(curr_scene);
				curr_scene = new SceneArrival;
				app->setWindowTitle(curr_scene->getTitle());
				
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_6)
			{
				delete(curr_scene);
				curr_scene = new SceneWander;
				app->setWindowTitle(curr_scene->getTitle());

			}
			if (event.key.keysym.scancode == SDL_SCANCODE_7)
			{
				delete(curr_scene);
				curr_scene = new ScenePursue;
				app->setWindowTitle(curr_scene->getTitle());

			}
			if (event.key.keysym.scancode == SDL_SCANCODE_8)
			{
				delete(curr_scene);
				curr_scene = new SceneEvade;
				app->setWindowTitle(curr_scene->getTitle());

			}
			
			if (event.key.keysym.scancode == SDL_SCANCODE_9)
			{
				delete(curr_scene);
				curr_scene = new ScenePathFollowing;
				app->setWindowTitle(curr_scene->getTitle());

			}

			if (event.key.keysym.scancode == SDL_SCANCODE_F1)
			{
				delete(curr_scene);
				curr_scene = new SceneCollisionAvoidance;
				app->setWindowTitle(curr_scene->getTitle());

			}
			
			if (event.key.keysym.scancode == SDL_SCANCODE_F2)
			{
				delete(curr_scene);
				curr_scene = new SceneCombination;
				app->setWindowTitle(curr_scene->getTitle());

			}

			if ((event.key.keysym.scancode == SDL_SCANCODE_Q) || (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
			{
				quit = true;
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_F)
			{
				app->setFullScreen();
			}
			break;
		case SDL_QUIT:
			quit = true;
			break;
		}

	}

	return 0;
}