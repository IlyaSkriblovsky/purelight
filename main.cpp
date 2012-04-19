#include <cstdio>
#include <cstring>

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


#include <X11/Xlib.h>

int main()
{
    Display* d = XOpenDisplay(0);
    Window root = RootWindow(d, DefaultScreen(d));
    Window w = XCreateSimpleWindow(
        d, root, 10, 10, 100, 100, 0, 0, 0
    );
    XMapWindow(d, w);
    XSync(d, 0);
    XUnmapWindow(d, w);
    XSync(d, 0);
    XDestroyWindow(d, w);
    XSync(d, 0);

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

    sleep(60);
}
