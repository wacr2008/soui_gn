import sys
import os

# Usage: core_gen.py shared_library 
# Usage: core_gen.py static_library   
 
library_type = sys.argv[1]  

script_dir = os.path.dirname(os.path.abspath(__file__))
output_file = script_dir + os.path.sep+ 'core-def.h'

if(library_type == 'shared_library'):    
		hfile = open(output_file, 'w')
		hfile.write('#ifndef DLL_CORE\n')
		hfile.write('#define DLL_CORE\n')
		hfile.write('#endif')
		hfile.close()
else:   
		hfile = open(output_file, 'w')
		hfile.write('#ifndef LIB_CORE\n')
		hfile.write('#define LIB_CORE\n')
		hfile.write('#endif')
		hfile.close() 

sys.exit(0)