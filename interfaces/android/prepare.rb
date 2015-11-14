#!/usr/bin/env ruby

require 'git'
require 'fileutils'

@build_dir = ARGV[0] || Dir.pwd

@build_api_level = 14
@build_targets = ["arm", "arm64", "x86", "x86_64"] #, "mips"]

puts "=== Preparing Android build dependencies"

def init()
  if @build_api_level < 21
    @build_targets = ["arm", "x86"] #, "mips"]
  end
end

def load_include_path(arch)
  "C_INCLUDE_PATH=#{@build_dir}/natives/include/#{arch}:$C_INCLUDE_PATH LD_LOAD_PATH=#{@build_dir}/natives/lib/#{arch}:$LD_LOAD_PATH CPPFLAGS=\"-I#{@build_dir}/natives/include/#{arch}\" LDFLAGS=\"-L#{@build_dir}/natives/lib/#{arch}\" "
end

def chain_env(arch)
  case arch
  when "arm"
    return "CC=\"#{@build_dir}/toolchains/arm/bin/arm-linux-androideabi-gcc --sysroot=$CRYSTAX_NDK/platforms/android-#{@build_api_level}/arch-arm\" "
  when "x86"
    return "CC=\"#{@build_dir}/toolchains/x86/bin/i686-linux-android-gcc --sysroot=$CRYSTAX_NDK/platforms/android-#{@build_api_level}/arch-x86\" "
  when "mips"
    return "CC=\"#{@build_dir}/toolchains/mips/bin/mipsel-linux-android-gcc --sysroot=$CRYSTAX_NDK/platforms/android-#{@build_api_level}/arch-mips\" "
  when "arm64"
    return "CC=\"#{@build_dir}/toolchains/arm64/bin/aarch64-linux-android-gcc --sysroot=$CRYSTAX_NDK/platforms/android-#{@build_api_level}/arch-arm64\" "
  when "x86_64"
    return "CC=\"#{@build_dir}/toolchains/x86_64/bin/x86_64-linux-android-gcc --sysroot=$CRYSTAX_NDK/platforms/android-#{@build_api_level}/arch-x86_64\" "
  end
end

def setup_paths()
  # base
  Dir.mkdir_p("#{@build_dir}/natives") unless File.exists? "#{@build_dir}/natives"

  # include
  Dir.mkdir("#{@build_dir}/natives/include") unless File.exists? "#{@build_dir}/natives/include"
  @build_targets.each do |target|
    Dir.mkdir("#{@build_dir}/natives/include/#{target}") unless File.exists? "#{@build_dir}/natives/include/#{target}"
  end

  # lib
  Dir.mkdir("#{@build_dir}/natives/lib") unless File.exists? "#{@build_dir}/natives/lib"
  @build_targets.each do |target|
    Dir.mkdir("#{@build_dir}/natives/lib/#{target}") unless File.exists? "#{@build_dir}/natives/lib/#{target}"
  end

  # bin
  Dir.mkdir("#{@build_dir}/natives/bin") unless File.exists? "#{@build_dir}/natives/bin"
  @build_targets.each do |target|
    Dir.mkdir("#{@build_dir}/natives/bin/#{target}") unless File.exists? "#{@build_dir}/natives/bin/#{target}"
  end

  # jumper links
  @build_targets.each do |target|
    Dir.mkdir("#{@build_dir}/natives/#{target}") unless File.exists? "#{@build_dir}/natives/#{target}"
    FileUtils.ln_s("#{@build_dir}/natives/bin/#{target}", "#{@build_dir}/natives/#{target}/bin")
    FileUtils.ln_s("#{@build_dir}/natives/include/#{target}", "#{@build_dir}/natives/#{target}/include")
    FileUtils.ln_s("#{@build_dir}/natives/lib/#{target}", "#{@build_dir}/natives/#{target}/lib")
  end
end

def full_env_override(arch)
  "#{load_include_path(arch)} #{chain_env(arch)}"
end

# Buld Chains
def prepare_chains()
  puts "== Preparing Android NDK Build Chains"
  @build_targets.each do |target|
    puts "= #{target}..."
    `$CRYSTAX_NDK/build/tools/make-standalone-toolchain.sh --platform=android-#{@build_api_level} --arch=#{target} --install-dir=#{@build_dir}/toolchains/#{target}` unless Dir.exists?("#{@build_dir}/toolchains/#{target}")
  end

  FileUtils.mkdir_p("#{@build_dir}/natives/lib")
  FileUtils.mkdir_p("#{@build_dir}/natives/include")
  FileUtils.mkdir_p("#{@build_dir}/natives")
  @build_targets.each do |target|
    FileUtils.mkdir_p("#{@build_dir}/natives/lib/#{target}")
  end
end


