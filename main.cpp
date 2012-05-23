#include <cstdio>
#include <cstring>

#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>

#define V4L2_CTRL_CLASS_FLASH 0x009c0000
#define V4L2_CID_FLASH_CLASS_BASE   (V4L2_CTRL_CLASS_FLASH | 0x900)
#define    V4L2_CID_FLASH_TORCH_INTENSITY        (V4L2_CID_FLASH_CLASS_BASE + 8)
#define V4L2_CID_FLASH_LED_MODE     (V4L2_CID_FLASH_CLASS_BASE + 1)

enum v4l2_flash_led_mode {
    V4L2_FLASH_LED_MODE_NONE,
    V4L2_FLASH_LED_MODE_FLASH,
    V4L2_FLASH_LED_MODE_TORCH,
};



pthread_mutex_t mutex;
pthread_cond_t cond;
bool stopped;


void sig_stop(int)
{
    printf("Stop signal received\n");

    pthread_mutex_lock(&mutex);
    stopped = true;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
}



int main()
{
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    signal(SIGINT, sig_stop);
    signal(SIGTERM, sig_stop);
    printf("Signals set\n");

    int fd = open("/dev/v4l-subdev10", O_RDWR | O_NONBLOCK, 0);
    if (fd == -1)
    {
        fprintf(stderr, "can't open\n");
        return 1;
    }

    v4l2_control mode_ctrl;

    mode_ctrl.id = V4L2_CID_FLASH_LED_MODE;
    mode_ctrl.value = V4L2_FLASH_LED_MODE_TORCH;
    if (ioctl(fd, VIDIOC_S_CTRL, &mode_ctrl) == -1)
    {
        fprintf(stderr, "Can't set (%s)\n", strerror(errno));
        return 1;
    }


    pthread_mutex_lock(&mutex);
    stopped = false;
    while (! stopped)
        pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);

    printf("Stopping\n");


    mode_ctrl.id = V4L2_CID_FLASH_LED_MODE;
    mode_ctrl.value = V4L2_FLASH_LED_MODE_NONE;
    if (ioctl(fd, VIDIOC_S_CTRL, &mode_ctrl) == -1)
    {
        fprintf(stderr, "Can't set (%s)\n", strerror(errno));
        return 1;
    }


    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);
}
