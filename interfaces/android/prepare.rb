#!/usr/bin/env ruby

require 'git'
require 'fileutils'

@build_dir = ARGV[0] || Dir.pwd

build_targets = ["arm", "x86", "x86_64", "mips"]

puts "== Preparing Android build dependencies"

# Buld Chains
def prepare_chains()
  puts "Preparing Android NDK Build Chains"
  puts "ARM..."
  `$ANDROID_NDK/build/tools/make-standalone-toolchain.sh --platform=android-21 --arch=arm --install-dir=#{@build_dir}/toolchains/arm` unless Dir.exists?("#{@build_dir}/toolchains/arm")
  puts "X86..."
  `$ANDROID_NDK/build/tools/make-standalone-toolchain.sh --platform=android-21 --arch=x86 --install-dir=#{@build_dir}/toolchains/x86` unless Dir.exists?("#{@build_dir}/toolchains/x86")
  puts "X86_64..."
  `$ANDROID_NDK/build/tools/make-standalone-toolchain.sh --platform=android-21 --arch=x86_64 --install-dir=#{@build_dir}/toolchains/x86_64` unless Dir.exists?("#{@build_dir}/toolchains/x86_64")
  puts "MIPS..."
  `$ANDROID_NDK/build/tools/make-standalone-toolchain.sh --platform=android-21 --arch=mips --install-dir=#{@build_dir}/toolchains/mipsel` unless Dir.exists?("#{@build_dir}/toolchains/mips")
end


# OpenSSL
def build_OpenSSL()
  if Dir.exists? "#{@build_dir}/openssl"
    puts "OpenSSL repository found. Updating..."
    git = Git.open("#{@build_dir}/openssl")
    git.clean({force: true, d: true, x:true})
    git.pull
    puts 'Updated.'
  else
    puts 'OpenSSL repository not found. Cloning...'
    git = Git.clone("https://github.com/openssl/openssl.git", "#{@build_dir}/openssl")
    puts 'Cloned.'
  end

  puts 'Building OpenSSL'
  Dir.chdir "#{@build_dir}/openssl"
  `CC="#{@build_dir}/toolchains/arm/bin/arm-linux-androideabi-gcc --sysroot=$ANDROID_NDK/platforms/android-21/arch-arm" ./Configure android-armv7 no-asm`
  `PATH=#{@build_dir}/toolchains/arm:$PATH make`
  if $?.exitstatus == 0
    puts 'Build appears to have succeeded. Continuing.'
  else
    exit 2
  end
  Dir.chdir @build_dir
end

# Boost for Android
def build_boost()
  if Dir.exists? "#{@build_dir}/Boost-for-Android"
    puts 'Boost for Android repository found. Updating...'
    git = Git.open("#{@build_dir}/Boost-for-Android")
    git.clean({force: true, d: true, x:true})
    git.pull
    puts 'Updated.'
  else
    puts 'Boost for Android directory not found. Cloning...'
    git = Git.clone("https://github.com/MysticTreeGames/Boost-for-Android.git", "#{@build_dir}/Boost-for-Android")
    puts 'Cloned.'
  end

  puts 'Building Boost for Android'
  Dir.chdir "#{@build_dir}/Boost-for-Android"
  `./build-android.sh #{ENV['ANDROID_NDK']}`
  if $?.exitstatus == 0
    puts 'Build appears to have succeeded. Continuing.'
  else
    exit 2
  end
  Dir.chdir @build_dir
end

def check_lock()
  if File.exists? "#{@build_dir}/buildlock"
    puts '=> Build lock found. Skipping dependency preparation.'
    puts '=> *Delete the buildlock file to update and regenerate.'
    exit 0
  end
end

def check_env()
  if ENV['ANDROID_NDK'] != nil && ENV['ANDROID_NDK'] != ""
    puts "ANDROID_NDK is set to: #{ENV['ANDROID_NDK']}"
  else
    puts "ANDROID_NDK is not set! You must set the ANDROID_NDK environment variable."
    exit 1
  end
end

def set_lock()
  # Create lock and exit
  puts "Dependencies acquired. Generating build lock."
  lock_file = File.new("#{@build_dir}/buildlock", 'w')
  lock_file.puts "Delete this file to re-build Android build dependencies"
  lock_file.close
end

check_lock()
check_env()
prepare_chains()
build_OpenSSL()
#build_boost()
#set_lock()

exit 0