# OpenSSL
def build_OpenSSL()
  if Dir.exists? "#{@build_dir}/openssl"
    puts "OpenSSL repository found. Updating..."
    git = Git.open("#{@build_dir}/openssl")
    git.reset_hard("HEAD")
    git.clean({force: true, d: true, x:true})
    git.checkout("OpenSSL_1_0_2-stable")
    git.pull
    puts 'Updated.'
  else
    puts 'OpenSSL repository not found. Cloning...'
    git = Git.clone("https://github.com/openssl/openssl.git", "#{@build_dir}/openssl")
    git.checkout("OpenSSL_1_0_2-stable")
    puts 'Cloned.'
  end

  puts '== Building OpenSSL'
  Dir.chdir "#{@build_dir}/openssl"
  
  puts '= Building for arm'
  `make clean && make dclean`
  git.clean({force: true, d: true, x:true})
  `CC="#{@build_dir}/toolchains/arm/bin/arm-linux-androideabi-gcc --sysroot=$CRYSTAX_NDK/platforms/android-#{@build_api_level}/arch-arm" ./Configure android-armv7 shared threads no-asm && make`
  FileUtils.cp(Dir.glob("#{@build_dir}/openssl/libcrypto.so*"), "#{@build_dir}/natives/lib/arm")
  FileUtils.cp(Dir.glob("#{@build_dir}/openssl/libssl.so*"), "#{@build_dir}/natives/lib/arm")
  FileUtils.ln_s("#{@build_dir}/openssl/include/openssl", "#{@build_dir}/natives/include/openssl", { force: true })

  puts '= Building for x86'
  `make clean && make dclean`
  git.clean({force: true, d: true, x:true})
  `CC="#{@build_dir}/toolchains/x86/bin/i686-linux-android-gcc --sysroot=$CRYSTAX_NDK/platforms/android-#{@build_api_level}/arch-x86" ./Configure android-x86 shared threads no-asm && make`
  FileUtils.cp(Dir.glob("#{@build_dir}/openssl/libcrypto.so*"), "#{@build_dir}/natives/lib/x86")
  FileUtils.cp(Dir.glob("#{@build_dir}/openssl/libssl.so*"), "#{@build_dir}/natives/lib/x86")


  if @build_targets.include? 'mips'
    puts '= Building for mips'
    `make clean && make dclean`
    git.clean({force: true, d: true, x:true})
    `CC="#{@build_dir}/toolchains/mips/bin/mipsel-linux-android-gcc --sysroot=$CRYSTAX_NDK/platforms/android-#{@build_api_level}/arch-mips" ./Configure android-mips shared threads no-asm && make`
    FileUtils.cp(Dir.glob("#{@build_dir}/openssl/libcrypto.so*"), "#{@build_dir}/natives/lib/mips")
    FileUtils.cp(Dir.glob("#{@build_dir}/openssl/libssl.so*"), "#{@build_dir}/natives/lib/mips")
  end

  if @build_api_level > 20
    if @build_targets.include? 'arm64'
      puts '= Building for arm64'
      `make clean && make dclean`
      git.clean({force: true, d: true, x:true})
      `CC="#{@build_dir}/toolchains/arm64/bin/aarch64-linux-android-gcc --sysroot=$CRYSTAX_NDK/platforms/android-#{@build_api_level}/arch-arm64" ./Configure android shared threads no-asm && make`
      FileUtils.cp(Dir.glob("#{@build_dir}/openssl/libcrypto.so*"), "#{@build_dir}/natives/lib/arm64")
      FileUtils.cp(Dir.glob("#{@build_dir}/openssl/libssl.so*"), "#{@build_dir}/natives/lib/arm64")
    end

    if @build_targets.include? 'x86_64'
      puts '= Building for x86_64'
      `make clean && make dclean`
      git.clean({force: true, d: true, x:true})
      `CC="#{@build_dir}/toolchains/x86_64/bin/x86_64-linux-android-gcc --sysroot=$CRYSTAX_NDK/platforms/android-#{@build_api_level}/arch-x86_64" ./Configure android-x86 shared threads no-asm && make`
      FileUtils.cp(Dir.glob("#{@build_dir}/openssl/libcrypto.so*"), "#{@build_dir}/natives/lib/x86_64")
      FileUtils.cp(Dir.glob("#{@build_dir}/openssl/libssl.so*"), "#{@build_dir}/natives/lib/x86_64")
    end
  end

  Dir.chdir @build_dir
end

