#include "SceneGameover.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleScene.h"
#include "ModuleScene2.h"
#include "HUD.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneGameover::SceneGameover(bool startEnabled) : Module(startEnabled)
{

}

SceneGameover::~SceneGameover()
{

}

// Load assets
bool SceneGameover::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	App->hud->Disable();
	App->player->Disable();
	App->level1->Disable();
	App->level2->Disable();

	bgTexture = App->textures->Load("Assets/17_Game_Over.png");
	App->audio->PlayMusic("Assets/17_Game_Over.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;


	return ret;
}

update_status SceneGameover::Update()
{
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	GamePad& pad = App->input->pads[0];

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || pad.a){
		*App->player->getLives() = (*App->player->getLives() - 1);
		App->fade->FadeToBlack(this, (Module*)App->sceneShop, 60.0f);
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneGameover::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	return update_status::UPDATE_CONTINUE;
}


bool SceneGameover::CleanUp()
{
	//Enable (and properly disable) the player module
	
	App->textures->Unload(bgTexture);

	return true;
}