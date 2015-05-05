#!/usr/bin/env ruby

require 'git'

if ENV['NDK_ROOT'] != nil && ENV['NDK_ROOT'] != ""
  puts "NDK_ROOT is set to: #{ENV['NDK_ROOT']}"
else
  puts "NDK_ROOT is not set! You must set the NDK_ROOT environment variable."
  
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
puts `cd ./Boost-for-Android; ./build-android.sh #{ENV['NDK_ROOT']}`
