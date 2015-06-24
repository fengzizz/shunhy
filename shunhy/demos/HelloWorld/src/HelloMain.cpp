#include <Windows.h>
#include "Core/FixArray.h"
#include "Core/Convert.h"
#include "Application/Application.h"
#include "RenderTest.h"

APPLICATION_FORCE_NvOptimusEnablement 

using namespace Shh;



class GameListener : public Shh::ApplicationListener
{
public:
	void OnStart()
	{		
		test::initRenderTest();
	}

	void OnStop()
	{

	}

	void OnExit()
	{

	}

	void OnScript()
	{

	}

};



int WINAPI wWinMain
(
	HINSTANCE hThisInst, //应用程序当前实例句柄
	HINSTANCE hPrevInst, //应用程序其它实例句柄
	LPWSTR lpszCmdLine, //指向程序命令行参数的指针
	int nCmdShow //应用程序开始执行时窗口显示方式的整数值标示
) 
{

	const int nBufSize = 512;
	TCHAR chBuf[nBufSize] = {0};

	ZeroMemory(chBuf,nBufSize);

	if (!GetModuleFileName(NULL,chBuf,nBufSize))  //获取的是当前EXE所在路径
	{
		return 1;
	}

	int index = nBufSize;
	int counter = 0;
	while(index)
	{
		if ('\\' == chBuf[index])
		{
			chBuf[index] = '/';
			++counter;
		}
		if (3 == counter)
		{
			chBuf[index] = 0;
			break;
		}
		--index;
	}
	while(index)
	{
		if ('\\' == chBuf[index])
		{
			chBuf[index] = '/';
		}
		--index;
	}

	U16String path = (utf16*)chBuf;

	path += UTEXT("/shunhy/media");

	U16String name((utf16*)L"Hello Word");

	GameListener* gl = new GameListener();


	APP_DESC desc;
	desc.hInstance = (size_t)hThisInst;
	desc.width = 800;
	desc.height = 600;
	desc.coord_x = 10;
	desc.coord_y = 10;
	desc.name = &name; 
	desc.working_path = &path;
	desc.listener = gl;
	
	//desc.update = Update;
	//desc.render = Render;
	Application app;
	app.Setup(desc);

	debug_output_line("hello world start.");
	app.Start();
	app.Run();
	app.Destroy();
	delete gl;
	debug_output_line("hello world exit.");
	return 0;
}