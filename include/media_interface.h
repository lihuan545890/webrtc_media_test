
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
������  : media_init
����    : ý����ʼ��
����    : ��
����ֵ  : �ɹ�����MEDIA_SUCCESS������Ϊʧ��
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t media_init();

/*
********************************************************************************
������  : set_trace_call_back
����    : ������־�ص�����
����    : [IN] call_back �ص�����
����ֵ  : �ɹ�����MEDIA_SUCCESS������Ϊʧ��
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t set_trace_call_back(media_trace_callback call_back);

/*******************************     ��Ƶ���     *****************************/
/*
********************************************************************************
������  : audio_init
����    : ��ʼ����Ƶ
����    : ��
����ֵ  : �ɹ�����MEDIA_SUCCESS������Ϊʧ��
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t audio_init();

/*
********************************************************************************
������  : audio_deinit
����    : ��Ƶ����ʼ��
����    : ��
����ֵ  : ��
*******************************************************************************/
MEDIA_INTERFACE_API void audio_deinit();

/*
********************************************************************************
������  : audio_create_channel
����    : ������Ƶͨ����ÿ����Ƶ����Ӧһ����Ƶͨ��
����    : [OUT] channel_id : ͨ��ID
����ֵ  : �ɹ�����MEDIA_SUCCESS������Ϊʧ��
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t audio_create_channel(int *channel_id);

/*
********************************************************************************
������  : audio_destroy_channel
����    : �ݻ���Ƶͨ��
����    : [IN] channel_id : ͨ��ID
����ֵ  : �ɹ�����MEDIA_SUCCESS������Ϊʧ��
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t audio_destroy_channel(int channel_id);

/*
********************************************************************************
������  : audio_start_send
����    : ��ʼ������Ƶ��
����    : [IN] channel_id : ͨ��ID
		  [IN] ip : �Է�IP
		  [IN] port : �Է��˿�
����ֵ  : �ɹ�����MEDIA_SUCCESS������Ϊʧ��
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t audio_start_send(int channel_id, const char *ip, int port);

/*
********************************************************************************
������  : audio_stop_send
����    : ֹͣ������Ƶ��
����    : [IN] channel_id : ͨ��ID
����ֵ  : �ɹ�����MEDIA_SUCCESS������Ϊʧ��
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t audio_stop_send(int channel_id);

/*
********************************************************************************
������  : audio_start_receive
����    : ��ʼ������Ƶ��
����    : [IN] channel_id : ͨ��ID
		  [IN] port : ����rtp�˿�
����ֵ  : �ɹ�����MEDIA_SUCCESS������Ϊʧ��
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t audio_start_receive(int channel_id, int port);

/*
********************************************************************************
������  : audio_stop_receive
����    : ֹͣ������Ƶ��
����    : [IN] channel_id : ͨ��ID
����ֵ  : �ɹ�����MEDIA_SUCCESS������Ϊʧ��
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t audio_stop_receive(int channel_id);

/*
********************************************************************************
������  : audio_get_codecs_cnt
����    : ��ȡ֧�ֵ���Ƶ��������
����    : ��
����ֵ  : ����֧�ֵĸ���
*******************************************************************************/
MEDIA_INTERFACE_API int audio_get_codecs_cnt();

/*
********************************************************************************
������  : audio_get_codecs
����    : ��ȡ֧�ֵ���Ƶ�������Ϣ
����    : [OUT] info  : �������Ϣ����
		  [OUT] p_count  : ��������
����ֵ  : �ɹ�����MEDIA_SUCCESS������Ϊʧ��
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t audio_get_codecs(webrtc_audio_codec_info info[], int *p_count);

/*
********************************************************************************
������  : audio_set_send_codec
����    : ���÷��͵ı������Ϣ
����    : [IN] channel_id  : ͨ��ID
		  [IN] payload_type  : payload ����pcmu��Ӧ8
		  [IN] payload_name  : payload���� ����PCMU
����ֵ  : �ɹ�����MEDIA_SUCCESS������Ϊʧ��
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t audio_set_send_codec(int channel_id, int payload_type, char *payload_name, int plfreq, int pacsize, int channels, int rate);


/*******************************     ��Ƶ���     *****************************/
/*
********************************************************************************
������  : video_init
����    : ��Ƶ��ʼ��
����    : ��
����ֵ  : �ɹ�����MEDIA_SUCCESS������Ϊʧ��
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t video_init();

/*
********************************************************************************
������  : video_deinit
����    : ��Ƶ����ʼ��
����    : ��
����ֵ  : ��
*******************************************************************************/
MEDIA_INTERFACE_API void video_deinit();

