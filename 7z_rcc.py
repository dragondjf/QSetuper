#!/usr/bin/python
# -*- coding: utf-8 -*-

import subprocess
import os
import sys


def delete_file_folder(src):
    '''delete files and folders'''
    if os.path.isfile(src):
        try:
            os.remove(src)
        except:
            pass
    elif os.path.isdir(src):
        for item in os.listdir(src):
            itemsrc = os.path.join(src, item)
            delete_file_folder(itemsrc)
        try:
            os.rmdir(src)
        except Exception, e:
            print e


def zip_7z(scr, destobj):
    destination = '%s.7z' % destobj
    delete_file_folder(destination)
    p = subprocess.Popen(['7-Zip/7z', 'a', destination, scr], stdout=subprocess.PIPE, shell=False)
    print ''.join(p.stdout.readlines())
    return destination


def view_rate(num=1, sum=100):
    rate = float(num) / float(sum)
    rate_num = int(rate * 100)
    print '\r%d%% ' % (rate_num)

def split_7z(scr, dest, objectName, num=10, show_bar=True):
    fp = file(scr, 'rb')
    fp.seek(os.SEEK_SET, os.SEEK_END)
    filesize = fp.tell()
    print filesize
    fp.seek(os.SEEK_SET)
    totallen = 0
    unit = filesize / num
    l = fp.read(unit)
    count = 0
    while len(l) > 0:
        with open('%s/%s%d.bin' % (dest, objectName, count), 'wb') as f:
            f.write(l)
        count += 1
        totallen += len(l)
        if show_bar:
            view_rate(totallen, filesize)
        l = fp.read(unit)

def rebuild_7z(srcfolder, dest, objectName, num=10):
    print srcfolder, '+++++++++'
    with open(dest, 'wb') as fp:
        for i in xrange(10):
            path = '%s/%s%d.bin' % (srcfolder, objectName, i)
            print srcfolder, path, os.path.isfile(path)
            if os.path.isfile(path):
                with open(path, 'rb') as f:
                    fp.write(f.read())


if __name__ == '__main__':
    scr = './example/QFramer'
    dest = 'example/qrcfiles/QFramer'
    bin_dest = 'example/qrcfiles'
    print "starting 7z....."
    result = zip_7z(scr, dest)
    print result
    split_7z(result, bin_dest, 'QFramer')
    print bin_dest, '+++++++++'
    rebuild_7z(bin_dest, '%s/QFramer_build.7z' % bin_dest, 'QFramer')
