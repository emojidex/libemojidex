#!/usr/bin/env ruby

require 'git'
require 'fileutils'

@build_dir = ARGV[0] || Dir.pwd
@source_dir = ARGV[1] || "#{@build_dir}/../"
@interface_dir = "#{@build_dir}/com/emojidex/"

FileUtils.mkdir_p(@interface_dir)

puts "== Copying NDK build files and modifying variables"
FileUtils.cp_r("#{@source_dir}/interfaces/android/jni", @build_dir, {remove_destination: true})
# set source path
txt = File.read("#{@build_dir}/jni/Android.mk")
txt.gsub!("SOURCE_DIRECTORY", "#{@source_dir}/src/ #{@source_dir}/vendor/rapidjson/include/")
File.open("#{@build_dir}/jni/Android.mk", "w") { |mkfile| mkfile.puts txt }

puts "== Creating Native Interface Java sources"
`swig -c++ -java -package com.emojidex -outdir #{@interface_dir} -o #{@build_dir}/jni/libemojidex_wrap.cpp #{@source_dir}/src/emojidex.i`

puts "== Building JNI bindings"
`NDK_PROJECT_PATH=#{@build_dir} #{ENV["ANDROID_NDK"]}/ndk-build`
