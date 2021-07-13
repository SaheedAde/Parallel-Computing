#! /usr/bin/env python

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import argparse
import time



if __name__ == "__main__":

    parser = argparse.ArgumentParser()
    parser.add_argument("-i", help="image with Julia data")
    parser.add_argument("-o", help="output file")
    args = parser.parse_args()

    # im_height = 0
    # im_width = 0

    fh = open(args.i)
    content = fh.readlines()
    fh.close()

    im_height = len(content)

    print("wxh", im_height, im_height)

    image = np.fromfile(args.i, dtype=np.float64, sep=" ")
    print(len(image))
    image = image.reshape(im_height, im_height)

    my_dpi = 300
    plt.figure(figsize=(im_height/my_dpi, im_height/my_dpi), dpi=my_dpi)
    fig, ax = plt.subplots()    
    #ax.imshow(image, interpolation='nearest', cmap=cm.hot)
    ax.imshow(image, interpolation='nearest', cmap=cm.get_cmap('autumn_r'))
    plt.axis('off')
    plt.savefig(args.o, bbox_inches='tight', dpi=my_dpi)
    
