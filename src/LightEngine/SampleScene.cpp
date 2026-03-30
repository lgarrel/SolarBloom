//#include "SampleScene.h"
//#include "PhysicalEntity.h"
//#include "DummyEntity.h"
//
//#include "Debug.h"
//
//void SampleScene::OnInitialize()
//{
//	pEntity1 = CreateEntity<PhysicalEntity>(50, sf::Color::Red);
//	pEntity1->SetPosition(640, 360);
//	pEntity1->SetRigidBody(false);
//	pEntity1->SetHitbox(200, 100);
//	pEntity1->SetIsHitboxActive(false);
//
//	pEntity2 = CreateEntity<PhysicalEntity>(50, sf::Color::Red);
//	pEntity2->SetPosition(400, 360);
//	pEntity2->SetRigidBody(false);
//	pEntity2->SetHitbox(100, 50);
//
//	pEntity3 = CreateEntity<PhysicalEntity>(50, sf::Color::Red);
//	pEntity3->SetPosition(880, 360);
//	pEntity3->SetRigidBody(false);
//	pEntity3->SetHitbox(150, 200);
//	pEntity3->SetHitboxOffset(50, 0);
//
//
//	pEntitySelected = nullptr;
//}
//
//void SampleScene::OnEvent(const sf::Event& event)
//{
//	if (event.type != sf::Event::EventType::MouseButtonPressed && event.type != sf::Event::EventType::KeyPressed)
//		return;
//
//	if (event.mouseButton.button == sf::Mouse::Button::Right)
//	{
//		TrySetSelectedEntity(pEntity1, event.mouseButton.x, event.mouseButton.y);
//		TrySetSelectedEntity(pEntity2, event.mouseButton.x, event.mouseButton.y);
//		TrySetSelectedEntity(pEntity3, event.mouseButton.x, event.mouseButton.y);
//	}
//
//	if (event.mouseButton.button == sf::Mouse::Button::Left)
//	{
//		if (pEntitySelected != nullptr)
//		{
//			pEntitySelected->GoToPosition(event.mouseButton.x, event.mouseButton.y, 100.f);
//		}
//	}
//
//	if (pEntitySelected != nullptr)
//	{
//		if (event.key.code == sf::Keyboard::H)
//		{
//			if (pEntitySelected->GetHitbox()->isActive)
//				pEntitySelected->SetIsHitboxActive(false);
//			else
//				pEntitySelected->SetIsHitboxActive();
//		}
//
//	}
//}
//
//void SampleScene::TrySetSelectedEntity(PhysicalEntity* pEntity, int x, int y)
//{
//	if (pEntity->IsInside(x, y) == false)
//		return;
//
//	pEntitySelected = pEntity;
//}
//
//void SampleScene::OnUpdate()
//{
//	if (pEntitySelected != nullptr)
//	{
//		sf::Vector2f position = pEntitySelected->GetPosition();
//		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
//	}
//}
