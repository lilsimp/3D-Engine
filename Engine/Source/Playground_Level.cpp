#include "Playground_Level.h"
#include "Components.h"
#include "Render.h"
#include "controls.h"

static void createCrate(GameObject* cube, glm::vec3 pos, glm::vec3 vel);

void Playground::Load(void)  {
	// Dark green background
	glClearColor(0.025f, 0.025f, 0.025f, 0.0f);
	
	RenderLoad();

	MainCam = new Camera(glm::perspective(45.0f, 16.0f / 9.0f, 0.1f, 600.0f),
		glm::lookAt(
			glm::vec3(50, 30, 70), // Camera position, in World Space
			glm::vec3(0, 0, 0),    // Point it looks at
			glm::vec3(0, 1, 0)     // Head is up (set to 0,-1,0 to look upside-down)
		));

	BaseManager = new ObjectManager(MainCam);
}  

void Playground::Init(void)  {
	GameObject* obj1 = BaseManager->CreateGameObject("GroundPlatform", CRATE_MODEL);
	Transform* ct1 = new Transform(obj1, glm::vec3(40,2,40));
	
	obj1 = BaseManager->CreateGameObject("NanoMan", NANOSUIT_MODEL);
	Transform* ct3 = new Transform(obj1, glm::vec3(2, 2, 2), glm::vec3(0, 2, 0));

	GameObject* post = BaseManager->CreateGameObject(std::string("Post"), POST_MODEL);
	glm::vec3 pos = glm::vec3(40,2,40);
	Transform* ct2 = new Transform(post, glm::vec3(8, 10, 8), pos);
	ct2->Rotation = glm::rotate(glm::cos(135.0f), glm::vec3(0,1,0));

	post = BaseManager->CreateGameObject(std::string("Post"), POST_MODEL);
	pos = glm::vec3(-40, 2, -40);
	ct2 = new Transform(post, glm::vec3(8, 10, 8), pos);
	ct2->Rotation = glm::rotate(glm::cos(45.0f), glm::vec3(0, -1, 0));

	post = BaseManager->CreateGameObject(std::string("Post"), POST_MODEL);
	pos = glm::vec3(40, 2, -40);
	ct2 = new Transform(post, glm::vec3(8, 10, 8), pos);
	ct2->Rotation = glm::rotate(glm::cos(225.0f), glm::vec3(0, 1, 0));

	post = BaseManager->CreateGameObject(std::string("Post"), POST_MODEL);
	pos = glm::vec3(-40, 2, 40);
	ct2 = new Transform(post, glm::vec3(8, 10, 8), pos);
	ct2->Rotation = glm::rotate(glm::cos(-225.0f), glm::vec3(0, -1, 0));

	for (int i = 0; i < 8; ++i) {
		GameObject* cube = BaseManager->CreateGameObject(std::string("Crate"), CRATE_MODEL);

		glm::vec3 pos = glm::vec3(-35.0f + (i * 10), 10.0f, -35.0f);

		Transform* ct = new Transform(cube, glm::vec3(2, 2, 2), pos);
		Physics* ph = new Physics(cube, glm::vec3(0, 0, 10), 3.5f);
		StrafeBehavior* cb = new StrafeBehavior(cube, pos, 80);
		RandRotationBehavior* r = new RandRotationBehavior(cube);
	}

	for (int i = 0; i < 8; ++i) {
		GameObject* cube = BaseManager->CreateGameObject(std::string("Crate"), CRATE_MODEL);

		glm::vec3 pos = glm::vec3(35.0f, 10.0f, 35.0f - (i * 10));

		Transform* ct = new Transform(cube, glm::vec3(2, 2, 2), pos);
		Physics* ph = new Physics(cube, glm::vec3(-10, 0, 0), 3.5f);
		StrafeBehavior* cb = new StrafeBehavior(cube, pos, 80);
		RandRotationBehavior* r = new RandRotationBehavior(cube);
	}

	for (int i = 0; i < 8; ++i) {
		GameObject* cube = BaseManager->CreateGameObject(std::string("Crate"), CRATE_MODEL);

		glm::vec3 pos = glm::vec3(-35.0f + (i * 10), 10.0f, 35.0f);

		Transform* ct = new Transform(cube, glm::vec3(2, 2, 2), pos);
		Physics* ph = new Physics(cube, glm::vec3(0, 0, -10), 3.5f);
		StrafeBehavior* cb = new StrafeBehavior(cube, pos, 80);
		RandRotationBehavior* r = new RandRotationBehavior(cube);
	}

	for (int i = 0; i < 8; ++i) {
		GameObject* cube = BaseManager->CreateGameObject(std::string("Crate"), CRATE_MODEL);

		glm::vec3 pos = glm::vec3(-35.0f, 10.0f, -35.0f + (i * 10));

		Transform* ct = new Transform(cube, glm::vec3(2, 2, 2), pos);
		Physics* ph = new Physics(cube, glm::vec3(10, 0, 0), 3.5f);
		StrafeBehavior* cb = new StrafeBehavior(cube, pos, 80);
		RandRotationBehavior* r = new RandRotationBehavior(cube);
	}


	BaseManager->EndFrame();
}

void Playground::Pause(void) {

}

void Playground::Resume(void) {

}

void Playground::InputHandler(void) {

}

void Playground::Update(void){
	computeMatricesFromInputs(MainCam);

	BaseManager->Update();
}

void Playground::Draw(void) {
	RenderGameObjects(BaseManager);

	BaseManager->EndFrame();
}

void Playground::Shutdown(void) {
	delete BaseManager;
}

void Playground::Unload(void){
	RenderUnload();
}

static void createCrate(GameObject* cub, glm::vec3 pos, glm::vec3 vel) {

}
