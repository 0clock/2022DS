# 颜色二值化滤波例子
#
# 这个脚本展示了二值图像滤波。
# 您可以传递二进制任意的阈值来分割图像。

import sensor, image, time
from machine import UART

sensor.reset()
sensor.set_framesize(sensor.QVGA)
sensor.set_pixformat(sensor.GRAYSCALE)


#设置颜色阈值，如果是rgb图像，六个数字分别为(minL, maxL, minA, maxA, minB, maxB)；
#如果是灰度图，则只需设置（min, max）两个数字即可。
threshold = (220, 255)
sensor.skip_frames(time = 2000)
clock = time.clock()

ROI1 = (0,120,320,120)
uart = UART(1, baudrate=115200)


GRAYSCALE_THRESHOLD = [(0, 80)]

#使用工具 - >机器视觉 - >阈值编辑器选择更好的阈值。
while(True):
    clock.tick()
    img = sensor.snapshot()
    img.binary([threshold])
    blobs = img.find_blobs(GRAYSCALE_THRESHOLD,roi=ROI1 ,pixels_threshold=1000)
    for b in blobs :
        if b.w()>250:
            img.draw_rectangle(b.rect(),color=100)
            img.draw_cross(b.cx(),b.cy(),size=10,color=255)
            print(b.cy())
            uart_array = bytearray([0XFF,125,int((b.cy()-100))])
            uart.write(uart_array)
    #image.binary(thresholds, invert=False)此函数将在thresholds内的
    #图像部分的全部像素变为1白，将在阈值外的部分全部像素变为0黑。invert将图像
    #的0 1（黑 白）进行反转，默认为false不反转。
