//Es necesario utilizar "extern c" para incluir -h files ffmpeg:
extern "C"
{
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <ffmpeg/swscale.h>
}

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
