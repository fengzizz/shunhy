#include "Renderer.h"

//#ifdef WIN32
//#include <Windows.h>
//typedef LPCWSTR DllString;
//typedef HMODULE DllHandle;
//#endif
namespace Shh
{
//	static const int gDrvDllCount = 2;
//#ifdef _DEBUG
//	DllString gDllName[gDrvDllCount] = {L"DrawDrv_d.dll", L"DrawDrv11_d.dll"};
//#else
//	DllString gDllName[gDrvDllCount] = {L"DrawDrv.dll", L"DrawDrv11.dll"};
//#endif
//
//	static DllHandle sDrvDll[gDrvDllCount] = {NULL, NULL};

	Renderer::Renderer()
		:mDriver(nullptr)
	{

	}

	Renderer::~Renderer()
	{

	}
	void Renderer::BeginScene()
	{
		shh_assert(mDriver);
		mDriver->DrawBegin();
	}
	void Renderer::EndScene()
	{
		shh_assert(mDriver);
		mDriver->DrawEnd();
	}

	void Renderer::SetShaderProgram(GPUProgram* program)
	{
		shh_assert(mDriver);
		mDriver->SetShaderProgram(program);
	}

	void Renderer::Draw(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, InputLayout* layout)
	{
		shh_assert(mDriver);
		mDriver->Draw(vertexBuffer, indexBuffer, layout);
	}

	void Renderer::Destroy()
	{
		g_RecycleRenderDevice(mDriver);
		mDriver = nullptr;

		//int index = (int)mDriver->GetDrawDrvType();
		//recycleDrvFunc func = nullptr;
		//func = (recycleDrvFunc)GetProcAddress (sDrvDll[index], "g_RecycleRenderDevice");
		//func(mDriver);
		//mDriver = nullptr;

		//for (int i = 0; i < gDrvDllCount; ++i)
		//{		
		//	if (sDrvDll[index])
		//	{
		//		FreeLibrary(sDrvDll[index]);
		//		sDrvDll[index] = nullptr;
		//	}
		//}

	}

	void Renderer::Setup(size_t width, size_t height, size_t handle, bool fullScrean, DrawDrvCode type)
	{
		//int index = (int)type;
		//n_assert(gDrvDllCount > index);
		//DllHandle& curr_dll = sDrvDll[index];
		//if (NULL == curr_dll)
		//{
		//	curr_dll = LoadLibrary(gDllName[index]);
		//}

		//if (curr_dll)
		//{
		//	createDrvFunc func = nullptr;
		//	func = (createDrvFunc)GetProcAddress (curr_dll, "g_CreateRenderDevice");
		//	if (func)
		//	{
				DRV_DESC desc;
				desc.width = width;
				desc.height = height;
				desc.full_screen = fullScrean;
				desc.stencil_buffer = true;
				desc.handle = handle;
				mDriver = g_CreateRenderDevice(desc);//mDriver = func(desc);
				if (mDriver->Initialize())
				{
					return;
				}
				else
				{
					//recycleDrvFunc rfunc = nullptr;
					//rfunc = (recycleDrvFunc)GetProcAddress (curr_dll, "g_RecycleRenderDevice");
					mDriver->Release();
					g_RecycleRenderDevice(mDriver);//rfunc(mDriver);
					mDriver = nullptr;
				}
		//	}
		//}


	}
}