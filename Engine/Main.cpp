#include "Core//Engine.h"
#include <iostream>

//#include "Math/Vector2.h"

using namespace Blue;
int main()
{
    // ���� ���� �� ����
    Engine engine(1280, 800, TEXT("ENGINE DEMO"), GetModuleHandle(nullptr));
    engine.Run();
}