def build_curl()
  disable_lines = '--disable-ftp --disable-gopher --disable-file --disable-imap --disable-ldap ' +
    '--disable-ldaps --disable-pop3 --disable-proxy --disable-rtsp --disable-smtp ' +
    '--disable-telnet --disable-tftp --disable-libidn --disable-librtmp --disable-dict'
  if Dir.exists? "#{@build_dir}/curl"
    puts "CURL repository found. Updating..."
    git = Git.open("#{@build_dir}/curl")
    git.reset_hard("HEAD")
    git.clean({force: true, d: true, x:true})
    git.pull
    puts 'Updated.'
  else
    puts 'CURL repository not found. Cloning...'
    git = Git.clone("https://github.com/bagder/curl.git", "#{@build_dir}/curl")
    puts 'Cloned.'
  end

  puts '== Building CURL'
  Dir.chdir "#{@build_dir}/curl"
  
  puts '= Building for arm'
  `make clean && make dclean`
  git.clean({force: true, d: true, x:true})
  #puts "#{full_env_override('arm')} ./buildconf && ./configure --host=arm-linux-androideabi --with-openssl-includes=#{@build_dir}/natives/include/arm --with-openssl-libraries=#{@build_dir}/natives/lib/arm --prefix=#{@build_dir}/natives/arm #{disable_lines} && make && make install"
  `#{chain_env('arm')} LDFLAGS=\"-L#{@build_dir}/natives/lib/arm -lssl -lcrypto\" CFLAGS=\"-I#{@build_dir}/natives/include/arm \" ./buildconf`
  `#{chain_env('arm')} LDFLAGS=\"-L#{@build_dir}/natives/lib/arm -lssl -lcrypto\" CFLAGS=\"-I#{@build_dir}/natives/include/arm \" ./configure --host=arm-linux-androideabi --with-openssl-includes=#{@build_dir}/natives/include/arm --with-openssl-libraries=#{@build_dir}/natives/lib/arm --with-ssl --prefix=#{@build_dir}/natives/arm #{disable_lines} && make && make install`

 # puts '= Building for x86'
 # `make clean && make dclean`
 # git.clean({force: true, d: true, x:true})
 # `#{full_env_override('x86')} ./buildconf && ./configure --prefix=#{@build_dir}/natives/x86 && make && make install`

 # if @build_targets.include? 'mips'
 #   puts '= Building for mips'
 #   `make clean && make dclean`
 #   git.clean({force: true, d: true, x:true})
 #   `#{full_env_override('mips')} ./buildconf && ./configure --prefix=#{@build_dir}/natives/mips && make`
 # end

 # if @build_api_level > 20
 #   if @build_targets.include? 'arm64'
 #     puts '= Building for arm64'
 #     `make clean && make dclean`
 #     git.clean({force: true, d: true, x:true})
 #     `#{full_env_override('arm64')} ./buildconf && ./configure --prefix=#{@build_dir}/natives/arm64 && make`
 #   end
 # 
 #   if @build_targets.include? 'x86_64'
 #     puts '= Building for x86_64'
 #     `make clean && make dclean`
 #     git.clean({force: true, d: true, x:true})
 #     `#{full_env_override('x86_64')} ./buildconf && ./configure --prefix=#{@build_dir}/natives/x86_64 && make`
 #   end
 # end
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
  `./build-android.sh #{ENV['CRYSTAX_NDK']}`
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
  Dir.chdir "#{@build_dir}"
  if Dir.exists? "#{@build_dir}/boost"
    puts "Boost repository found. Moving to #{@build_dir}/boost"
    puts 'Updating...'
    Dir.chdir "#{@build_dir}/boost"
    `git pull`
    `git submodule update --recursive`
    puts 'Updated.'
  else
    puts 'Boost directory not found. Cloning...'
    git = Git.clone("https://github.com/boostorg/boost.git", "#{@build_dir}/boost")
    puts "Cloned. Moving to #{@build_dir}/boost"
    puts 'Obtaining submodules (this will take a long time)...'
    Dir.chdir "#{@build_dir}/boost"
    `git submodule init`
    `git submodule update --recursive`
  end

  puts 'Building Boost'
  Dir.chdir "#{@build_dir}/boost"
  puts "Moved to #{Dir.getwd}. Running build."
  `CC="#{@build_dir}/toolchains/arm/bin/arm-linux-androideabi-gcc --sysroot=$CRYSTAX_NDK/platforms/android-19/arch-arm" ./bootstrap.sh --without-libraries=python`
  `CC="#{@build_dir}/toolchains/arm/bin/arm-linux-androideabi-gcc --sysroot=$CRYSTAX_NDK/platforms/android-19/arch-arm" ./b2 headers`
  `CC="#{@build_dir}/toolchains/arm/bin/arm-linux-androideabi-gcc --sysroot=$CRYSTAX_NDK/platforms/android-19/arch-arm" ./b2`
  `CC="#{@build_dir}/toolchains/arm/bin/arm-linux-androideabi-gcc --sysroot=$CRYSTAX_NDK/platforms/android-19/arch-arm" ./b2 install --prefix=#{@build_dir}/natives/arm/`
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
  if ENV['CRYSTAX_NDK'] != nil && ENV['CRYSTAX_NDK'] != ""
    puts "CRYSTAX_NDK is set to: #{ENV['CRYSTAX_NDK']}"
  else
    puts "CRYSTAX_NDK is not set! You must set the CRYSTAX_NDK environment variable."
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

#check_lock()
init()
check_env()
setup_paths()
prepare_chains()
build_OpenSSL()
#build_boost()
build_curl()
#build_android_boost()
set_lock()

exit 0
