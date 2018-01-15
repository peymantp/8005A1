#! python3

from concurrent.futures import ProcessPoolExecutor, ThreadPoolExecutor
import numpy as np
import time
import matplotlib.pyplot as plt
import glob
from PIL import Image
import random
import string

try:
    from urllib.request import urlopen
except ImportError:
    from urllib2 import urlopen

url = 'http://scholar.princeton.edu/sites/default/files/oversize_pdf_test_0.pdf'
URLS = [url,url,url,url,url,url,url,url,url,url,url]

MULTITHREADING_TITLE="Multithreading"
MULTIPROCESSING_TITLE="Multiprocessing"

def download(url, base):
    start = time.time() - base
    resp = urlopen(url)
    stop = time.time() - base
    return start,stop

def visualize_runtimes(results, title):
    start,stop = np.array(results).T
    plt.barh(range(len(start)),stop-start,left=start)
    plt.grid(axis='x')
    plt.ylabel("Tasks")
    plt.xlabel("Seconds")
    plt.title(title)
    return stop[-1]-start[0]

results = [download(url, 1) for url in URLS]

visualize_runtimes(results,'Results')
