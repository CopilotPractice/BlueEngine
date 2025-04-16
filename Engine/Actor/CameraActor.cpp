#include "CameraActor.h"
#include "Component/CameraComponent.h"
#include "Core/InputController.h"
#include "Core/Engine.h"

namespace Blue
{
	CameraActor::CameraActor()
	{
		//ī�޶� ������Ʈ �߰�
		AddComponent(std::make_shared<CameraComponent>());
	}
	void CameraActor::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);

		//�̵�
		Move(deltaTime);

		//ȸ��
		Rotate(deltaTime);
	}
	void CameraActor::Move(float deltaTime)
	{
		// �Է� ������ ������ ����
		static InputController& input = InputController::Get();

		if (InputController::Get().IsKeyDown(VK_ESCAPE))
		{
			if (MessageBox(nullptr, TEXT("Want to Quit?"), TEXT("Quit Engine"), MB_YESNO) == IDYES)
			{
				Engine::Get().Quit(); // esc ������ ����
			}
		}

		// ī�޶� �̵� �ӷ�
		static float moveSpeed = 2.0f;

		//ī�޶� �̵�ó��           ... ������ ī�޶�� ������ �ϴ� �� �̻���
		if (input.IsKey('A') || input.IsKey(VK_LEFT))
		{
			//transform.position.x -= 1.0f * deltaTime;
			transform.position -= transform.Right() * moveSpeed * deltaTime;
		}

		if (input.IsKey('D') || input.IsKey(VK_RIGHT))
		{
			//transform.position.x += 1.0f * deltaTime;
			transform.position += transform.Right() * moveSpeed * deltaTime;
		}

		if (input.IsKey('W') || input.IsKey(VK_UP))
		{
			//transform.position.y += 1.0f * deltaTime;
			transform.position += transform.Up() * moveSpeed * deltaTime;
		}

		if (input.IsKey('S') || input.IsKey(VK_DOWN))
		{
			transform.position -= transform.Up() * moveSpeed * deltaTime;
		}

		if (input.IsKey('Q'))
		{
			//transform.position.z += 1.0f * deltaTime;
			transform.position += transform.Forward() * moveSpeed * deltaTime;

		}
		if (input.IsKey('E'))
		{
			//transform.position.z -= 1.0f * deltaTime;
			transform.position -= transform.Forward() * moveSpeed * deltaTime;

		}
	}
	void CameraActor::Rotate(float deltaTime)
	{
		// �Է� ������ ������ ����
		static InputController& input = InputController::Get();

		// ���콺 �巡�� Ȯ��
		if (input.IsBoutton(0))
		{
			// �巡�� ����
			static float sensitivity = 0.05f;

			//ī�޶� ���� ȸ��
			transform.rotation.x += input.GetMouseDeltaY() * sensitivity;
		
			//ī�޶� �¿� ȸ��
			transform.rotation.y += input.GetMouseDeltaX() * sensitivity;
		}
	}
}