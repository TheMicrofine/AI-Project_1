#ifndef _globalStuff_HG_
#define _globalStuff_HG_

#include "globalOpenGLStuff.h"

#include "behaviours/Entity.h"
#include "behaviours/cProperties.h"
#include "behaviours/cTransform.h"
#include "behaviours/cVelocity.h"
#include "behaviours/BehaviourManager.h"

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

#include <string>
#include <iostream>
#include <vector>

#include "sPlyVertex.h"
#include "sPlyTriangle.h"
#include "sModelDrawInfo.h"
#include "cVAOMeshManager.h"

#include "cLightManager.h"
#include "cCamera.h"
#include "cBasicTextureManager.h"

#include "CErrorLog.h"
#include "iDebugRenderer.h"

extern iDebugRenderer* g_pDebugRenderer;

extern cCamera* g_pCamera;

extern cVAOMeshManager* g_pVAOMeshManager;
extern cBasicTextureManager* g_pTextureManager;

extern std::vector<sLight*> g_Lights;
extern int g_LightIndex;

extern bool g_bDrawDebugLightSpheres;

void CreateLights(GLint program);

void LoadModelTypes(cVAOMeshManager* pTheVAOMeshManager, GLuint shaderProgramID);
void LoadModelsIntoScene();

void DrawObject(Entity* entity, glm::mat4x4& matModel, GLuint shaderProgramID);

extern BehaviourManager gBehaviourManager;
extern Transform* playerTransform;
extern double startTime;

//// *****************************************************************
//// This is part of the physics stuff
//// (really should be moved to the physics area, not here)
//struct sClosestPointData
//{
//	glm::vec3 thePoint;
//	unsigned int triangleIndex;
//};
//void CalculateClosestPointsOnMesh(sModelDrawInfo theMeshDrawInfo,
//	glm::vec3 pointToTest,
//	std::vector<sClosestPointData> &vecPoints);
//// *****************************************************************
//
//
////https://stackoverflow.com/questions/9878965/rand-between-0-and-1
//template <class T>
//T getRandBetween0and1(void)
//{
//	return (T)((double)rand() / (RAND_MAX));
//}
//
//// Inspired by: https://stackoverflow.com/questions/686353/c-random-float-number-generation
//template <class T>
//T getRandInRange(T min, T max)
//{
//	double value =
//		min + static_cast <double> (rand())
//		/ (static_cast <double> (RAND_MAX / (static_cast<double>(max - min))));
//	return static_cast<T>(value);
//}
#endif	// _globalStuff_HG_