/*
********************************************************************************
������  : video_create_channel
����    : ������Ƶ��ͨ��
����    : [IN] audio_channel_id  : ��Ӧ����Ƶͨ��ID��û����Ƶ������0
		  [OUT] video_channel_id  : ��������Ƶͨ��ID
����ֵ  : �ɹ�����MEDIA_SUCCESS������Ϊʧ��
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t video_create_channel(int audio_channel_id, int *video_channel_id);

/*
********************************************************************************
������  : video_destroy_channel
����    : ������Ƶ��ͨ��
����    : [IN] channel_id  : ͨ��ID
		  [IN] capture_id  : �ɼ�ID��û������0
����ֵ  : �ɹ�����MEDIA_SUCCESS������Ϊʧ��
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t video_destroy_channel(int channel_id, int capture_id);

/*
********************************************************************************
������  : video_start_camera
����    : ������ͷ
����    : [IN] channel_id  : ͨ��ID
		  [IN] camera_num  : ����ͷid
		  [OUT] capture_id ���ɼ�ID
����ֵ  : �ɹ�����MEDIA_SUCCESS������Ϊʧ��
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t video_start_camera(int channel_id, const int camera_num, int *capture_id);

/*
********************************************************************************
������  : video_start_local_render
����    : �򿪱�����Ƶ��Ⱦ����ʾ��
����    : [IN] channel_id  : ͨ��ID
		  [IN] capture_id ���ɼ�ID
		  [IN] window  : ��ʾ���ھ��
		  ��������ʾ�ڴ��ڵ�λ�� �� �� �� ��
����ֵ  : �ɹ�����MEDIA_SUCCESS������Ϊʧ��
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t video_start_local_render(int channel_id, int capture_id, void *window, const unsigned int z_order, const float left,
															const float top, const float right, const float bottom);
/*
********************************************************************************
������  : video_start_remote_render
����    : ��Զ����Ƶ��Ⱦ����ʾ��
����    : [IN] channel_id  : ͨ��ID
		  [IN] capture_id ���ɼ�ID
		  [IN] window  : ��ʾ���ھ��
		  ��������ʾ�ڴ��ڵ�λ�� �� �� �� ��
����ֵ  : �ɹ�����MEDIA_SUCCESS������Ϊʧ��
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t video_start_remote_render(int channel_id, void *window, const unsigned int z_order, const float left,
															const float top, const float right, const float bottom);
/*
********************************************************************************
������  : video_start_receive
����    : ��ʼ������Ƶ��
����    : [IN] channel_id  : ͨ��ID
		  [IN] port ������rtp�˿�
����ֵ  : �ɹ�����MEDIA_SUCCESS������Ϊʧ��
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t video_start_receive(int channel_id, int port);

/*
********************************************************************************
������  : video_stop_receive
����    : ֹͣ������Ƶ��
����    : [IN] channel_id  : ͨ��ID
����ֵ  : �ɹ�����MEDIA_SUCCESS������Ϊʧ��
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t video_stop_receive(int channel_id);

/*
********************************************************************************
������  : video_start_send
����    : ��ʼ������Ƶ��
����    : [IN] channel_id  : ͨ��ID
		  [IN] ip  : Զ��ip
		  [IN] port  : Զ�˶˿�
����ֵ  : �ɹ�����MEDIA_SUCCESS������Ϊʧ��
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t video_start_send(int channel_id, const char *ip, int port);

/*
********************************************************************************
������  : video_stop_send
����    : ֹͣ������Ƶ��
����    : [IN] channel_id  : ͨ��ID
����ֵ  : �ɹ�����MEDIA_SUCCESS������Ϊʧ��
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t video_stop_send(int channel_id);

/*
********************************************************************************
������  : video_get_codecs_cnt
����    : ��ȡ֧����Ƶ��������
����    : ��
����ֵ  : ���ظ���
*******************************************************************************/
MEDIA_INTERFACE_API int video_get_codecs_cnt();

/*
********************************************************************************
������  : video_get_codecs
����    : ��ȡ�������Ϣ
����    : [IN] info  : �������Ϣ
		  [OUT] p_count  : ��������
		  ����ֵ  : �ɹ�����MEDIA_SUCCESS������Ϊʧ��
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t video_get_codecs(webrtc_video_codec_info info[], int *p_count);

/*
********************************************************************************
������  : video_set_send_codec
����    : ���÷��͵ı����
����    : [IN] channel_id  : ͨ��ID
		  [IN] payload_type
		  [IN] payload_name
����ֵ  : �ɹ�����MEDIA_SUCCESS������Ϊʧ��
*******************************************************************************/
MEDIA_INTERFACE_API media_status_t video_set_send_codec(int channel_id, int payload_type, char *payload_name, int width, int height, int startBitrate, int maxBitrate, int minBitrate, int maxFramerate);
/*
********************************************************************************
������  : video_set_recv_codec
����    : ���ý��յı����
����    : [IN] channel_id  : ͨ��ID
		  [IN] payload_type
		  [IN] payload_name
����ֵ  : �ɹ�����MEDIA_SUCCESS������Ϊʧ��
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