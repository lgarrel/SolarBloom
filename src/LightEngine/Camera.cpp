#include "Camera.h"
#include "Player.h"

void Camera::Resize(float width, float height)
{
	mView.reset(sf::FloatRect(0, 0, width, height));
}

void Camera::FollowPlayer()
{
	if (!pOwner)
	{
		SetFocus(false);
		return;
	}
	SetPosition(pOwner->GetPosition());
}
