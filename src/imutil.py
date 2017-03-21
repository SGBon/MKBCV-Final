# utility functions for image mosaic generator

import os
import numpy as np
from scipy import spatial
import cv2

# get average cell value from image
def get_average_hsv(hsv):
    h,s,v = cv2.split(hsv)
    return (np.mean(h), np.mean(s), np.mean(v))

# get tile based on HSV
# value - HSV value to use when retrieving image
# bank - path to root directory to sorted images
# tilesize - size of tile to return
def lookup_tile_by_hsv(hsv,bank,tilesize):
    tile = None

    # index the folder to test against
    hsv_mean = get_average_hsv(hsv)
    bins = np.linspace(0,180,21)
    folder = str(int(bins[int(hsv_mean[0]/20)]))
    path = bank + folder + dirdelim()

    # get listing of all the files at the indexed directory
    files = [f for f in os.listdir(path) if os.path.isfile(os.path.join(path,f))]

    # iterate over every file, compare mean hsv of loaded images to source hsv
    for f in files:
        tile = cv2.resize(cv2.imread(path+f),tilesize)
        tile_hsv = cv2.cvtColor(tile,cv2.COLOR_BGR2HSV)
        h,s,v = cv2.split(tile_hsv)

        # get means, create vector, compute distance
        tile_mean = get_average_hsv(tile_hsv)

        #print "try '%s' with hsv %s an dmean %s" % (f, hsv, mean)
        distance = spatial.distance.euclidean(tile_mean,hsv_mean)
        if distance < 40.0:
            break
    return tile

# portable path delimiter
def dirdelim():
    if os.name == 'nt':
        return '\\'
    else:
        return '/'
