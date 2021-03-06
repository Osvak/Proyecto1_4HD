#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include <SDL_mixer\include\SDL_mixer.h>

SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled)
{

}

SceneIntro::~SceneIntro()
		
{
	
}

// Load assets
bool SceneIntro::Start()
{
	LOG("Loading background assets");



	bool ret = true;

	bgTexture = App->textures->Load("Assets/Intro/Star_Menu_Sprite.png");	
	App->audio->PlayMusic("Assets/01_Introduction.ogg", 1.0f);

	App->render->camera.x, App->render->camera.y = 0;

	for (int i = 0; i < 4; i++)
	Uni_Fire.PushBack({510*i,0,510,443});

	
	Uni_Fire.speed = 0.1f;
	Uni_Fire.loop = true;
	currentAnim = &Uni_Fire;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

update_status SceneIntro::Update(){
	GamePad& pad = App->input->pads[0];

	if (currentAnim != nullptr){
		currentAnim->Update();
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || pad.a){
		Mix_HaltMusic();
		//Mix_FreeMusic(App->audio->getMusic());

		//Empezar Nivel
		App->fade->FadeToBlack(this, (Module*)App->sceneShop, 60.0f);
		//App->fade->FadeToBlack(this, (Module*)App->level2, 60.0f);
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneIntro::PostUpdate()
{	
	
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(bgTexture, 0, 0, &(currentAnim->GetCurrentFrame()));
	return update_status::UPDATE_CONTINUE;
}


bool SceneIntro::CleanUp()
{
	//Enable (and properly disable) the player module
	App->textures->Unload(bgTexture);
	bgTexture = NULL;

	return true;
}
