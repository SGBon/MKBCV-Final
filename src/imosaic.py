# MKBCV image mosaic generator
# substitutes pixels in image with other images matching the pixel's hue and saturation
import numpy as np
import cv2

import argparse

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Image Mosaic preprocessor')
    parser.add_argument('img', help='Image File')
    parser.add_argument('bank',help='root to bank of sorted images')
    args = parser.parse_args()

    bank_root = args.bank # bank of images to use for subtitution

    # load image and convert to HSV
    img = cv2.imread(args.img)
    hsv = cv2.cvtColor(img,cv2.COLOR_BGR2HSV)
    h,s,v = cv2.split(hsv)
    bins = np.linspace(0,180,20)
    print bins

    # iterate over every pixel
    for hue in h:
        # index the bins and look for image
        print "implement lookup"
