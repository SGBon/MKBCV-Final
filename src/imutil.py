# utility functions for image mosaic generator

import os
import numpy as np
from scipy import spatial
import cv2

# get tile based on HSV
# value - HSV value to use when retrieving image
# bank - path to root directory to sorted images
# tilesize - size of tile to return
def lookup_tile_by_hsv(hsv,bank,tilesize):
    tile = None

    # index the folder to test against
    h = hsv[0]
    bins = np.linspace(0,180,21)
    folder = str(int(bins[int(h/20)]))
    path = bank + folder + dirdelim()

    # get listing of all the files at the indexed directory
    files = [f for f in os.listdir(path) if os.path.isfile(os.path.join(path,f))]

    # iterate over every file, compare mean hsv of loaded images to source hsv
    for f in files:
        tile = cv2.resize(cv2.imread(path+f),tilesize)
        tile_hsv = cv2.cvtColor(tile,cv2.COLOR_BGR2HSV)
        h,s,v = cv2.split(tile_hsv)

        # get means, create vector, compute distance
        mh = np.mean(h)
        ms = np.mean(s)
        mv = np.mean(v)
        mean = (mh,ms,mv)

        distance = spatial.distance.euclidean(mean,hsv)
        if distance < 40.0:
            break
    return tile

# portable path delimiter
def dirdelim():
    if os.name == 'nt':
        return '\\'
    else:
        return '/'
