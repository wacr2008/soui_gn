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
  'obj/src/components/imgdecoder-stb/imgdecoder-stb.lib',
  'obj/src/third-part/png/png.lib',
  'obj/src/components/render-skia/render-skia.lib',
  'obj/src/components/imgdecoder-stb/imgdecoder-stb.lib',
  'obj/src/third-part/lua-52/lua-52.lib',
  #'obj/src/components/resprovider-7zip/resprovider-7zip.lib',
  'obj/src/components/resprovider-zip/resprovider-zip.lib',
  'obj/src/third-part/mhook/mhook.lib',
  'obj/src/components/log4z/log4z.lib',
  'obj/src/third-part/smiley/smiley.lib',
  'obj/src/utilities/utilities.lib',
  'obj/src/third-part/skia/skia.lib',
  'obj/src/components/ScriptModule-LUA/ScriptModule-LUA.lib',
  'obj/src/components/translator/translator.lib',
  'obj/src/components/imgdecoder-png/imgdecoder-png.lib',
  'obj/src/SOUI/SOUI.lib',
  'obj/src/components/imgdecoder-gdip/imgdecoder-gdip.lib',
  'obj/src/components/imgdecoder-wic/imgdecoder-wic.lib',
  'obj/src/components/render-gdi/render-gdi.lib',
  'obj/src/third-part/zlib/zlib_static.lib',
  'obj/src/third-part/zlib/zlib_x86_simd_static.lib',
]

APP_PACKAGE_DLL_FILE_LISTS = [
  'uiresbuilder.exe',
  'uiresImporter.exe',
  'souispy.exe',
]

APP_PACKAGE_PDB_FILE_LISTS = [
  'obj/src/components/imgdecoder-stb/imgdecoder-stb_cc.pdb',
  'obj/src/third-part/png/png_cc.pdb',
  'obj/src/components/render-skia/render-skia_cc.pdb',
  'obj/src/components/imgdecoder-stb/imgdecoder-stb_cc.pdb',
  'obj/src/third-part/lua-52/lua-52_cc.pdb',
  'obj/src/components/resprovider-zip/resprovider-zip_cc.pdb',
  #'obj/src/components/resprovider-7zip/resprovider-7zip_cc.pdb', 
  'obj/src/third-part/mhook/mhook_cc.pdb',
  'obj/src/components/log4z/log4z_cc.pdb',
  'obj/src/third-part/smiley/smiley_cc.pdb',
  'obj/src/utilities/utilities_cc.pdb',
  'obj/src/third-part/skia/skia_cc.pdb',
  'obj/src/components/ScriptModule-LUA/ScriptModule-LUA_cc.pdb',
  'obj/src/components/translator/translator_cc.pdb',
  'obj/src/components/imgdecoder-png/imgdecoder-png_cc.pdb',
  'obj/src/SOUI/SOUI_cc.pdb',
  'obj/src/components/imgdecoder-gdip/imgdecoder-gdip_cc.pdb',
  'obj/src/components/imgdecoder-wic/imgdecoder-wic_cc.pdb',
  'obj/src/components/render-gdi/render-gdi_cc.pdb',
  'obj/src/third-part/zlib/zlib_static_c.pdb',
  'obj/src/third-part/zlib/zlib_x86_simd_static_c.pdb',
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
      srcPath =PROJECT_ROOT_DIR + os.path.sep +'out'+os.path.sep+'Debug_static'+os.path.sep+ pkg_path
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
      srcPath =PROJECT_ROOT_DIR + os.path.sep +'out'+os.path.sep+'Debug_static'+os.path.sep+ pkg_path
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
      srcPath =PROJECT_ROOT_DIR + os.path.sep +'out'+os.path.sep+'Debug_static'+os.path.sep+ pkg_path
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
      srcPath =PROJECT_ROOT_DIR + os.path.sep +'out'+os.path.sep+'Release_static'+os.path.sep+ pkg_path
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
      srcPath =PROJECT_ROOT_DIR + os.path.sep +'out'+os.path.sep+'Release_static'+os.path.sep+ pkg_path
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
      srcPath =PROJECT_ROOT_DIR + os.path.sep +'out'+os.path.sep+'Release_static'+os.path.sep+ pkg_path
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
