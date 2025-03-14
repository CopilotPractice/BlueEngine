#include "Renderer.h"
#include <vector>
#include <d3dcompiler.h>

#include "../Math/Vector3.h"
#include "TriangleMesh.h"
#include "QuadMesh.h"
#include "Core/Common.h"

namespace Blue
{
	//                                                 창의 포인터
	Renderer::Renderer(uint32 width, uint32 height, HWND window)
	{
		// 장치 생성에 사용하는 옵션.
		uint32 flag = 0u;

#if _DEBUG
		flag |= D3D11_CREATE_DEVICE_DEBUG; // 디버그 모드일 때 flag
		                                   // 이렇게 지정해줘야 디버그 정보를 더 많이 줌
#endif

		// 생성할 라이브러리 버전.
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1, // 가장 맨처음 생성 시도 (실패하면 아래꺼)
			D3D_FEATURE_LEVEL_11_0,
		};

		D3D_FEATURE_LEVEL outFeatureLevel;

		// 장치 생성
		D3D11CreateDevice(
			nullptr,     //파라미터의 어댑터는 그래픽카드의 정보
			D3D_DRIVER_TYPE_HARDWARE, //
			nullptr,
			flag,
			featureLevels,
			_countof(featureLevels),
			D3D11_SDK_VERSION, //현재 버전에서 다이렉트x 설치된 버전을 알려줌
			&device,
			nullptr,     // outFeatureLevel, = feature 버전 알려줌
			&context
		);


		IDXGIFactory* factory = nullptr;
		//CreateDXGIFactory(__uuidof(factory), reinterpret_cast<void**>(&factory));
		ThrowIfFailed(CreateDXGIFactory(IID_PPV_ARGS(&factory))
		, TEXT("Faiiled to create dxgiiifactory."));
		

		// 스왑 체인 정보 구조체.
		DXGI_SWAP_CHAIN_DESC swapChainDesc = { };
		swapChainDesc.Windowed = true;		// 창 모드?.
		swapChainDesc.OutputWindow = window;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 2;		// 백버퍼 개수.
		swapChainDesc.SampleDesc.Count = 1;	// 멀티 샘플링 개수.
		swapChainDesc.SampleDesc.Quality = 0; // 멀티 샘플링 수준.
		swapChainDesc.BufferDesc.Width = width;
		swapChainDesc.BufferDesc.Height = height;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

		//D3D_FEATURE_LEVEL targetLevel;

		// 장치 생성.
		/*ThrowIfFailed(D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			flag,
			featureLevels,
			_countof(featureLevels),
			D3D11_SDK_VERSION,
			&swapChainDesc,
			&swapChain,
			&device,
			nullptr,
			&context
		), TEXT("Failed to create devices"));*/

		ThrowIfFailed(factory->CreateSwapChain(
			device,
			&swapChainDesc,
			&swapChain
		), TEXT("Failed to create a swap chain"));

		// 렌더 타겟 뷰 생성.
		ID3D11Texture2D* backbuffer = nullptr;


		ThrowIfFailed(swapChain->GetBuffer(0, IID_PPV_ARGS(&backbuffer))
			, TEXT("Failed to get back buffer"));

		
		ThrowIfFailed(device->CreateRenderTargetView(
			backbuffer, nullptr, &renderTargetView
		), TEXT("Failed to create render target view"));


		// 렌더 타겟 뷰 바인딩(연결).
		//context->OMSetRenderTargets(1, &renderTargetView, nullptr);

		// 뷰포트(화면).
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.Width = (float)width;
		viewport.Height = (float)height;
		viewport.MaxDepth = 1.0f;
		viewport.MinDepth = 0.0f;

		// 뷰포트 설정.
		context->RSSetViewports(1, &viewport);
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::Draw()
	{
		// @임시/Test
		if (mesh == nullptr)
		{
			//mesh = std::make_unique<TriangleMesh>();
			mesh = std::make_unique<QuadMesh>();
			mesh->transform.scale = Vector3::One * 0.5f;
			mesh->transform.position.x = 0.5f;
		}
		if (mesh2 == nullptr)
		{
			//mesh = std::make_unique<TriangleMesh>();
			mesh2 = std::make_unique<QuadMesh>();
			mesh2->transform.scale = Vector3::One * 0.5f;
			mesh2->transform.position.x = -0.5f;
		}

		if (mesh3 == nullptr)
		{
			//mesh = std::make_unique<TriangleMesh>();
			mesh3 = std::make_unique<TriangleMesh>();
			mesh3->transform.scale = Vector3::One * 0.5f;
			mesh3->transform.position.y = 0.5f;
		}



		// 그리기 전 작업 (BeginScene).
		context->OMSetRenderTargets(1, &renderTargetView, nullptr);

		// 지우기(Clear).
		float color[] = { 0.6f, 0.7f, 0.8f, 1.0f };
		context->ClearRenderTargetView(renderTargetView, color);

		// @Test.
		mesh->Update(1.0f / 60.0f);
		mesh2->Update(1.0f / 60.0f);

		// 드로우.
		mesh->Draw();
		mesh2->Draw();  //그려질 물체가 2개니까 update, draw 두번씩
		mesh3->Draw();

		// 버퍼 교환. (EndScene/Present).
		swapChain->Present(1u, 0u);
	}
}