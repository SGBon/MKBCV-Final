# image mosaic preprocessor
# Converts an image to HSV, analyses their hue, and writes them to
# the folder with the range that the hue value falls into

import cv2
import numpy as np

import argparse
import os
if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Image Mosaic preprocessor')
    parser.add_argument('img', help='Image File')
    parser.add_argument('dest', help='Root folder to write the image to')
    args = parser.parse_args()

    root = args.dest

    # get directory delimiter based on os
    if os.name == 'nt':
        dirdelim = '\\'
    else:
        dirdelim = '/'
    if root[len(root)-1] != dirdelim: # if the root argument doesn't have the delimiter for directory
        root = root + dirdelim

    img = cv2.imread(args.img)
    hsv = cv2.cvtColor(img,cv2.COLOR_BGR2HSV)
    h,s,v = cv2.split(hsv)

    hist,edges = np.histogram(h,bins=20,range=(0,180)) # create histogram of hue values
    ind = np.argmax(hist) # index of largest bin in histogram

    # get path to location to write to
    path = root+str(int(edges[ind]))
    try:
        os.mkdir(path)
    except OSError: # directory exist from previous invocation, continue execution
        pass

    cv2.imwrite(path+dirdelim+args.img,img)
