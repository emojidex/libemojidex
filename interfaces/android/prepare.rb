#!/usr/bin/env ruby

require 'git'
require 'fileutils'

script_dir = File.expand_path(File.dirname(__FILE__))

if File.exists? "#{script_dir}/buildlock"
  puts 'Build lock found. Skipping dependency preparation.'
  exit 0
end

# Boost for Android
if ENV['NDK_ROOT'] != nil && ENV['NDK_ROOT'] != ""
  puts "NDK_ROOT is set to: #{ENV['NDK_ROOT']}"
else
  puts "NDK_ROOT is not set! You must set the NDK_ROOT environment variable."
  exit 1
end

if Dir.exists? './Boost-for-Android'
  puts 'Boost for Android directory found. Updating...'
  git = Git.open('./Boost-for-Android')
  git.pull
  puts 'Updated.'
else
  puts 'Boost for Android directory not found. Cloning...'
  git = Git.clone("https://github.com/MysticTreeGames/Boost-for-Android.git", 'Boost-for-Android')
  puts 'Cloned.'
end

puts 'Building Boost for Android'
Dir.chdir "#{script_dir}/Boost-for-Android"
`./build-android.sh #{ENV['NDK_ROOT']}`
if $?.exitstatus == 0
  puts 'Build appears to have succeeded. Continuing.'
else
  exit 2
end
Dir.chdir "#{script_dir}"

# Android CMake
Git.clone("https://github.com/taka-no-me/android-cmake.git", 'android-cmake') unless Dir.exists? './android-cmake'

# Create lock and exit
puts "Dependencies acquired. Generating build lock."
lock_file = File.new("#{script_dir}/buildlock", 'w')
lock_file.puts "Delete this file to re-build Android build dependencies"
lock_file.close
exit 0
