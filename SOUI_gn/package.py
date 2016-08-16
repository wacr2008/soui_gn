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
  'imgdecoder-gdip',
  'imgdecoder-png',
  'imgdecoder-stb',
  'imgdecoder-wic',
  'log4z',
  'render-gdi',
  'render-skia',
  'resprovider-zip',
  'ScriptModule-LUA',
  'SOUI',
  'soui-sys-resource',
  'translator',
  'utilities',
]

APP_PACKAGE_DLL_FILE_LISTS = [
  'imgdecoder-gdip.dll',
  'imgdecoder-png.dll',
  'imgdecoder-stb.dll',
  'imgdecoder-wic.dll',
  'log4z.dll',
  'render-gdi.dll',
  'render-skia.dll',
  'resprovider-zip.dll',
  'ScriptModule-LUA.dll',
  'SOUI.dll',
  'soui-sys-resource.dll',
  'translator.dll',
  'utilities.dll',
]

APP_PACKAGE_PDB_FILE_LISTS = [
  'imgdecoder-gdip.dll.pdb',
  'imgdecoder-png.dll.pdb',
  'imgdecoder-stb.dll.pdb',
  'imgdecoder-wic.dll.pdb',
  'log4z.dll.pdb',
  'render-gdi.dll.pdb',
  'render-skia.dll.pdb',
  'resprovider-zip.dll.pdb',
  'ScriptModule-LUA.dll.pdb',
  'SOUI.dll.pdb',
  'soui-sys-resource.dll.pdb',
  'translator.dll.pdb',
  'utilities.dll.pdb',
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
    destDir =PROJECT_ROOT_DIR + '/dynamic/lib/Debug'
    if not os.path.exists(destDir):  
      os.makedirs(destDir)  
    
    for pkg_path  in self._package_db:
       orgPath =PROJECT_ROOT_DIR + os.path.sep +'out'+os.path.sep+'Debug'+os.path.sep+ pkg_path
       srcPath =PROJECT_ROOT_DIR + os.path.sep +'out'+os.path.sep+'Debug'+os.path.sep+ pkg_path + '.dll.lib'
       logging.debug('package file  %s  ', srcPath)
      
       if os.path.isfile( srcPath ):
         fileName = os.path.basename(orgPath)  
         destPath = destDir + os.path.sep + fileName + '.lib'
         shutil.copy(srcPath,destPath)  
    
    return True

  def PackDllFiles(self):
    destDir =PROJECT_ROOT_DIR + '/dynamic/bin/Debug'
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
    destDir =PROJECT_ROOT_DIR + '/dynamic/pdb/Debug'
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
    destDir =PROJECT_ROOT_DIR + '/dynamic/lib/Release'
    if not os.path.exists(destDir):  
      os.makedirs(destDir)  
    
    for pkg_path  in self._package_db:
      orgPath =PROJECT_ROOT_DIR + os.path.sep +'out'+os.path.sep+'Release'+os.path.sep+ pkg_path
      srcPath =PROJECT_ROOT_DIR + os.path.sep +'out'+os.path.sep+'Release'+os.path.sep+ pkg_path + '.dll.lib'
      logging.debug('package file  %s  ', srcPath)
      
      if os.path.isfile( srcPath ):
        fileName = os.path.basename(orgPath)  
        destPath = destDir + os.path.sep + fileName + '.lib'
        shutil.copy(srcPath,destPath)  
    
    return True

  def PackDllFiles(self):
    destDir =PROJECT_ROOT_DIR + '/dynamic/bin/Release'
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
    destDir =PROJECT_ROOT_DIR + '/dynamic/pdb/Release'
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
