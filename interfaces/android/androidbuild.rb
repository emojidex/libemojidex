#!/usr/bin/env ruby

require 'git'
require 'fileutils'

@build_dir = ARGV[0] || Dir.pwd
@source_dir = ARGV[1] || "#{@build_dir}/../"
@natives_dir = ARGV[2] || "#{@source_dir}/tmp/build/"
@interface_dir = "#{@build_dir}/com/emojidex/libemojidex/"

puts "== Copying NDK build files and modifying variables"
FileUtils.cp_r("#{@source_dir}/interfaces/android/jni", @build_dir, {remove_destination: true})

txt = File.read("#{@build_dir}/jni/Android.mk")

# set source path
txt.gsub!("$(OR_INCLUDE_PATH)", "#{@source_dir}/src/ #{@source_dir}/vendor/rapidjson/include/ #{ENV["CRYSTAX_NDK"]}/sources/boost/1.59.0/include/  #{@natives_dir}/natives/include/")
txt.gsub!("$(OR_LIB_PATH)", "#{@natives_dir}/natives/lib/")

cpp_files = Dir.glob("#{@source_dir}/src/**/*.cpp")
cpp_files_string = ""
cpp_files.each { |cpp_file| cpp_files_string += "#{cpp_file} " }
txt.gsub!("$(OR_CPP_SOURCES)", cpp_files_string )

File.open("#{@build_dir}/jni/Android.mk", "w") { |mkfile| mkfile.puts txt }

puts "== Creating Native Interface Java sources"
`swig -c++ -java -package com.emojidex.libemojidex -outdir #{@interface_dir} -o #{@build_dir}/jni/libemojidex_wrap.cpp #{@source_dir}/src/libemojidex.i`

puts "== Running NDK Build"
`NDK_PROJECT_PATH=#{@build_dir} #{ENV["CRYSTAX_NDK"]}/ndk-build`

puts "== copying natives"
FileUtils.mkdir_p(@interface_dir)
FileUtils.mkdir_p("#{@build_dir}/libs")

if File.exists? "#{@natives_dir}/natives/lib/arm"
  FileUtils.mkdir_p("#{@build_dir}/libs/armeabi")
  FileUtils.cp_r(Dir["#{@natives_dir}/natives/lib/arm/*.so*"].collect{|f| File.expand_path(f)}, "#{@build_dir}/libs/armeabi/", {remove_destination: true})
  FileUtils.mkdir_p("#{@build_dir}/libs/armeabi-v7a")
  FileUtils.cp_r(Dir["#{@natives_dir}/natives/lib/arm/*.so*"].collect{|f| File.expand_path(f)}, "#{@build_dir}/libs/armeabi-v7a/", {remove_destination: true})
end
if File.exists? "#{@natives_dir}/natives/lib/arm64"
  FileUtils.mkdir_p("#{@build_dir}/libs/arm64-v8a")
  FileUtils.cp_r(Dir["#{@natives_dir}/natives/lib/arm64/*.so*"].collect{|f| File.expand_path(f)}, "#{@build_dir}/libs/arm64-v8a/", {remove_destination: true})
end
if File.exists? "#{@natives_dir}/natives/lib/x86"
  FileUtils.mkdir_p("#{@build_dir}/libs/x86")
  FileUtils.cp_r(Dir["#{@natives_dir}/natives/lib/x86/*.so*"].collect{|f| File.expand_path(f)}, "#{@build_dir}/libs/x86/", {remove_destination: true})
end
if File.exists? "#{@natives_dir}/natives/lib/x86_64"
  FileUtils.mkdir_p("#{@build_dir}/libs/x86_64")
  FileUtils.cp_r(Dir["#{@natives_dir}/natives/lib/x86_64/*.so*"].collect{|f| File.expand_path(f)}, "#{@build_dir}/libs/x86_64/", {remove_destination: true})
end
if File.exists? "#{@natives_dir}/natives/lib/mips"
  FileUtils.mkdir_p("#{@build_dir}/libs/mips")
  FileUtils.cp_r(Dir["#{@natives_dir}/natives/lib/mips/*.so*"].collect{|f| File.expand_path(f)}, "#{@build_dir}/libs/mips/", {remove_destination: true})
end

puts "== for mac (copy the missing file)"
FileUtils.cp("#{@natives_dir}/natives/lib/arm/libcurl.so", "#{@build_dir}/libs/armeabi/libcurl.so") if File.exists? "#{@natives_dir}/natives/lib/arm/libcurl.so"
FileUtils.cp("#{@natives_dir}/natives/lib/arm/libcurl.so", "#{@build_dir}/libs/armeabi-v7a/libcurl.so") if File.exists? "#{@natives_dir}/natives/lib/arm/libcurl.so"
FileUtils.cp("#{@natives_dir}/natives/lib/arm64/libcurl.so", "#{@build_dir}/libs/arm64-v8a/libcurl.so") if File.exists? "#{@natives_dir}/natives/lib/arm64/libcurl.so"
FileUtils.cp("#{@natives_dir}/natives/lib/x86/libcurl.so", "#{@build_dir}/libs/x86/libcurl.so") if File.exists? "#{@natives_dir}/natives/lib/x86/libcurl.so"
FileUtils.cp("#{@natives_dir}/natives/lib/x86_64/libcurl.so", "#{@build_dir}/libs/x86_64/libcurl.so") if File.exists? "#{@natives_dir}/natives/lib/x86_64/libcurl.so"
FileUtils.cp("#{@natives_dir}/natives/lib/mips/libcurl.so", "#{@build_dir}/libs/mips/libcurl.so") if File.exists? "#{@natives_dir}/natives/lib/mips/libcurl.so"

puts "== Copying temporary natives for jar"
Dir.chdir(@build_dir) do
  tmp_dir = 'tmp';
  FileUtils.rm_rf(tmp_dir);
  Dir.glob('libs/**/*') do |filename|
    tmp_filename = "#{tmp_dir}/#{filename}"
    if FileTest.directory?(filename) then
      FileUtils.mkdir_p(tmp_filename)
      next
    end
    FileUtils.cp_r(filename, "#{tmp_filename}_", {remove_destination: true});
  end
end
