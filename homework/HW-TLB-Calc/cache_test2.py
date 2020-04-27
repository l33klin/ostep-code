#!/usr/bin/python3
# -*- coding: utf-8 -*-
"""
@Time    : 2019-04-28 1:12
@Author  : Jann
@Contact : l33klin@foxmail.com
@Site    : 
@File    : cache_test2.py
@Require : pip3 install -U matplotlib
"""


import os
import subprocess
import matplotlib.pyplot as plt
import numpy as np 

ROOT_PATH = "/Users/klin/CODE/github/ostep-code/homework/HW-TLB-Calc"

def run_cahce_test2():
    inc = 1024
    x = [i for i in range(1, 20)]
    y = []

    for times in x:
        cmd = [os.path.join(ROOT_PATH, 'cache_test2.o'), str(inc), str(times)]
        return_proc = subprocess.run(cmd, stdout=subprocess.PIPE)
        elapse = int(return_proc.stdout)
        print("{} times, Elapsed {}ms".format(times, elapse/1000.0))
        y.append(elapse)

    fig, ax = plt.subplots()  # Create a figure containing a single axes.
    ax.plot(x, y)  # Plot some data on the axes.
    plt.show()

if __name__ == "__main__":
    run_cahce_test2()