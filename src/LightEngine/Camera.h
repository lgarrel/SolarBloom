#pragma once
#include <SFML/Graphics/View.hpp>

class Player;

class Camera
{
	sf::View mView;
	bool mFocusPlayer;

	Player* pOwner;
public:
	void SetPosition(const sf::Vector2f& pos) { mView.setCenter(pos); }
	void Move(float offsetX, float offsetY) { mView.move({ offsetX, offsetY }); }
	void Resize(float width, float height);
	bool GetFocus() { return mFocusPlayer; }
	void SetFocus(bool value) { mFocusPlayer = value; }
	void FollowPlayer();
	const sf::View* GetView() const { return &mView; }
	sf::Vector2f GetSize() { return mView.getSize(); }

	void SetOwner(Player* pPlayer) { pOwner = pPlayer; }
};

