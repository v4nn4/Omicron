#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <windows.h>
#include <cstdint>
#include "quaternion.hpp"
#include "vector3d.hpp"
#include "polygon.hpp"
#include "coordinates.hpp"
#include "math.hpp"

struct win32_offscreen_buffer
{
	BITMAPINFO Info;
	void *Memory;
	int Width;
	int Height;
	int BytesPerPixel;
	int Pitch;
};

static bool Running;
static win32_offscreen_buffer GlobalBackBuffer;
static double aspect_ratio = 2.0;

struct win32_window_dimension
{
	int Width;
	int Height;
};

win32_window_dimension
GetWindowDimension(HWND Window)
{
	win32_window_dimension Result;
	RECT ClientRect;
	GetClientRect(Window, &ClientRect);
	Result.Width = ClientRect.right - ClientRect.left;
	Result.Height = ClientRect.bottom - ClientRect.top;
	return Result;
}

static void
SetPixel(win32_offscreen_buffer* Buffer, const int& x, const int& y, const uint32_t& color)
{
	uint32_t& row = reinterpret_cast<uint32_t&>(static_cast<uint8_t*>(Buffer->Memory)[Buffer->Pitch*y+4*x]);
	row = color;
}

static void
Render(win32_offscreen_buffer* Buffer, const polygon& pp, const polygon& fp)
{
	screen_coordinates sc{ aspect_ratio, Buffer->Width, Buffer->Height };
	int x, y;
	for (auto i = 0; i < pp.vertices.size(); ++i)
	{
		coordinates_utilities::world_to_screen(pp.vertices[i], sc, x, y);
		SetPixel(Buffer, x + 1, y, 0);
		SetPixel(Buffer, x, y, 0);
		SetPixel(Buffer, x - 1, y, 0);
		SetPixel(Buffer, x + 1, y + 1, 0);
		SetPixel(Buffer, x, y + 1, 0);
		SetPixel(Buffer, x - 1, y + 1, 0);
		SetPixel(Buffer, x + 1, y - 1, 0);
		SetPixel(Buffer, x, y - 1, 0);
		SetPixel(Buffer, x - 1, y - 1, 0);
	}
	uint32_t color;
	for (auto i = 0; i < fp.vertices.size(); ++i)
	{
		coordinates_utilities::world_to_screen(fp.vertices[i], sc, x, y);
		auto n = static_cast<uint32_t>(floor(0.5*(atan(fp.vertices[i].z *fp.vertices[i].z *fp.vertices[i].z * 100)*M_2_OVER_PI + 1) * 255));
		color = static_cast<uint32_t>(n) << 2 * 4 | 0x000000AA;
		SetPixel(Buffer, x + 1, y, color);
		SetPixel(Buffer, x, y, color);
		SetPixel(Buffer, x - 1, y, color);
		SetPixel(Buffer, x + 1, y + 1, color);
		SetPixel(Buffer, x, y + 1, color);
		SetPixel(Buffer, x - 1, y + 1, color);
		SetPixel(Buffer, x + 1, y - 1, color);
		SetPixel(Buffer, x, y - 1, color);
		SetPixel(Buffer, x - 1, y - 1, color);
	}
}

static void
ClearScreen(win32_offscreen_buffer* Buffer)
{
	for (auto y = 0; y < Buffer->Height;++y)
	{
		for (auto x = 0; x < Buffer->Width;++x)
		{
			SetPixel(Buffer, x, y, 0);
		}
	}
}

static void
Win32ResizeDIBSection(win32_offscreen_buffer *Buffer, int Width, int Height)
{
	if (Buffer->Memory)
	{
		VirtualFree(Buffer->Memory, 0, MEM_RELEASE);
	}

	Buffer->Width = Width;
	Buffer->Height = Height;

	Buffer->Info.bmiHeader.biSize = sizeof(Buffer->Info.bmiHeader);
	Buffer->Info.bmiHeader.biWidth = Buffer->Width;
	Buffer->Info.bmiHeader.biHeight = -Buffer->Height;
	Buffer->Info.bmiHeader.biPlanes = 1;
	Buffer->Info.bmiHeader.biBitCount = 32;
	Buffer->Info.bmiHeader.biCompression = BI_RGB;

	Buffer->BytesPerPixel = 4;
	int BitmapMemorySize = (Buffer->Width*Buffer->Height)*Buffer->BytesPerPixel;
	Buffer->Memory = VirtualAlloc(nullptr, BitmapMemorySize, MEM_COMMIT, PAGE_READWRITE);
	Buffer->Pitch = Buffer->Width*Buffer->BytesPerPixel;
}

