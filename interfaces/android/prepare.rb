#!/usr/bin/env ruby

require 'git'
require 'fileutils'

@build_dir = ARGV[0] || Dir.pwd

@build_targets = ["arm", "x86", "x86_64", "mips"]

puts "=== Preparing Android build dependencies"

# Buld Chains
def prepare_chains()
  puts "== Preparing Android NDK Build Chains"
  puts "= ARM..."
  `$ANDROID_NDK/build/tools/make-standalone-toolchain.sh --platform=android-21 --arch=arm --install-dir=#{@build_dir}/toolchains/arm` unless Dir.exists?("#{@build_dir}/toolchains/arm")
  puts "= X86..."
  `$ANDROID_NDK/build/tools/make-standalone-toolchain.sh --platform=android-21 --arch=x86 --install-dir=#{@build_dir}/toolchains/x86` unless Dir.exists?("#{@build_dir}/toolchains/x86")
  puts "= X86_64..."
  `$ANDROID_NDK/build/tools/make-standalone-toolchain.sh --platform=android-21 --arch=x86_64 --install-dir=#{@build_dir}/toolchains/x86_64` unless Dir.exists?("#{@build_dir}/toolchains/x86_64")
  puts "= MIPS..."
  `$ANDROID_NDK/build/tools/make-standalone-toolchain.sh --platform=android-21 --arch=mips --install-dir=#{@build_dir}/toolchains/mipsel` unless Dir.exists?("#{@build_dir}/toolchains/mips")

  FileUtils.mkdir_p("#{@build_dir}/natives")
  @build_targets.each do |target|
    FileUtils.mkdir_p("#{@build_dir}/natives/#{target}")
    FileUtils.mkdir_p("#{@build_dir}/natives/#{target}/lib")
    FileUtils.mkdir_p("#{@build_dir}/natives/#{target}/include")
  end
end


# OpenSSL
def build_OpenSSL()
  if Dir.exists? "#{@build_dir}/openssl"
    puts "OpenSSL repository found. Updating..."
    git = Git.open("#{@build_dir}/openssl")
    git.reset_hard("HEAD")
    git.clean({force: true, d: true, x:true})
    git.pull("https://github.com/openssl/openssl.git", "OpenSSL_1_0_2-stable")
    puts 'Updated.'
  else
    puts 'OpenSSL repository not found. Cloning...'
    git = Git.clone("https://github.com/openssl/openssl.git", "#{@build_dir}/openssl")
    git.checkout("OpenSSL_1_0_2-stable")
    puts 'Cloned.'
  end

  puts '== Building OpenSSL'
  Dir.chdir "#{@build_dir}/openssl"

  puts '= Building for ARM'
  `make clean && make dclean`
  git.clean({force: true, d: true, x:true})
  `CC="#{@build_dir}/toolchains/arm/bin/arm-linux-androideabi-gcc --sysroot=$ANDROID_NDK/platforms/android-21/arch-arm" ./Configure android-armv7 threads no-asm && make`
  FileUtils.cp("#{@build_dir}/openssl/libcrypto.a", "#{@build_dir}/natives/arm/lib/")
  FileUtils.cp("#{@build_dir}/openssl/libssl.a", "#{@build_dir}/natives/arm/lib/")
  FileUtils.ln_s("#{@build_dir}/openssl/include/openssl", "#{@build_dir}/natives/arm/include/openssl", { force: true })

  puts '= Building for x86'
  `make clean && make dclean`
  git.clean({force: true, d: true, x:true})
  `CC="#{@build_dir}/toolchains/x86/bin/i686-linux-android-gcc --sysroot=$ANDROID_NDK/platforms/android-21/arch-x86" ./Configure android-x86 threads no-asm && make`
  FileUtils.cp("#{@build_dir}/openssl/libcrypto.a", "#{@build_dir}/natives/x86/lib/")
  FileUtils.cp("#{@build_dir}/openssl/libssl.a", "#{@build_dir}/natives/x86/lib/")
  FileUtils.ln_s("#{@build_dir}/openssl/include/openssl", "#{@build_dir}/natives/x86/include/openssl", { force: true })
  
  Dir.chdir @build_dir
end

# Boost for Android
def build_android_boost()
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

  puts '== Building Boost for Android'
  Dir.chdir "#{@build_dir}/Boost-for-Android"
  `./build-android.sh #{ENV['ANDROID_NDK']}`
  if $?.exitstatus == 0
    puts 'Build appears to have succeeded. Continuing.'
    FileUtils.cp_r("#{@build_dir}/Boost-for-Android/build/include/", "#{@build_dir}/natives/arm/")
    FileUtils.cp_r("#{@build_dir}/Boost-for-Android/build/lib/", "#{@build_dir}/natives/arm/")
    FileUtils.ln_s("#{@build_dir}/natives/arm/include/boost-1_53/boost", "#{@build_dir}/natives/arm/include/boost", { force: true })
  else
    exit 2
  end
  Dir.chdir @build_dir
end

def build_boost()
  if Dir.exists? "#{@build_dir}/boost"
    puts 'Boost repository found. Updating...'
    Dir.chdir "#{@build_dir}/boost"
    `git pull`
    `git submodule update --recursive`
    puts 'Updated.'
  else
    puts 'Boost directory not found. Cloning...'
    `git clone https://github.com/boostorg/boost.git`
    puts 'Cloned. Obtaining submodules (this will take a long time)...'
    Dir.chdir "#{@build_dir}/boost"
    `git submodule init --recursive`
  end

  puts 'Building Boost'
  #Dir.chdir "#{@build_dir}/boost"
  `CC="#{@build_dir}/toolchains/arm/bin/arm-linux-androideabi-gcc --sysroot=$ANDROID_NDK/platforms/android-21/arch-arm" ./bootstrap.sh --without-libraries=python`
  `CC="#{@build_dir}/toolchains/arm/bin/arm-linux-androideabi-gcc --sysroot=$ANDROID_NDK/platforms/android-21/arch-arm" ./b2 headers`
  `CC="#{@build_dir}/toolchains/arm/bin/arm-linux-androideabi-gcc --sysroot=$ANDROID_NDK/platforms/android-21/arch-arm" ./b2`
  `CC="#{@build_dir}/toolchains/arm/bin/arm-linux-androideabi-gcc --sysroot=$ANDROID_NDK/platforms/android-21/arch-arm" ./b2 install --prefix=#{@build_dir}/natives/arm/`
  if $?.exitstatus == 0
    puts 'Build appears to have succeeded. Continuing.'
    #FileUtils.cp_r("#{@build_dir}/boost/build/include/", "#{@build_dir}/natives/arm/")
    #FileUtils.cp_r("#{@build_dir}/Boost-for-Android/build/lib/", "#{@build_dir}/natives/arm/")
    #FileUtils.ln_s("#{@build_dir}/natives/arm/include/boost-1_53/boost", "#{@build_dir}/natives/arm/include/boost", { force: true })
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
#build_OpenSSL()
build_boost()
#build_android_boost()
set_lock()

exit 0
