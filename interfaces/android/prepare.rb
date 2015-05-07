#!/usr/bin/env ruby

require 'git'
require 'fileutils'

build_dir = ARGV[0] || Dir.pwd

puts "== Preparing Android build dependencies"

if File.exists? "#{build_dir}/buildlock"
  puts '=> Build lock found. Skipping dependency preparation.'
  puts '=> *Delete the buildlock file to update and regenerate.'
  exit 0
end

# Boost for Android
if ENV['ANDROID_NDK'] != nil && ENV['ANDROID_NDK'] != ""
  puts "ANDROID_NDK is set to: #{ENV['ANDROID_NDK']}"
else
  puts "ANDROID_NDK is not set! You must set the ANDROID_NDK environment variable."
  exit 1
end

if Dir.exists? "#{build_dir}/Boost-for-Android"
  puts 'Boost for Android directory found. Updating...'
  git = Git.open("#{build_dir}/Boost-for-Android")
  git.pull
  puts 'Updated.'
else
  puts 'Boost for Android directory not found. Cloning...'
  git = Git.clone("https://github.com/MysticTreeGames/Boost-for-Android.git", "#{build_dir}/Boost-for-Android")
  puts 'Cloned.'
end

puts 'Building Boost for Android'
Dir.chdir "#{build_dir}/Boost-for-Android"
`./build-android.sh #{ENV['ANDROID_NDK']}`
if $?.exitstatus == 0
  puts 'Build appears to have succeeded. Continuing.'
else
  exit 2
end
Dir.chdir build_dir

# Android CMake
# Git.clone("https://github.com/taka-no-me/android-cmake.git", 'android-cmake') unless Dir.exists? './android-cmake'

# Create lock and exit
puts "Dependencies acquired. Generating build lock."
lock_file = File.new("#{build_dir}/buildlock", 'w')
lock_file.puts "Delete this file to re-build Android build dependencies"
lock_file.close
exit 0
