# MKBCV image mosaic generator
# substitutes pixels in image with other images matching the pixel's hue and saturation
import numpy as np
import cv2

import imutil

import argparse

# produces a mosaic
def create_mosiac(img, tilesize):
    ret = np.zeros(img.shape)
    for i in range(img.shape[0]/tilesize[0]):
        for j in range(img.shape[1]/tilesize[1]):
            current_subgrid = img[(tilesize[0]*i):(tilesize[0]*(i+1)), (tilesize[0]*j):(tilesize[0]*(j+1))]
            ret[(tilesize[0]*i):(tilesize[0]*(i+1)), (tilesize[0]*j):(tilesize[0]*(j+1))] = current_subgrid

    return ret

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Image Mosaic preprocessor')
    parser.add_argument('img', help='Image File')
    parser.add_argument('bank',help='root to bank of sorted images')
    args = parser.parse_args()

    bank_root = args.bank # bank of images to use for subtitution

    # load image and convert to HSV
    img = cv2.imread(args.img)
    hsv = cv2.cvtColor(img,cv2.COLOR_BGR2HSV)

    tile = imutil.lookup_tile_by_hsv(hsv[0][0],bank_root,(32,32))

    # mosaic & display
    mosaiced = create_mosiac(img, [32,32])
    cv2.imwrite("output.jpg", mosaiced)
