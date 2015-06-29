require 'mkmf'

#swig = [ 'swig3', 'swig3.0', 'swig' ].select { |swig_name| find_executable(swig_name) }.first

#if swig
#  puts "Using #{swig} to generate wrapper code. If generation fails please make sure you have " \
#    "SWIG version 3.0 or greater."
#else
#  puts "SWIG is required and must be in your system path. Please install SWIG version 3.0 or " \
#    "greater."


$CFLAGS = '-x c++'
$LOCAL_LIBS = '-lemojidex'

dir_config 'libemojidex'

create_makefile 'libemojidex'
