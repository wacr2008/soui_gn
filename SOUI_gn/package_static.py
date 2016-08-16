#!/usr/bin/env python

import ctypes
import errno
import logging
import optparse
import os
import shelve
import shutil
import subprocess
import sys
import textwrap 

APP_PACKAGE_LIB_FILE_LISTS = [ 
  'obj/source/components/imgdecoder-stb/imgdecoder-stb.lib',
  'obj/source/third-part/png/png.lib',
  'obj/source/components/render-skia/render-skia.lib',
  'obj/source/components/imgdecoder-stb/imgdecoder-stb.lib',
  'obj/source/third-part/lua-52/lua-52.lib',
  'obj/source/components/resprovider-zip/resprovider-zip.lib',
  'obj/source/third-part/mhook/mhook.lib',
  'obj/source/components/log4z/log4z.lib',
  'obj/source/third-part/smiley/smiley.lib',
  'obj/source/utilities/utilities.lib',
  'obj/source/third-part/skia/skia.lib',
  'obj/source/components/ScriptModule-LUA/ScriptModule-LUA.lib',
  'obj/source/components/translator/translator.lib',
  'obj/source/components/imgdecoder-png/imgdecoder-png.lib',
  'obj/source/SOUI/SOUI.lib',
  'obj/source/components/imgdecoder-gdip/imgdecoder-gdip.lib',
  'obj/source/components/imgdecoder-wic/imgdecoder-wic.lib',
  'obj/source/components/render-gdi/render-gdi.lib',
  'obj/source/third-part/zlib/zlib.lib',
]

APP_PACKAGE_DLL_FILE_LISTS = [
  'soui-sys-resource.dll', 
  'uiresbuilder.exe',
  'uiresImporter.exe',
  'souispy.exe',
]

APP_PACKAGE_PDB_FILE_LISTS = [
  'obj/source/components/imgdecoder-stb/imgdecoder-stb.cc.pdb',
  'obj/source/third-part/png/png.cc.pdb',
  'obj/source/components/render-skia/render-skia.cc.pdb',
  'obj/source/components/imgdecoder-stb/imgdecoder-stb.cc.pdb',
  'obj/source/third-part/lua-52/lua-52.cc.pdb',
  'obj/source/components/resprovider-zip/resprovider-zip.cc.pdb',
  'obj/source/third-part/mhook/mhook.cc.pdb',
  'obj/source/components/log4z/log4z.cc.pdb',
  'obj/source/third-part/smiley/smiley.cc.pdb',
  'obj/source/utilities/utilities.cc.pdb',
  'obj/source/third-part/skia/skia.cc.pdb',
  'obj/source/components/ScriptModule-LUA/ScriptModule-LUA.cc.pdb',
  'obj/source/components/translator/translator.cc.pdb',
  'obj/source/components/imgdecoder-png/imgdecoder-png.cc.pdb',
  'obj/source/SOUI/SOUI.cc.pdb',
  'obj/source/components/imgdecoder-gdip/imgdecoder-gdip.cc.pdb',
  'obj/source/components/imgdecoder-wic/imgdecoder-wic.cc.pdb',
  'obj/source/components/render-gdi/render-gdi.cc.pdb',
  'obj/source/third-part/zlib/zlib.cc.pdb',
]
 
ROOT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT_DIR =  os.path.dirname(os.path.abspath(__file__))
  
class LinkError(IOError):
  """Failed to create a link."""
  pass



class PackageDebug():
  def __init__(self, package_db,package_dll_db, backup_db):
    self._package_db = package_db
    self._package_dll_db = package_dll_db
    self._backup_db  = backup_db
 
 
  def PackExecuteFiles(self):
    destDir =PROJECT_ROOT_DIR + '/static/lib/Debug'
    if not os.path.exists(destDir):  
      os.makedirs(destDir)  
    
    for pkg_path  in self._package_db:
      srcPath =PROJECT_ROOT_DIR + os.path.sep +'out'+os.path.sep+'Debug'+os.path.sep+ pkg_path
      logging.debug('package file  %s  ', srcPath)
      
      if os.path.isfile( srcPath ):
        fileName = os.path.basename(srcPath)  
        destPath = destDir + os.path.sep + fileName 
        shutil.copy(srcPath,destPath)  
    
    return True

  def PackDllFiles(self):
    destDir =PROJECT_ROOT_DIR + '/static/bin/Debug'
    if not os.path.exists(destDir):  
      os.makedirs(destDir)  
    
    for pkg_path  in self._package_dll_db:
      srcPath =PROJECT_ROOT_DIR + os.path.sep +'out'+os.path.sep+'Debug'+os.path.sep+ pkg_path
      logging.debug('package file  %s  ', srcPath)
      
      if os.path.isfile( srcPath ):
        fileName = os.path.basename(srcPath)  
        destPath = destDir + os.path.sep + fileName 
        shutil.copy(srcPath,destPath)  
    
    return True       
        		
  def BackFiles(self):
    destDir =PROJECT_ROOT_DIR + '/static/pdb/Debug'
    if not os.path.exists(destDir):  
       os.makedirs(destDir)  
    
    for pkg_path  in self._backup_db:
      srcPath =PROJECT_ROOT_DIR + os.path.sep +'out'+os.path.sep+'Debug'+os.path.sep+ pkg_path
      logging.debug('backup file  %s  ', srcPath)
      
      if os.path.isfile( srcPath ):
        fileName = os.path.basename(srcPath)  
        destPath = destDir + os.path.sep + fileName 
        shutil.copy(srcPath,destPath)  
    
    return True

