#!/usr/bin/python
# -*- coding: utf-8 -*-

import subprocess
import os
import sys
import time

import xml.dom.minidom as Dom


class XMLGenerator(object): 
    def __init__(self, xml_name=None): 
        self.doc = Dom.Document() 
        self.xml_name = xml_name 

    def createNode(self, node_name): 
        return self.doc.createElement(node_name) 
    
    def addNode(self, node, parent_node=None): 
        cur_node = node 
        if parent_node is not None: 
            parent_node.appendChild(cur_node) 
        else: 
            self.doc.appendChild(cur_node) 
        return cur_node

    def setNodeAttr(self, node, att_name, value): 
        cur_node = node 
        cur_node.setAttribute(att_name, value) 

    def setNodeValue(self, cur_node, value): 
        node_data = self.doc.createTextNode(value) 
        cur_node.appendChild(node_data) 
    
    def genXml(self, name=None):
        if name is None:
            name = self.xml_name
        f = open(name, "w") 
        f.write(self.doc.toprettyxml(indent = "\t", newl = "\n", encoding = "utf-8")) 
        f.close()


def getfiles(path):
    '''
        获取指定path下的所有文件列表
    '''
    files = []
    for dirpath, dirnames, filenames in os.walk(path):
        for filename in filenames:
            files.append('/'.join([dirpath, filename]))
    return files


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


def zip_7z(scr, dest, obj):
    '''
        7z.exe a example/qrcfiles/QFramer.7z ./example/QFramer -v5m
    '''
    destination = '%s/%s.7z' % (dest, obj)
    delete_file_folder(dest)
    time.sleep(1)
    os.mkdir(dest)
    time.sleep(1)
    p = subprocess.Popen(['7-Zip/7z', 'a', destination, scr, '-v5m'], stdout=subprocess.PIPE, shell=False)
    print ''.join(p.stdout.readlines())
    return destination


def unzip_7z(scr, root, obj):
    '''
        7z.exe e example/qrcfiles/QFramer.7z.001 -oexample/QFramer_new
    '''
    destination = '%s/%s_new' % (root, obj)
    delete_file_folder(destination)
    time.sleep(1)
    os.mkdir(destination)
    time.sleep(1)
    p = subprocess.Popen(['7-Zip/7z', 'x', '%s/%s.7z.001' % (scr, obj), '-o%s'%destination], stdout=subprocess.PIPE, shell=False)
    print ''.join(p.stdout.readlines())
    return destination

def generateQRCFile(destination=None, obj=None):
    qrcfiles = []

    files = getfiles(destination)
    #xml root node
    
    for index, f in enumerate(files):
        qrcGenerator = XMLGenerator()
        rccNode = qrcGenerator.createNode("RCC")
        qrcGenerator.addNode(node=rccNode)
        qresourceNode = qrcGenerator.createNode("qresource")
        qrcGenerator.setNodeAttr(qresourceNode, 'prefix', "/%s" %obj)
        qrcGenerator.addNode(qresourceNode, rccNode)

        node_7z = qrcGenerator.createNode("file")
        qrcGenerator.setNodeValue(node_7z, f)
        qrcGenerator.addNode(node_7z, qresourceNode)
        qrc = "%s%s.qrc" % (obj, index)
        qrcGenerator.genXml(qrc)
        qrcfiles.append(qrc)

    obj_7z = '7-Zip'
    fiels_7z = getfiles(obj_7z)
    qrcGenerator = XMLGenerator()
    rccNode = qrcGenerator.createNode("RCC")
    qrcGenerator.addNode(node=rccNode)
    qresourceNode = qrcGenerator.createNode("qresource")
    qrcGenerator.setNodeAttr(qresourceNode, 'prefix', "/%s" % obj_7z)
    qrcGenerator.addNode(qresourceNode, rccNode)
    for index, f in enumerate(fiels_7z):
        node_7z = qrcGenerator.createNode("file")
        qrcGenerator.setNodeValue(node_7z, f)
        qrcGenerator.addNode(node_7z, qresourceNode)
    qrc = '%s.qrc' % obj_7z
    qrcGenerator.genXml(qrc)
    qrcfiles.append(qrc)

    qrcfiles.append('skin.qrc')

    return qrcfiles

def addQRCToPro(profile, qrcfiles):
    with open(profile, 'r+') as f:
        content = f.read()
        index = content.find("RESOURCES +=")
        qrc = "RESOURCES +=" + ' '.join(qrcfiles)
        newcontent = content[0:index] + qrc

    with open(profile, 'w') as f:
        f.write(newcontent)

def clearQRCFiles():
    files = getfiles('.')
    for f in files:
        if f.endswith('.qrc') and not f.endswith('skin.qrc'):
            delete_file_folder(f)
            print 'delete', f

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
    with open(dest, 'wb') as fp:
        for i in xrange(10):
            path = '%s/%s%d.bin' % (srcfolder, objectName, i)
            print srcfolder, path, os.path.isfile(path)
            if os.path.isfile(path):
                with open(path, 'rb') as f:
                    fp.write(f.read())


if __name__ == '__main__':
    root = './example'
    objectName = 'QFramer'
    scr = './example/%s' % objectName
    destination = 'example/qrcfiles'
    print 'starting 7z.....'
    result = zip_7z(scr, destination, objectName)
    print ' starting unzip.......'
    unzip_7z(destination, root, objectName)
    print getfiles('7-Zip')
    clearQRCFiles()
    qrcfiles = generateQRCFile(destination, objectName)
    addQRCToPro('Qsetuper.pro', qrcfiles)
