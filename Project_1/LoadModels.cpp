#include "globalOpenGLStuff.h"
#include "globalStuff.h"
#include "ecs/EntityManager.h"
#include "ecs/bSeekBehaviour.h"
#include "ecs/bPursueBehaviour.h"
#include "ecs/bApproachBehaviour.h"
#include "ecs/bWanderBehaviour.h"

Transform* playerTransform;
Velocity* playerVelocity;
Transform* bulletTransform;
Velocity* bulletVelocity;

// Loading models was moved into this function
void LoadModelTypes(cVAOMeshManager* pTheVAOMeshManager, GLuint shaderProgramID)
{
	sModelDrawInfo sphereInfo;
	sphereInfo.meshFileName = "Sphere_n_uv.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(sphereInfo, shaderProgramID);

	sModelDrawInfo sphereInvertedNormalsInfo;
	sphereInvertedNormalsInfo.meshFileName = "Sphere_n_uv_INVERTED_NORMALS.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(sphereInvertedNormalsInfo, shaderProgramID);

	// At this point, mesh in in GPU
	std::cout << "Mesh was loaded OK" << std::endl;

	// Load the cube map
	::g_pTextureManager->SetBasePath("assets/textures/cubemaps");
	std::string errorString;
	if (::g_pTextureManager->CreateCubeTextureFromBMPFiles("CityCubeMap",
		"TropicalSunnyDayLeft2048.bmp", "TropicalSunnyDayRight2048.bmp",		// Alternate these
		"TropicalSunnyDayDown2048.bmp", "TropicalSunnyDayUp2048.bmp", 			// Rotate these 90 degrees
		"TropicalSunnyDayFront2048.bmp", "TropicalSunnyDayBack2048.bmp", true, errorString))
	{
		std::cout << "Loaded the city cube map OK" << std::endl;
	}
	else
	{
		std::cout << "Error: city cube map DIDN't load. On no!" << std::endl;
	}

	return;
}

