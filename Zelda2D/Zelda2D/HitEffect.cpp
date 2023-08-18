#include "pch.h"
#include "HitEffect.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"

HitEffect::HitEffect()
{
	SetLayer(LAYER_EFFECT);
	UpdateAnimation();
}

HitEffect::~HitEffect()
{

}

void HitEffect::BeginPlay()
{
	Super::BeginPlay();
}

void HitEffect::Tick()
{
	Super::Tick();

	if (IsAnimationEnded())
	{
		Scene* scene = GET_SINGLE(SceneManager)->GetCurrentScene();
		scene->RemoveActor(this);
	}
}

void HitEffect::Render(HDC hdc)
{
	Super::Render(hdc);

}

void HitEffect::UpdateAnimation()
{
	SetFlipbook(GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Hit"));
}
