#!/usr/bin/env ruby

require 'git'
require 'fileutils'

@build_dir = ARGV[0] || Dir.pwd
@source_dir = ARGV[1] || "#{@build_dir}/../"
@natives_dir = ARGV[2] || "#{@source_dir}/tmp/build/"
@interface_dir = "#{@build_dir}/com/emojidex/"

puts "== copying natives"
FileUtils.cp_r("#{@source_dir}/interfaces/android/jni", @build_dir, {remove_destination: true})

FileUtils.mkdir_p(@interface_dir)

puts "== Copying NDK build files and modifying variables"
FileUtils.cp_r("#{@source_dir}/interfaces/android/jni", @build_dir, {remove_destination: true})

txt = File.read("#{@build_dir}/jni/Android.mk")

# set source path
txt.gsub!("$(OR_INCLUDE_PATH)", "#{@source_dir}/src/ #{@source_dir}/vendor/rapidjson/include/ #{@natives_dir}/natives/include/ #{ENV["CRYSTAX_NDK"]}/sources/boost/1.58.0/include/")
txt.gsub!("$(OR_LIB_PATH)", "#{@natives_dir}/natives/lib/")

cpp_files = Dir.glob("#{@source_dir}/src/**/*.cpp")
cpp_files_string = ""
cpp_files.each { |cpp_file| cpp_files_string += "#{cpp_file} " }
txt.gsub!("$(OR_CPP_SOURCES)", cpp_files_string )

File.open("#{@build_dir}/jni/Android.mk", "w") { |mkfile| mkfile.puts txt }

puts "== Creating Native Interface Java sources"
`swig -c++ -java -package com.emojidex.libemojidex -outdir #{@interface_dir} -o #{@build_dir}/jni/libemojidex_wrap.cpp #{@source_dir}/src/emojidex.i`

puts "== Running NDK Build"
`NDK_PROJECT_PATH=#{@build_dir} #{ENV["CRYSTAX_NDK"]}/ndk-build`
