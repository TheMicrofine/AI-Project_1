#ifndef _HG_cProperties_
#define _HG_cProperties_

#include "Component.h"
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

struct sTextureInfo
{
	std::string name;
	int cachedTextureID;	// Set to -1 by default
	float strength;			// Set to 0.0f by default
};

class Properties : public Component
{
public:
	Properties();
	
	std::string meshName;

	glm::vec4 materialDiffuse;
	glm::vec4 materialSpecular;

	bool bIsVisible;
	bool bIsWireFrame;
	bool bDontLight;
	bool bUseVertexColour;

	std::vector<sTextureInfo> vecTextures;

	void setDiffuseColour(glm::vec3 newDiffuse);
};

#endif
