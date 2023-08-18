#pragma once
#include "Component.h"

class BoxCollider;
class SphereCollider;

class Collider : public Component
{
public:
	Collider(ColliderType colliderType);
	virtual ~Collider() override;

	virtual void BeginPlay() override;
	virtual void TickComponent() override;
	virtual void Render(HDC hdc) override;

	virtual bool CheckCollision(Collider* other);

	ColliderType GetColliderType() { return _colliderType; }
	void SetShowDebug(bool show) { _showDebug = show; }

public:
	static bool CheckCollisionBox2Box(BoxCollider* b1, BoxCollider* b2);
	static bool CheckCollisionSphere2Box(SphereCollider* s1, BoxCollider* b2);
	static bool CheckCollisionSphere2Sphere(SphereCollider* s1, SphereCollider* s2);

	void SetCollisionLayer(COLLISION_LAYER_TYPE layer) { _collisionLayer = layer; }
	COLLISION_LAYER_TYPE GetCollisionLayerType() { return _collisionLayer; }

	void SetCollisionFlag(uint32 flag) { _collisionFlag = flag; }
	uint32 GetCollisionFlag() { return _collisionFlag; }

	/* 모든 아이들과 충돌을 안하겠다 */
	void ResetCollisionFlag() { _collisionFlag = 0; } 
	/* 특정 아이와 충돌하겠다 */
	void AddCollisionFlagLayer(COLLISION_LAYER_TYPE layer); 
	/* 특정 아이와 충돌안하겠다 */
	void RemoveCollisionFlagLayer(COLLISION_LAYER_TYPE layer); 

protected:
	ColliderType _colliderType;
	bool _showDebug = true;

public:
	unordered_set<Collider*> _collisionMap;

	// 나는 누구인가?
	COLLISION_LAYER_TYPE _collisionLayer = CLT_OBJECT;
	// 누구랑 충돌할 것인가? bit flag
	uint32 _collisionFlag = 0xFFFFFFFF; // 모든 아이들과의 충돌을 허락한다
};

