//Es necesario utilizar "extern c" para incluir -h files ffmpeg:
extern "C"
{
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <ffmpeg/swscale.h>
}

using namespace std;

// Register all components of FFmpeg
av_register_all();

// Open file
if (av_open_input_file(&pFormatCtx, inputFile.c_str(), NULL, 0, NULL) != 0)
{
   CloseFile();
   return false;
}
// Get infromation about streams
if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
{
   CloseFile();
   return false;
}

// # video stream
videoStreamIndex = -1;
for (unsigned int i = 0; i < pFormatCtx->nb_streams; i++)
{
   if (pFormatCtx->streams[i]->codec->codec_type == CODEC_TYPE_VIDEO)
   {
     videoStreamIndex = i;
     pVideoCodecCtx = pFormatCtx->streams[i]->codec;
     // Find decoder
     pVideoCodec = avcodec_find_decoder(pVideoCodecCtx->codec_id);
     if (pVideoCodec)
     {
       // Open decoder
       res = !(avcodec_open2(pVideoCodecCtx, pVideoCodec, NULL) < 0);
       width = pVideoCodecCtx->coded_width;
       height = pVideoCodecCtx->coded_height;
     }
     break;
   }
}

// FPS
videoFramePerSecond =
av_q2d(pFormatCtx->streams[videoStreamIndex]->r_frame_rate);
// Base time unit
videoBaseTime =
av_q2d(pFormatCtx->streams[videoStreamIndex]->time_base);
// Duration of video clip
videoDuration = (unsigned long)
pFormatCtx->streams[videoStreamIndex]->duration * (videoFramePerSecond *
videoBaseTime);
// Frame width
width = formatCtx->streams[videoStreamIndex]->codec->width;
// Frame height
height = formatCtx->streams[videoStreamIndex]->codec->height;

while (av_read_frame(pFormatCtx, &packet) >= 0)

if(packet.stream_index == videoStreamIndex)

// Decode packeg to frame.
AVFrame * pOutFrame;
int videoFrameBytes = avcodec_decode_video2(pVideoCodecCtx, pOutFrame,
&got_picture_ptr, avpkt);

int packetDecodedSize = avcodec_decode_audio4(pAudioCodecCtx,
audioFrame, &got_picture_ptr, avpkt);

// close video codec
avcodec_close(pVideoCodecCtx);
// close audio codec
avcodec_close(pAudioCodecCtx);
// close file
av_close_input_file(pFormatCtx);


int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
