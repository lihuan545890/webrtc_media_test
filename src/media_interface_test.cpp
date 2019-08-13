

#include <stdio.h>
#include "media_interface.h"
#include <Windows.h>

#include <tchar.h>

//#include <process.h>


HWND g_local_view = NULL;
HWND g_remote_view = NULL;

LRESULT CALLBACK ViEAutoTestWinProc(HWND hWnd, UINT uMsg, WPARAM wParam,
	LPARAM lParam) {
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(WM_QUIT);
		break;
	case WM_COMMAND:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int create_window(HWND &hwndMain, int xPos,
	int yPos, int width, int height,
	TCHAR* className)
{
	HINSTANCE hinst = GetModuleHandle(0);
	WNDCLASSEX wcx;
	wcx.hInstance = hinst;
	wcx.lpszClassName = className;
	wcx.lpfnWndProc = (WNDPROC)ViEAutoTestWinProc;
	wcx.style = CS_DBLCLKS;
	wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcx.lpszMenuName = NULL;
	wcx.cbSize = sizeof(WNDCLASSEX);
	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.hbrBackground = GetSysColorBrush(COLOR_3DFACE);

	RegisterClassEx(&wcx);

	// Create the main window.
	hwndMain = CreateWindowEx(0,          // no extended styles
		className,  // class name
		className,  // window name
		WS_OVERLAPPED | WS_THICKFRAME,  // overlapped window
		xPos,    // horizontal position
		yPos,    // vertical position
		width,   // width
		height,  // height
		(HWND)NULL,   // no parent or owner window
		(HMENU)NULL,  // class menu used
		hinst,  // instance handle
		NULL);  // no window creation data

	if (!hwndMain)
		return -1;

	// Show the window using the flag specified by the program
	// that started the application, and send the application
	// a WM_PAINT message.
	ShowWindow(hwndMain, SW_SHOWDEFAULT);
	UpdateWindow(hwndMain);

	::SetWindowPos(hwndMain, HWND_TOP, xPos, yPos, width, height,
		SWP_FRAMECHANGED);

	return 0;
}

void trace_callback(char *str, int len)
{
	printf("APP TRACE %s\r\n", str);
}

int main(int argc, char **argv)
{
	int capture_id_1 = -1;
	int capture_id_2 = -1;
	int audio_channel_id = -1;
	int video_channel_id_1 = -1;
	int video_channel_id_2 = -1;

	printf("===== test begin =====\r\n");
	
	if (0 != create_window(g_local_view, 0, 0, 352, 288, _T("Local")))
	{
		printf("create_window fail\r\n");

		goto exit;
	}

	if (0 != create_window(g_remote_view, 0, 0, 640, 480, _T("Remote")))
	{
		printf("create_window fail\r\n");

		goto exit;
	}

	if (0 != media_init())
	{
		printf("media_init fail\r\n");

		goto exit;
	}

	if (0 != set_trace_call_back(trace_callback))
	{
		printf("media_init fail\r\n");

		goto exit;
	}


	if (0 != audio_init())
	{
		printf("audio_init fail\r\n");

		goto exit;
	}

	if (0 != audio_create_channel(&audio_channel_id))
	{
		printf("audio_create_channel fail\r\n");

		goto exit;
	}

	int codec_cnt;
	webrtc_audio_codec_info codecs[32];
	audio_get_codecs(codecs, &codec_cnt);

	if (0 != audio_start_send(audio_channel_id, "192.168.6.106", 8001))
	{
		printf("audio_set_receiver fail\r\n");

		goto exit;
	}

	if (0 != audio_start_receive(audio_channel_id, 8001))
	{
		printf("audio_set_receiver fail\r\n");

		goto exit;
	}


	if (0 != video_init())
	{
		printf("video_init fail\r\n");

		goto exit;
	}

//video 1	
	if (0 != video_create_channel(audio_channel_id, &video_channel_id_1))
	{
		printf("video_create_channel fail\r\n");

		goto exit;
	}
	
	if (0 != video_start_camera(video_channel_id_1, 0, &capture_id_1))
	{
		printf("video_start_camera fail\r\n");

		goto exit;
	}

	if (0 != video_start_local_render(video_channel_id_1, capture_id_1, g_local_view, 1, 0.0, 0.0, 1.0, 1.0))
	{
		printf("video_start_local_render fail\r\n");

		goto exit;
	}

	if (0 != video_start_remote_render(video_channel_id_1, g_remote_view, 1, 0.0, 0.0, 1.0, 1.0))
	{
		printf("video_start_remote_render fail\r\n");

		goto exit;
	}

	video_set_send_codec(video_channel_id_1, 100, "VP8", 640, 480, 150, 0, 30, 30);
	video_set_recv_codec(video_channel_id_1, 100, "VP8", 640, 480, 150, 0, 30, 30);

	if (0 != video_start_send(video_channel_id_1, "192.168.6.106", 9001))
	{
		printf("video_start_send fail\r\n");

		goto exit;
	}

	if (0 != video_start_receive(video_channel_id_1, 9001))
	{
		printf("video_start_receive fail\r\n");

		goto exit;
	}

#if 0

//video 2
	if (0 != video_create_channel(audio_channel_id, &video_channel_id_2))
	{
		printf("video_create_channel fail\r\n");

		goto exit;
	}

	if (0 != video_start_camera(video_channel_id_2, 0, &capture_id_1))
	{
		printf("video_start_camera fail\r\n");

		goto exit;
	}

	if (0 != video_start_local_render(video_channel_id_2, capture_id_1, g_local_view, 1, 0.0, 0.0, 1.0, 1.0))
	{
		printf("video_start_local_render fail\r\n");

		goto exit;
	}

	if (0 != video_start_remote_render(video_channel_id_2, g_remote_view, 1, 0.0, 0.0, 0.5, 0.5))
	{
		printf("video_start_remote_render fail\r\n");

		goto exit;
	}

	video_set_send_codec(video_channel_id_2, 100, "VP8", 640, 480, 100, 0, 30, 30);
	video_set_recv_codec(video_channel_id_2, 100, "VP8", 640, 480, 100, 0, 30, 30);

	if (0 != video_start_send(video_channel_id_2, "192.168.6.106", 9005))
	{
		printf("video_start_send fail\r\n");

		goto exit;
	}

	if (0 != video_start_receive(video_channel_id_2, 9005))
	{
		printf("video_start_receive fail\r\n");

		goto exit;
	}
#endif



	MSG msg;
	int i = 0;
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
		//printf("=========%d============\r\n", i++);
		
		Sleep(100);
	}
	

	audio_destroy_channel(audio_channel_id);
	video_destroy_channel(video_channel_id_1, capture_id_1);


	DestroyWindow(g_local_view);
	DestroyWindow(g_remote_view);

	return 0;

exit:
	getchar();
	return 0;
}
