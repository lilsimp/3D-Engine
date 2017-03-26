#include "Render.h"
#include "Shader.h"
#include "Mesh.h"
#include "Model.h"
#include "Transform.h"

static Shader* shader;
static Model models[MODEL_NUM];

/************************************************************/
/************************************************************/

void RenderInit(void) {
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	// Mesh drawing
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void RenderShutdown(void) {

}

void RenderLoad() {
	// Create and compile our GLSL program from the shaders
	shader = new Shader("Shaders/DeferredGeometry.vertexshader", "Shaders/DeferredGeometry.fragmentshader");

	models[CRATE_MODEL] = Model("Models/cube/cube.obj");
	models[NANOSUIT_MODEL] = Model("Models/nanosuit/nanosuit.obj");

}

void RenderUnload(void) {
	delete shader;
}

void RenderGameObjects(ObjectManager *pObjManager) {
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	std::vector< std::vector<GameObject*> >::iterator it;

	shader->Use();
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "projection"), 1, GL_FALSE, &pObjManager->WorldCam->Projection[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "view"), 1, GL_FALSE, &pObjManager->WorldCam->View[0][0]);

	// Loop through each game
	for (it = pObjManager->Objects.begin(); it !=  pObjManager->Objects.end(); ++it) {
		std::vector<GameObject*>::iterator Objs;
		for (Objs = (*it).begin(); Objs != (*it).end(); ++Objs) {

			GameObject* obj = (*Objs);
			Transform* trans = dynamic_cast<Transform*>(obj->GetComponent(TRANSFORM));

			// Transformation matrices
			glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, &trans->Model[0][0]);

			// Draw the loaded model
			models[obj->model].Draw(*shader);
		}
	}
}
