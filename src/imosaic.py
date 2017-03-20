# MKBCV image mosaic generator
# substitutes pixels in image with other images matching the pixel's hue and saturation
import numpy as np
import cv2

import argparse

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Image Mosaic preprocessor')
    parser.add_argument('img', help='Image File')
    args = parser.parse_args()

    img = cv2.imread(args.img)
