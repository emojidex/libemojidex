#!/usr/bin/env ruby

require 'git'
require 'fileutils'

@build_dir = ARGV[0] || Dir.pwd
@source_dir = ARGV[1] || "#{@build_dir}/../"
@interface_dir = "#{@build_dir}/com/emojidex/"

FileUtils.mkdir_p(@interface_dir)

puts "== Creating Native Interface sources in #{@build_dir}"

`swig -c++ -java -package com.emojidex -outdir #{@interface_dir} -o #{@source_dir}/src/emojidex.h #{@source_dir}/src/emojidex.i`