// Loads the models we are drawing into the vector
void LoadModelsIntoScene()
{
	// ENTITY #0 - Skybox
	Entity* entity = EntityManager::CreateEntity();
	entity->name = "SkyBoxObject";

	Properties* properties = entity->AddComponent<Properties>();
	properties->setDiffuseColour(glm::vec3(1.0f, 1.0f, 0.0f));
	properties->meshName = "Sphere_n_uv_INVERTED_NORMALS.ply";
	properties->bIsVisible = false;

	Transform* transform = entity->AddComponent<Transform>();
	transform->position = glm::vec3(0.0f, 0.0f, 0.0f);
	transform->setUniformScale(5000.0f);
	transform->orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	entity->sphereRadius *= transform->scale.x;


	// ENTITY #1 - The Player
	Entity* entity1 = EntityManager::CreateEntity();
	entity1->name = "Player";

	Properties* properties1 = entity1->AddComponent<Properties>();
	properties1->setDiffuseColour(glm::vec3(0.0f, 0.0f, 0.0f));
	properties1->bDontLight = true;
	properties1->meshName = "Sphere_n_uv.ply";

	playerTransform = entity1->AddComponent<Transform>();
	playerTransform->position = glm::vec3(-250.0f, 300.0f, 0.0f);
	playerTransform->setUniformScale(15.0f);
	playerTransform->orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	entity1->sphereRadius = playerTransform->scale.x;

	playerVelocity = entity1->AddComponent<Velocity>();
	entity1->AddComponent<Velocity>();


	// ENTITY #2 - Seek
	Entity* entity2 = EntityManager::CreateEntity();
	entity2->name = "Seek";

	Properties* properties2 = entity2->AddComponent<Properties>();
	properties2->setDiffuseColour(glm::vec3(1.0f, 0.0f, 0.0f));						// SEEK == RED		FLEE == BLUE
	properties2->bDontLight = true;
	properties2->meshName = "Sphere_n_uv.ply";

	Transform* transform2 = entity2->AddComponent<Transform>();
	transform2->position = glm::vec3(100.0f, 0.0f, 0.0f);
	transform2->setUniformScale(15.0f);
	transform2->orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	entity2->sphereRadius = transform2->scale.x;

	entity2->AddComponent<Velocity>();
	gBehaviourManager.SetBehaviour(entity2, new SeekBehaviour(entity2, entity1));

	// ENTITY #3 - Pursue
	Entity* entity3 = EntityManager::CreateEntity();
	entity3->name = "Pursue";

	Properties* properties3 = entity3->AddComponent<Properties>();
	properties3->setDiffuseColour(glm::vec3(0.0f, 1.0f, 0.0f));							// PURSUE == GREEN		EVADE == YELLOW
	properties3->bDontLight = true;
	properties3->meshName = "Sphere_n_uv.ply";

	Transform* transform3 = entity3->AddComponent<Transform>();
	transform3->position = glm::vec3(-200.0f, 0.0f, 0.0f);
	transform3->setUniformScale(15.0f);
	transform3->orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	entity3->sphereRadius = transform3->scale.x;

	entity3->AddComponent<Velocity>();

	gBehaviourManager.SetBehaviour(entity3, new PursueBehaviour(entity3, entity1));

	// ENTITY #4 - Approach
	Entity* entity4 = EntityManager::CreateEntity();
	entity4->name = "Approach";

	Properties* properties4 = entity4->AddComponent<Properties>();
	properties4->setDiffuseColour(glm::vec3(1.0f, 0.0f, 1.0f));							// APPROACH == PURPLE
	properties4->bDontLight = true;
	properties4->meshName = "Sphere_n_uv.ply";

	Transform* transform4 = entity4->AddComponent<Transform>();
	transform4->position = glm::vec3(-1000.0f, 0.0f, 0.0f);
	transform4->setUniformScale(15.0f);
	transform4->orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	entity4->sphereRadius = transform4->scale.x;

	entity4->AddComponent<Velocity>();

	gBehaviourManager.SetBehaviour(entity4, new ApproachBehaviour(entity4, entity1));

	// ENTITY #5 - Wander
	Entity* entity5 = EntityManager::CreateEntity();
	entity5->name = "Wander";

	Properties* properties5 = entity5->AddComponent<Properties>();
	properties5->setDiffuseColour(glm::vec3(0.0f, 1.0f, 1.0f));							// WANDER == CYAN		IDLE == BROWN (150.0f/255.0f, 92.0f, 255.0f, 26.0f/255.0f)
	properties5->bDontLight = true;
	properties5->meshName = "Sphere_n_uv.ply";

	Transform* transform5 = entity5->AddComponent<Transform>();

	float xRand = rand() % 515 + (-1160);
	float yRand = rand() % 630 + (-115);

	transform5->position = glm::vec3(xRand, yRand, 0.0f);
	transform5->setUniformScale(15.0f);
	transform5->orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	entity5->sphereRadius = transform5->scale.x;

	entity5->AddComponent<Velocity>();

	gBehaviourManager.SetBehaviour(entity5, new WanderBehaviour(entity5));

	// ENTITY PLAYER BULLET
	{
		Entity* entity = EntityManager::CreateEntity();
		entity->name = "playerBullet";

		Properties* properties = entity->AddComponent<Properties>();
		properties->setDiffuseColour(glm::vec3(194.0f/155.0f, 64.0f/255.0f, 118.0f/255.0f));
		properties->bDontLight = true;
		properties->meshName = "Sphere_n_uv.ply";
		properties->bIsVisible = true;
		properties->bIsWireFrame = true;

		bulletTransform = entity->AddComponent<Transform>();
		bulletTransform->position = glm::vec3(-250.0f, 300.0f, 0.0f);
		bulletTransform->setUniformScale(10.0f);
		bulletTransform->orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
		entity->sphereRadius = bulletTransform->scale.x;

		bulletVelocity = entity->AddComponent<Velocity>();
	}


	// ENTITY #10 - Debug Sphere
	{
		Entity* entity = EntityManager::CreateEntity();
		entity->name = "DebugSphere";
		Properties* properties = entity->AddComponent<Properties>();
		properties->setDiffuseColour(glm::vec3(0.0f, 1.0f, 0.0f));
		properties->meshName = "Sphere_n_uv.ply";
		properties->bIsVisible = false;
		properties->bIsWireFrame = true;

		Transform* transform = entity->AddComponent<Transform>();
		transform->position = glm::vec3(0.0f, 0.0f, 0.0f);
		transform->setUniformScale(0.1f);
	}

	return;
}