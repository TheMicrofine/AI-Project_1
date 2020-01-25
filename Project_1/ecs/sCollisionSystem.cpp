//#include "sCollisionSystem.h"
//
//#include <math.h>
//
//#include "SphereCollider.h"
//#include "cTransform.h"
//
//struct CollisionPair
//{
//	CollisionPair(Entity* entityA, Entity* entityB) : entityA(entityA), entityB(entityB) { }
//
//	Entity* entityA;
//	Entity* entityB;
//};
//
//void CollisionSystem::Process(const std::vector<Entity*> &entities, float dt)
//{
//	Entity* entityA;
//	Entity* entityB;
//
//	Transform* transformA;
//	Transform* transformB;
//	SphereCollider* sphereColliderA;
//	SphereCollider* sphereColliderB;
//
//	std::vector<CollisionPair*> collisions;
//
//	unsigned int numEntities = entities.size();
//	for (unsigned int idxA = 0; idxA < numEntities; idxA++)
//	{
//		entityA = entities[idxA];
//
//		sphereColliderA = entityA->GetComponent<SphereCollider>();
//		transformA = entityA->GetComponent<Transform>();
//
//		if (sphereColliderA == 0 || transformA == 0) continue;
//
//		for (unsigned int idxB = idxA + 1; idxB < numEntities; idxB++)
//		{
//			entityB = entities[idxB];
//			sphereColliderB = entityB->GetComponent<SphereCollider>();
//			transformB = entityB->GetComponent<Transform>();
//
//			if (sphereColliderB == 0 || transformB == 0) continue;
//
//			if (TestSphereSphereCollision(transformA->position, sphereColliderA->radius, transformB->position, sphereColliderB->radius))
//			{
//#ifdef LOG_SYSTEMS
//				printf("Collision!\n");
//#endif
//				collisions.push_back(new CollisionPair(entityA, entityB));
//			}
//		}
//	}
//}
//
//bool CollisionSystem::TestSphereSphereCollision(const glm::vec3 &pA, float rA, const glm::vec3 &pB, float rB)
//{
//	float xDiff = pA.x - pB.x;
//	float yDiff = pA.y - pB.y;
//
//	float distance = sqrt(xDiff * xDiff + yDiff * yDiff);
//	float totalRadius = rA + rB;
//
//	return distance < totalRadius;
//}