
#ifndef _MEDIA_INTERFACE_H_
#define _MEDIA_INTERFACE_H_


#ifdef _WIN32
#define MEDIA_INTERFACE_API __declspec(dllexport)
#else
#define SIP_UA_DLL_API __attribute__ ((visibility("default")))
#endif

#ifdef __cplusplus
extern "C"
{
#endif


typedef struct
{
	int  index;
	char payload_name[32];
	int payload_type;
	int plfreq;
	int pacsize;
	int channels;
	int rate;
}webrtc_audio_codec_info;

typedef struct  
{
	int index;
	char payload_name[32];
	int payload_type;
	int width;
	int height;
	int start_bitrate;
	int max_bitrate;
	int min_bitrate;
	int max_framerate;
}webrtc_video_codec_info;


typedef int		media_status_t;

/** Some constants */
enum media_constants
{
	/** Status is OK. */
	MEDIA_SUCCESS = 0,

	/** Status is NOT OK. */
	MEDIA_FAIL = -1,

	/** True value. */
	MEDIA_TRUE = 1,

	/** False value. */
	MEDIA_FALSE = 0
};
typedef void(*media_trace_callback)(char *str, int len);


/*
********************************************************************************
函数名  : media_init
功能    : 媒体库初始化
参数    : 无
返回值  : 成功返回MEDIA_SUCCESS，否则为失败
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t media_init();

/*
********************************************************************************
函数名  : set_trace_call_back
功能    : 设置日志回调函数
参数    : [IN] call_back 回调函数
返回值  : 成功返回MEDIA_SUCCESS，否则为失败
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t set_trace_call_back(media_trace_callback call_back);

/*******************************     音频相关     *****************************/
/*
********************************************************************************
函数名  : audio_init
功能    : 初始化音频
参数    : 无
返回值  : 成功返回MEDIA_SUCCESS，否则为失败
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t audio_init();

/*
********************************************************************************
函数名  : audio_deinit
功能    : 音频反初始化
参数    : 无
返回值  : 无
*******************************************************************************/
MEDIA_INTERFACE_API void audio_deinit();

/*
********************************************************************************
函数名  : audio_create_channel
功能    : 创建音频通道，每个音频流对应一个音频通道
参数    : [OUT] channel_id : 通道ID
返回值  : 成功返回MEDIA_SUCCESS，否则为失败
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t audio_create_channel(int *channel_id);

/*
********************************************************************************
函数名  : audio_destroy_channel
功能    : 摧毁音频通道
参数    : [IN] channel_id : 通道ID
返回值  : 成功返回MEDIA_SUCCESS，否则为失败
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t audio_destroy_channel(int channel_id);

/*
********************************************************************************
函数名  : audio_start_send
功能    : 开始发送音频流
参数    : [IN] channel_id : 通道ID
		  [IN] ip : 对方IP
		  [IN] port : 对方端口
返回值  : 成功返回MEDIA_SUCCESS，否则为失败
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t audio_start_send(int channel_id, const char *ip, int port);

/*
********************************************************************************
函数名  : audio_stop_send
功能    : 停止发送音频流
参数    : [IN] channel_id : 通道ID
返回值  : 成功返回MEDIA_SUCCESS，否则为失败
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t audio_stop_send(int channel_id);

/*
********************************************************************************
函数名  : audio_start_receive
功能    : 开始接收音频流
参数    : [IN] channel_id : 通道ID
		  [IN] port : 本地rtp端口
返回值  : 成功返回MEDIA_SUCCESS，否则为失败
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t audio_start_receive(int channel_id, int port);

/*
********************************************************************************
函数名  : audio_stop_receive
功能    : 停止接收音频流
参数    : [IN] channel_id : 通道ID
返回值  : 成功返回MEDIA_SUCCESS，否则为失败
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t audio_stop_receive(int channel_id);

/*
********************************************************************************
函数名  : audio_get_codecs_cnt
功能    : 获取支持的音频编解码个数
参数    : 无
返回值  : 返回支持的个数
*******************************************************************************/
MEDIA_INTERFACE_API int audio_get_codecs_cnt();

/*
********************************************************************************
函数名  : audio_get_codecs
功能    : 获取支持的音频编解码信息
参数    : [OUT] info  : 编解码信息数组
		  [OUT] p_count  : 编解码个数
返回值  : 成功返回MEDIA_SUCCESS，否则为失败
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t audio_get_codecs(webrtc_audio_codec_info info[], int *p_count);

/*
********************************************************************************
函数名  : audio_set_send_codec
功能    : 设置发送的编解码信息
参数    : [IN] channel_id  : 通道ID
		  [IN] payload_type  : payload 比如pcmu对应8
		  [IN] payload_name  : payload名称 比如PCMU
返回值  : 成功返回MEDIA_SUCCESS，否则为失败
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t audio_set_send_codec(int channel_id, int payload_type, char *payload_name, int plfreq, int pacsize, int channels, int rate);


/*******************************     视频相关     *****************************/
/*
********************************************************************************
函数名  : video_init
功能    : 视频初始化
参数    : 无
返回值  : 成功返回MEDIA_SUCCESS，否则为失败
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t video_init();

/*
********************************************************************************
函数名  : video_deinit
功能    : 视频反初始化
参数    : 无
返回值  : 无
*******************************************************************************/
MEDIA_INTERFACE_API void video_deinit();

/*
********************************************************************************
函数名  : video_create_channel
功能    : 创建视频流通道
参数    : [IN] audio_channel_id  : 对应的音频通道ID，没有音频流则填0
		  [OUT] video_channel_id  : 创建的视频通道ID
返回值  : 成功返回MEDIA_SUCCESS，否则为失败
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t video_create_channel(int audio_channel_id, int *video_channel_id);

/*
********************************************************************************
函数名  : video_destroy_channel
功能    : 销毁视频流通道
参数    : [IN] channel_id  : 通道ID
		  [IN] capture_id  : 采集ID，没有则填0
返回值  : 成功返回MEDIA_SUCCESS，否则为失败
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t video_destroy_channel(int channel_id, int capture_id);

/*
********************************************************************************
函数名  : video_start_camera
功能    : 打开摄像头
参数    : [IN] channel_id  : 通道ID
		  [IN] camera_num  : 摄像头id
		  [OUT] capture_id ：采集ID
返回值  : 成功返回MEDIA_SUCCESS，否则为失败
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t video_start_camera(int channel_id, const int camera_num, int *capture_id);

/*
********************************************************************************
函数名  : video_start_local_render
功能    : 打开本地视频渲染（显示）
参数    : [IN] channel_id  : 通道ID
		  [IN] capture_id ：采集ID
		  [IN] window  : 显示窗口句柄
		  其他：显示在窗口的位置 左 上 右 下
返回值  : 成功返回MEDIA_SUCCESS，否则为失败
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t video_start_local_render(int channel_id, int capture_id, void *window, const unsigned int z_order, const float left,
															const float top, const float right, const float bottom);
/*
********************************************************************************
函数名  : video_start_remote_render
功能    : 打开远端视频渲染（显示）
参数    : [IN] channel_id  : 通道ID
		  [IN] capture_id ：采集ID
		  [IN] window  : 显示窗口句柄
		  其他：显示在窗口的位置 左 上 右 下
返回值  : 成功返回MEDIA_SUCCESS，否则为失败
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t video_start_remote_render(int channel_id, void *window, const unsigned int z_order, const float left,
															const float top, const float right, const float bottom);
/*
********************************************************************************
函数名  : video_start_receive
功能    : 开始接收视频流
参数    : [IN] channel_id  : 通道ID
		  [IN] port ：本地rtp端口
返回值  : 成功返回MEDIA_SUCCESS，否则为失败
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t video_start_receive(int channel_id, int port);

/*
********************************************************************************
函数名  : video_stop_receive
功能    : 停止接收视频流
参数    : [IN] channel_id  : 通道ID
返回值  : 成功返回MEDIA_SUCCESS，否则为失败
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t video_stop_receive(int channel_id);

/*
********************************************************************************
函数名  : video_start_send
功能    : 开始发送视频流
参数    : [IN] channel_id  : 通道ID
		  [IN] ip  : 远端ip
		  [IN] port  : 远端端口
返回值  : 成功返回MEDIA_SUCCESS，否则为失败
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t video_start_send(int channel_id, const char *ip, int port);

/*
********************************************************************************
函数名  : video_stop_send
功能    : 停止发送视频流
参数    : [IN] channel_id  : 通道ID
返回值  : 成功返回MEDIA_SUCCESS，否则为失败
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t video_stop_send(int channel_id);

/*
********************************************************************************
函数名  : video_get_codecs_cnt
功能    : 获取支持视频编解码个数
参数    : 无
返回值  : 返回个数
*******************************************************************************/
MEDIA_INTERFACE_API int video_get_codecs_cnt();

/*
********************************************************************************
函数名  : video_get_codecs
功能    : 获取编解码信息
参数    : [IN] info  : 编解码信息
		  [OUT] p_count  : 编解码个数
		  返回值  : 成功返回MEDIA_SUCCESS，否则为失败
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t video_get_codecs(webrtc_video_codec_info info[], int *p_count);

/*
********************************************************************************
函数名  : video_set_send_codec
功能    : 设置发送的编解码
参数    : [IN] channel_id  : 通道ID
		  [IN] payload_type
		  [IN] payload_name
返回值  : 成功返回MEDIA_SUCCESS，否则为失败
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t video_set_send_codec(int channel_id, int payload_type, char *payload_name, int width, int height, int startBitrate, int maxBitrate, int minBitrate, int maxFramerate);
/*
********************************************************************************
函数名  : video_set_recv_codec
功能    : 设置接收的编解码
参数    : [IN] channel_id  : 通道ID
		  [IN] payload_type
		  [IN] payload_name
返回值  : 成功返回MEDIA_SUCCESS，否则为失败
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t video_set_recv_codec(int channel_id, int payload_type, char *payload_name, int width, int height, int startBitrate, int maxBitrate, int minBitrate, int maxFramerate);



#if defined(WEBRTC_ANDROID)
MEDIA_INTERFACE_API int audio_set_android_objects(void* javaVM, void* env, void* context);
MEDIA_INTERFACE_API int video_set_android_objects(void* javaVM, void* context);
#endif



#ifdef __cplusplus
}
#endif


#endif