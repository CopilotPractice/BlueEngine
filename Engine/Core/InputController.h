#pragma once

#include "Math/Vector2.h" //���콺 Ŭ�� ��ġ�� �����ؾ��ϱ� ������ include

//�Է� ó�� ��� Ŭ����
namespace Blue
{
	//Ű �Է� ó���� ���� ����ü
	struct KeyInputData
	{
		// �Է� ���� ����
		bool isKeyDown = false;
		bool isKeyUp = false;
		bool isKey = false;

		//Ű �� ���� �Լ�
		void SetKeyUpDown(bool isKeyUp, bool isKeyDown)
		{
			this->isKeyUp = isKeyUp;
			this->isKeyDown = isKeyDown;

			isKey = isKeyDown && !isKeyUp;  //down�� �Ǿ��µ�, Up�� �ƴϸ� ���� ����

		}
	};

	//���콺 �Է�ó���� ���� ����ü
	struct MouseInputData
	{
		//���� ó���� �� �ε巴�� �Է� ���ӵ��� ó���ϴµ� ���⼱ �� ��

		// �Է� ���� ����
		bool isButtonDown = false;
		bool isButtonUp = false;
		bool isButton = false;

		void SetButtonUpDown(bool isButtonUp, bool isButtonDown)
		{
			this->isButtonUp = isButtonUp;
			this->isButtonDown = isButtonDown;

			isButton = isButtonDown && !isButtonUp;  //down�� �Ǿ��µ�, Up�� �ƴϸ� ���� ����

		}
	};

	//�Է� ������ Ŭ����
	class InputController
	{
	public:
		InputController();
		~InputController();
		
		//���� �Լ�
		//KeyCode -> ��ư ��(�� :'A')
		bool IsKeyDown(unsigned int keyCode);
		bool IsKeyUp(unsigned int keyCode);
		bool IsKey(unsigned int keyCode);

		//���콺 �Է� ���� �Լ�.
		bool IsBouttonDown(unsigned int Button);
		bool IsBouttonUp(unsigned int Button);
		bool IsBoutton(unsigned int Button);

		//�Է� ���� �Լ�
		void ResetInputs();

		Vector2 GetMousePosition();
		float GetMouseDeltaX();    // ���� ������ ��� �̵��� �Ÿ�(x)
		float GetMouseDeltaY();    // ���� ������ ��� �̵��� �Ÿ�(y)

		//�� ���� �Լ�
		void SetKeyUpDown(unsigned int keyCode, bool isKeyUp, bool isKeyDown);
		void SetButtonUpDown(unsigned int button, bool isButtonUp, bool isButtonDown);
		void SetMousePosition(int x, int y);

		//�̱����� ��Ȯ�ϰ� ���������, �����ϴ��� Ȯ���ؾ���
		//�̱��� ���� �Լ�
		static InputController& Get();
 
		//���� ����(��ȿ�� �Ǵ�)
		static bool IsVaild();

	private:

		// Ű/��ư �Է� ���� ����
		KeyInputData keyInputData[256];
		MouseInputData mouseInputData[3];

		//���콺 ��ġ ����.
		Vector2 mousePosition = Vector2::Zero;
		Vector2 mousePreviousPosition = Vector2::Zero; //�巡�׸� ���� ����(������ ��ġ) = delta ���ϱ� ���� ��


		//�̱��� ������ ���� ����
		static InputController* instance;
	};
}