static void
Win32DisplayBufferInWindow(HDC DeviceContext, int Width, int Height, win32_offscreen_buffer Buffer)
{
	StretchDIBits(DeviceContext,
		0, 0, Width, Height,
		0, 0, Buffer.Width, Buffer.Height,
		Buffer.Memory,
		&Buffer.Info,
		DIB_RGB_COLORS, SRCCOPY);
}

LRESULT CALLBACK
Win32MainWindowCallback(HWND Window,
UINT Message,
WPARAM WParam,
LPARAM LParam)
{
	LRESULT Result = 0;
	switch (Message)
	{
	case WM_SIZE:
	{
	} break;
	case WM_DESTROY:
	{
		OutputDebugStringA("WM_DESTROY\n");
	} break;
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		OutputDebugStringA("WM_CLOSE\n");
	} break;
	case WM_ACTIVATEAPP:
	{
		OutputDebugStringA("WM_ACTIVATEAPP\n");
	} break;
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
	case WM_KEYDOWN:
	case WM_KEYUP:
	{
		auto VKCode = WParam;
		auto WasDown = ((LParam & (1 << 30)) != 0);
		auto IsDown = ((LParam & (1 << 32)) == 0);
		switch (VKCode)
		{
			case VK_UP:
			{
				if (IsDown && !WasDown)
				{
					aspect_ratio *= 1.1;
					ClearScreen(&GlobalBackBuffer);
				}
			} break;
			case VK_DOWN:
			{
				if (IsDown && !WasDown)
				{
					aspect_ratio /= 1.1;
					ClearScreen(&GlobalBackBuffer);
				}
				//
			} break;
		}
	} break;
	case WM_PAINT:
	{
		PAINTSTRUCT Paint;
		auto DeviceContext = BeginPaint(Window, &Paint);
		auto Dimension = GetWindowDimension(Window);
		Win32DisplayBufferInWindow(DeviceContext, Dimension.Width, Dimension.Height, GlobalBackBuffer);
		EndPaint(Window, &Paint);
	}
	default:
	{
		Result = DefWindowProc(Window, Message, WParam, LParam);
	} break;
	}
	return Result;
}

int CALLBACK
WinMain(HINSTANCE hInstance,
HINSTANCE /*hPrevInstance*/,
LPSTR /*lpCmdLine*/,
int /*nCmdShow*/)
{
	WNDCLASS WindowClass = {};

	Win32ResizeDIBSection(&GlobalBackBuffer, 1288, 720);

	WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	WindowClass.lpfnWndProc = Win32MainWindowCallback;
	WindowClass.hInstance = hInstance;
	WindowClass.lpszClassName = "MandelbrotViewerWindowClass";

	if (RegisterClass(&WindowClass))
	{
		auto Window =
			CreateWindowEx(
			0,
			WindowClass.lpszClassName,
			"3DMotor",
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			nullptr,
			nullptr,
			hInstance,
			nullptr);

		vector3d u{ 0.0, 1.0, 0.0 };
		vector3d_utilities::normalize(u);
		auto angle = 0.001;
		auto p = polyhedra_utilities::generate_human_head();// polyhedra_utilities::generate_discrete_sphere(u,50);
		auto versor = quaternion_utilities::versor(u, angle);

		if (Window)
		{
			Running = true;
			while (Running)
			{
				MSG Message;
				while (PeekMessage(&Message, nullptr, 0, 0, PM_REMOVE))
				{
					if (Message.message == WM_QUIT)
					{
						Running = false;
					}
					TranslateMessage(&Message);
					DispatchMessageA(&Message);
				}
				auto DeviceContext = GetDC(Window);
				auto Dimension = GetWindowDimension(Window);
				Win32DisplayBufferInWindow(DeviceContext, Dimension.Width, Dimension.Height, GlobalBackBuffer);
				ReleaseDC(Window, DeviceContext);
				polygon pp{p.vertices};
				vector3d_utilities::rotate(p.vertices, versor);
				Render(&GlobalBackBuffer, pp, p);
			}
		}
		else
		{
			// TODO : Logging
		}
	}
	else
	{
		// TODO : Logging
	}

	return 0;
}
#else
int main(int argc, char *argv[]) {
	return 0;
}
#endif