class PackageRelease():
  def __init__(self, package_db,package_dll_db, backup_db):
    self._package_db = package_db
    self._package_dll_db = package_dll_db
    self._backup_db  = backup_db
 
 
  def PackExecuteFiles(self):
    destDir =PROJECT_ROOT_DIR + '/static/lib/Release'
    if not os.path.exists(destDir):  
      os.makedirs(destDir)  
    
    for pkg_path  in self._package_db:
      srcPath =PROJECT_ROOT_DIR + os.path.sep +'out'+os.path.sep+'Release'+os.path.sep+ pkg_path
      logging.debug('package file  %s  ', srcPath)
      
      if os.path.isfile( srcPath ):
        fileName = os.path.basename(srcPath)  
        destPath = destDir + os.path.sep + fileName 
        shutil.copy(srcPath,destPath)  
    
    return True

  def PackDllFiles(self):
    destDir =PROJECT_ROOT_DIR + '/static/bin/Release'
    if not os.path.exists(destDir):  
      os.makedirs(destDir)  
    
    for pkg_path  in self._package_dll_db:
      srcPath =PROJECT_ROOT_DIR + os.path.sep +'out'+os.path.sep+'Release'+os.path.sep+ pkg_path
      logging.debug('package file  %s  ', srcPath)
      
      if os.path.isfile( srcPath ):
        fileName = os.path.basename(srcPath)  
        destPath = destDir + os.path.sep + fileName 
        shutil.copy(srcPath,destPath)  
    
    return True       
        		
  def BackFiles(self):
    destDir =PROJECT_ROOT_DIR + '/static/pdb/Release'
    if not os.path.exists(destDir):  
       os.makedirs(destDir)  
    
    for pkg_path  in self._backup_db:
      srcPath =PROJECT_ROOT_DIR + os.path.sep +'out'+os.path.sep+'Release'+os.path.sep+ pkg_path
      logging.debug('backup file  %s  ', srcPath)
      
      if os.path.isfile( srcPath ):
        fileName = os.path.basename(srcPath)  
        destPath = destDir + os.path.sep + fileName 
        shutil.copy(srcPath,destPath)  
    
    return True

def main():
  parser = optparse.OptionParser()
  options, _ = parser.parse_args()
 
  logging.basicConfig(format='%(message)s', level=logging.DEBUG)
  
  # Work from the root directory of the checkout.
  script_dir = os.path.dirname(os.path.abspath(__file__))
  os.chdir(script_dir)
   
			
  try:
    package_release = PackageRelease(APP_PACKAGE_LIB_FILE_LISTS,APP_PACKAGE_DLL_FILE_LISTS,APP_PACKAGE_PDB_FILE_LISTS)
    logging.debug(' Package Release Library Files ') 
    package_release.PackExecuteFiles() 
    
    logging.debug(' Package Release Dll Files ') 
    package_release.PackDllFiles()  
    
    logging.debug(' Backup Release pdb files')
    package_release.BackFiles()  
    
    package_debug = PackageDebug(APP_PACKAGE_LIB_FILE_LISTS,APP_PACKAGE_DLL_FILE_LISTS,APP_PACKAGE_PDB_FILE_LISTS)
    logging.debug(' Package Debug Library Files ') 
    package_debug.PackExecuteFiles() 
    
    logging.debug(' Package Debug Dll Files ') 
    package_debug.PackDllFiles()  
    
    logging.debug(' Backup Debug pdb files')
    package_debug.BackFiles()  
    	
  except LinkError as e:
    print >> sys.stderr, e.message
    return 3    
  return 0


if __name__ == '__main__':
  sys.exit(main())
