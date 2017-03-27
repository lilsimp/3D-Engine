#include "Render.h"
#include "Shader.h"
#include "Mesh.h"
#include "Model.h"
#include "Transform.h"

static Shader* multiLights;
static Model models[MODEL_NUM];

/************************************************************/
/************************************************************/

static void setPointLight(glm::vec3 pos);

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
	multiLights = new Shader("Shaders/MultiLight.vs", "Shaders/MultiLight.fs");

	models[CRATE_MODEL] = Model("Models/crate/cube.obj");
	models[NANOSUIT_MODEL] = Model("Models/nanosuit/nanosuit.obj");
	models[POST_MODEL] = Model("Models/post/post.obj");

}

void RenderUnload(void) {
	delete multiLights;
}

void RenderGameObjects(ObjectManager *pObjManager) {
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	std::vector< std::vector<GameObject*> >::iterator it;

	multiLights->Use();
	glUniformMatrix4fv(glGetUniformLocation(multiLights->Program, "projection"), 1, GL_FALSE, &pObjManager->WorldCam->Projection[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(multiLights->Program, "view"), 1, GL_FALSE, &pObjManager->WorldCam->View[0][0]);


	GLint viewPosLoc = glGetUniformLocation(multiLights->Program, "viewPos");
	glUniform3f(viewPosLoc, pObjManager->WorldCam->Position.x, pObjManager->WorldCam->Position.y, pObjManager->WorldCam->Position.z);
	// Set material properties
	glUniform1f(glGetUniformLocation(multiLights->Program, "material.shininess"), 32.0f);
	// == ==========================
	// Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index 
	// the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
	// by defining light types as classes and set their values in there, or by using a more efficient uniform approach
	// by using 'Uniform buffer objects', but that is something we discuss in the 'Advanced GLSL' tutorial.
	// == ==========================
	// Directional light
	glUniform3f(glGetUniformLocation(multiLights->Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
	glUniform3f(glGetUniformLocation(multiLights->Program, "dirLight.ambient"), 0.2f, 0.2f, 0.2f);
	glUniform3f(glGetUniformLocation(multiLights->Program, "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
	glUniform3f(glGetUniformLocation(multiLights->Program, "dirLight.specular"), 0.15f, 0.15f, 0.15f);
	// Point light 
	//for (int i = 0; i < 4; ++i) 
		setPointLight(glm::vec3(10,4,10));

	// SpotLight
	glUniform3f(glGetUniformLocation(multiLights->Program, "spotLight.position"), pObjManager->WorldCam->Position.x, pObjManager->WorldCam->Position.y, pObjManager->WorldCam->Position.z);
	glUniform3f(glGetUniformLocation(multiLights->Program, "spotLight.direction"), pObjManager->WorldCam->Front.x, pObjManager->WorldCam->Front.y, pObjManager->WorldCam->Front.z);
	glUniform3f(glGetUniformLocation(multiLights->Program, "spotLight.ambient"), 0.001f, 0.001f, 0.001f);
	glUniform3f(glGetUniformLocation(multiLights->Program, "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(multiLights->Program, "spotLight.specular"), 1.0f, 1.0f, 1.0f);
	glUniform1f(glGetUniformLocation(multiLights->Program, "spotLight.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(multiLights->Program, "spotLight.linear"), 0.09);
	glUniform1f(glGetUniformLocation(multiLights->Program, "spotLight.quadratic"), 0.032);
	glUniform1f(glGetUniformLocation(multiLights->Program, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
	glUniform1f(glGetUniformLocation(multiLights->Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

	// Loop through each game
	for (it = pObjManager->Objects.begin(); it !=  pObjManager->Objects.end(); ++it) {
		std::vector<GameObject*>::iterator Objs;
		for (Objs = (*it).begin(); Objs != (*it).end(); ++Objs) {

			GameObject* obj = (*Objs);
			Transform* trans = dynamic_cast<Transform*>(obj->GetComponent(TRANSFORM));

			// Transformation matrices
			glUniformMatrix4fv(glGetUniformLocation(multiLights->Program, "model"), 1, GL_FALSE, &trans->Model[0][0]);

			// Draw the loaded model
			models[obj->model].Draw(*multiLights);
		}
	}
}

static void setPointLight(glm::vec3 pos) {
	glUniform3f(glGetUniformLocation(multiLights->Program, "pointLights[0].position"), pos.x, pos.y, pos.z);
	glUniform3f(glGetUniformLocation(multiLights->Program, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
	glUniform3f(glGetUniformLocation(multiLights->Program, "pointLights[0].diffuse"), 0.8f, 0.8f, 0.8f);
	glUniform3f(glGetUniformLocation(multiLights->Program, "pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
	glUniform1f(glGetUniformLocation(multiLights->Program, "pointLights[0].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(multiLights->Program, "pointLights[0].linear"), 0.09);
	glUniform1f(glGetUniformLocation(multiLights->Program, "pointLights[0].quadratic"), 0.032);
}
