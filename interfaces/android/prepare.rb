#!/usr/bin/env ruby

require 'git'
require 'fileutils'

@build_dir = ARGV[0] || Dir.pwd

@build_api_level = 16
@build_targets = ["arm", "arm64", "x86", "x86_64"] #, "mips"]

puts "=== Preparing Android build dependencies"

def init()
  if @build_api_level < 21
    @build_targets = ["arm", "x86"] #, "mips"]
  end

  FileUtils.mkdir_p("#{@build_dir}") unless File.exists? "#{@build_dir}"
  Dir.chdir(@build_dir)
  @build_dir = Dir.pwd
end

def load_include_path(arch)
  "C_INCLUDE_PATH=#{@build_dir}/natives/include/#{arch}:$C_INCLUDE_PATH LD_LOAD_PATH=#{@build_dir}/natives/lib/#{arch}:$LD_LOAD_PATH CPPFLAGS=\"-I#{@build_dir}/natives/include/#{arch}\" LDFLAGS=\"-L#{@build_dir}/natives/lib/#{arch}\" "
end

def chain_env(arch)
  case arch
  when "arm"
    return "CC=\"#{@build_dir}/toolchains/arm/bin/arm-linux-androideabi-gcc --sysroot=$CRYSTAX_NDK/platforms/android-#{@build_api_level}/arch-arm\" LD=#{@build_dir}/toolchains/arm/bin/arm-linux-androideabi-ld AR=#{@build_dir}/toolchains/arm/bin/arm-linux-androideabi-ar RANLIB=#{@build_dir}/toolchains/arm/bin/arm-linux-androideabi-ranlib STRIP=#{@build_dir}/toolchains/arm/bin/arm-linux-androideabi-strip "
  when "x86"
    return "CC=\"#{@build_dir}/toolchains/x86/bin/i686-linux-android-gcc --sysroot=$CRYSTAX_NDK/platforms/android-#{@build_api_level}/arch-x86\" LD=#{@build_dir}/toolchains/x86/bin/i686-linux-android-ld AR=#{@build_dir}/toolchains/x86/bin/i686-linux-android-ar RANLIB=#{@build_dir}/toolchains/x86/bin/i686-linux-android-ranlib STRIP=#{@build_dir}/toolchains/x86/bin/i686-linux-android-strip "
  when "mips"
    return "CC=\"#{@build_dir}/toolchains/mips/bin/mipsel-linux-android-gcc --sysroot=$CRYSTAX_NDK/platforms/android-#{@build_api_level}/arch-mips\" LD=#{@build_dir}/toolchains/mips/bin/mipsel-linux-android-ld AR=#{@build_dir}/toolchains/mips/bin/mipsel-linux-android-ar RANLIB=#{@build_dir}/toolchains/mips/bin/mipsel-linux-android-ranlib STRIP=#{@build_dir}/toolchains/mips/bin/mipsel-linux-android-strip "
  when "arm64"
    return "CC=\"#{@build_dir}/toolchains/arm64/bin/aarch64-linux-android-gcc --sysroot=$CRYSTAX_NDK/platforms/android-#{@build_api_level}/arch-arm64\" LD=#{@build_dir}/toolchains/arm64/bin/aarch64-linux-android-ld AR=#{@build_dir}/toolchains/arm64/bin/aarch64-linux-android-ar RANLIB=#{@build_dir}/toolchains/arm64/bin/aarch64-linux-android-ranlib STRIP=#{@build_dir}/toolchains/arm64/bin/aarch64-linux-android-strip "
  when "x86_64"
    return "CC=\"#{@build_dir}/toolchains/x86_64/bin/x86_64-linux-android-gcc --sysroot=$CRYSTAX_NDK/platforms/android-#{@build_api_level}/arch-x86_64\" LD=#{@build_dir}/toolchains/x86_64/bin/x86_64-linux-android-ld AR=#{@build_dir}/toolchains/x86_64/bin/x86_64-linux-android-ar RANLIB=#{@build_dir}/toolchains/x86_64/bin/x86_64-linux-android-ranlib STRIP=#{@build_dir}/toolchains/x86_64/bin/x86_64-linux-android-strip "
  end
end

def setup_paths()
  # base
  Dir.mkdir("#{@build_dir}/natives") unless File.exists? "#{@build_dir}/natives"

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
    FileUtils.ln_s("#{@build_dir}/natives/bin/#{target}", "#{@build_dir}/natives/#{target}/bin") unless File.exists? "#{@build_dir}/natives/#{target}/bin"
    FileUtils.ln_s("#{@build_dir}/natives/include/#{target}", "#{@build_dir}/natives/#{target}/include") unless File.exists? "#{@build_dir}/natives/#{target}/include"
    FileUtils.ln_s("#{@build_dir}/natives/lib/#{target}", "#{@build_dir}/natives/#{target}/lib") unless File.exists? "#{@build_dir}/natives/#{target}/lib"
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
    Dir.chdir "#{@build_dir}/openssl"
    `git reset HEAD --hard`
    `git clean -fdx`
    puts 'Updated.'
  else
    puts 'OpenSSL repository not found. Cloning...'
    Dir.chdir "#{@build_dir}"
    `git clone https://github.com/openssl/openssl.git openssl`
    puts 'Cloned.'
  end

  Dir.chdir "#{@build_dir}/openssl"
  `git checkout OpenSSL_1_1_0-stable`
  `git pull`

  puts '== Building OpenSSL'

  puts '= Building for arm'
  `git clean -fdx`
  `#{chain_env('arm')} ./Configure --prefix=#{@build_dir}/natives/arm/ --sysroot=$CRYSTAX_NDK/platforms/android-#{@build_api_level}/arch-arm android-armeabi shared threads no-asm; make; make install`

  puts '= Building for x86'
  `git clean -fdx`
  `#{chain_env('x86')} ./Configure --prefix=#{@build_dir}/natives/x86/ --sysroot=$CRYSTAX_NDK/platforms/android-#{@build_api_level}/arch-x86 android-x86 shared threads no-asm; make; make install`

  if @build_targets.include? 'mips'
    puts '= Building for mips'
    `git clean -fdx`
    `#{chain_env('mips')} ./Configure --prefix=#{@build_dir}/natives/mips/ --sysroot=$CRYSTAX_NDK/platforms/android-#{@build_api_level}/arch-mips android-mips shared threads no-asm; make; make install`
  end

  if @build_api_level > 20
    if @build_targets.include? 'arm64'
      puts '= Building for arm64'
      `git clean -fdx`
      `#{chain_env('arm64')} ./Configure --prefix=#{@build_dir}/natives/arm64/ --sysroot=$CRYSTAX_NDK/platforms/android-#{@build_api_level}/arch-arm64 android64 shared threads no-asm; make; make install`
    end

    if @build_targets.include? 'x86_64'
      puts '= Building for x86_64'
      `git clean -fdx`
      `#{chain_env('x86_64')} ./Configure --prefix=#{@build_dir}/natives/x86_64/ --sysroot=$CRYSTAX_NDK/platforms/android-#{@build_api_level}/arch-x86_64 android-x86 shared threads no-asm; make; make install`
    end
  end

  Dir.chdir @build_dir
end

def build_curl()
  disable_lines = '--disable-ftp --disable-gopher --disable-file --disable-imap --disable-ldap ' +
    '--disable-ldaps --disable-pop3 --disable-proxy --disable-rtsp --disable-smtp ' +
    '--disable-telnet --disable-tftp --without-libidn --without-librtmp --disable-dict'
  if Dir.exists? "#{@build_dir}/curl"
    puts "CURL repository found. Updating..."
    git = Git.open("#{@build_dir}/curl")
    git.reset_hard("HEAD")
    git.clean({force: true, d: true, x:true})
    git.pull
    puts 'Updated.'
  else
    puts 'CURL repository not found. Cloning...'
    git = Git.clone("https://github.com/curl/curl.git", "#{@build_dir}/curl")
    puts 'Cloned.'
  end

  puts '== Building CURL'
  Dir.chdir "#{@build_dir}/curl"

  puts '= Building for arm'
  `git clean -fdx`
  `#{chain_env('arm')} LDFLAGS=\"-L#{@build_dir}/natives/lib/arm -lssl -lcrypto\" CFLAGS=\"-I#{@build_dir}/natives/include/arm \" ./buildconf`
  `#{chain_env('arm')} LDFLAGS=\"-L#{@build_dir}/natives/lib/arm -lssl -lcrypto\" CFLAGS=\"-I#{@build_dir}/natives/include/arm \" ./configure --host=arm-linux-androideabi --with-openssl-includes=#{@build_dir}/natives/include/arm --with-openssl-libraries=#{@build_dir}/natives/lib/arm --with-ssl --prefix=#{@build_dir}/natives/arm/ #{disable_lines} && make && make install`

  puts '= Building for x86'
  `git clean -fdx`
  `#{chain_env('x86')} LDFLAGS=\"-L#{@build_dir}/natives/lib/x86 -lssl -lcrypto\" CFLAGS=\"-I#{@build_dir}/natives/include/x86 \" ./buildconf`
  `#{chain_env('x86')} LDFLAGS=\"-L#{@build_dir}/natives/lib/x86 -lssl -lcrypto\" CFLAGS=\"-I#{@build_dir}/natives/include/x86 \" ./configure --host=x86-linux-android --with-openssl-includes=#{@build_dir}/natives/include/x86 --with-openssl-libraries=#{@build_dir}/natives/lib/x86 --with-ssl --prefix=#{@build_dir}/natives/x86/ #{disable_lines} && make && make install`

  if @build_targets.include? 'mips'
    puts '= Building for mips'
    `git clean -fdx`
    `#{chain_env('mips')} LDFLAGS=\"-L#{@build_dir}/natives/lib/mips -lssl -lcrypto\" CFLAGS=\"-I#{@build_dir}/natives/include/mips \" ./buildconf`
    `#{chain_env('mips')} LDFLAGS=\"-L#{@build_dir}/natives/lib/mips -lssl -lcrypto\" CFLAGS=\"-I#{@build_dir}/natives/include/mips \" ./configure --host=mips-linux-androideabi --with-openssl-includes=#{@build_dir}/natives/include/mips --with-openssl-libraries=#{@build_dir}/natives/lib/mips --with-ssl --prefix=#{@build_dir}/natives/mips/ #{disable_lines} && make && make install`
  end

  if @build_api_level > 20
    if @build_targets.include? 'arm64'
      puts '= Building for arm64'
      `git clean -fdx`
      `#{chain_env('arm64')} LDFLAGS=\"-L#{@build_dir}/natives/lib/arm64 -lssl -lcrypto\" CFLAGS=\"-I#{@build_dir}/natives/include/arm64 \" ./buildconf`
      `#{chain_env('arm64')} LDFLAGS=\"-L#{@build_dir}/natives/lib/arm64 -lssl -lcrypto\" CFLAGS=\"-I#{@build_dir}/natives/include/arm64 \" ./configure --host=arm64-linux-androideabi --with-openssl-includes=#{@build_dir}/natives/include/arm64 --with-openssl-libraries=#{@build_dir}/natives/lib/arm64 --with-ssl --prefix=#{@build_dir}/natives/arm64/ #{disable_lines} && make && make install`
    end

    if @build_targets.include? 'x86_64'
      puts '= Building for x86_64'
      `git clean -fdx`
      `#{chain_env('x86_64')} LDFLAGS=\"-L#{@build_dir}/natives/lib/x86_64 -lssl -lcrypto\" CFLAGS=\"-I#{@build_dir}/natives/include/x86_64 \" ./buildconf`
      `#{chain_env('x86_64')} LDFLAGS=\"-L#{@build_dir}/natives/lib/x86_64 -lssl -lcrypto\" CFLAGS=\"-I#{@build_dir}/natives/include/x86_64 \" ./configure --host=x86-linux-android --with-openssl-includes=#{@build_dir}/natives/include/x86_64 --with-openssl-libraries=#{@build_dir}/natives/lib/x86_64 --with-ssl --prefix=#{@build_dir}/natives/x86_64/ #{disable_lines} && make && make install`
    end
  end
end

def build_msgpack()
  # disable_lines = '--disable-ftp --disable-gopher --disable-file --disable-imap --disable-ldap ' +
  #   '--disable-ldaps --disable-pop3 --disable-proxy --disable-rtsp --disable-smtp ' +
  #   '--disable-telnet --disable-tftp --without-libidn --without-librtmp --disable-dict'
  if Dir.exists? "#{@build_dir}/msgpack"
    puts "msgpack repository found. Updating..."
    git = Git.open("#{@build_dir}/msgpack")
    git.clean({force: true, d: true, x:true})
    git.checkout 'master'
    git.pull
    puts 'Updated.'
  else
    puts 'msgpack repository not found. Cloning...'
    git = Git.clone("https://github.com/msgpack/msgpack-c.git", "#{@build_dir}/msgpack")
    puts 'Cloned.'
  end

  puts '== Building msgpack'
  Dir.chdir "#{@build_dir}/msgpack"

  puts '= Building for arm'
  git.clean({force: true, d: true, x:true})
  `#{chain_env('arm')} cmake -DMSGPACK_ENABLE_SHARED=ON -DMSGPACK_ENABLE_CXX=ON -DMSGPACK_BOOST=ON -DMSGPACK_CXX11=ON -DMSGPACK_BUILD_EXAMPLES=OFF -DCMAKE_INSTALL_PREFIX=#{@build_dir}/natives/arm/ .`
  `#{chain_env('arm')} make`
  `#{chain_env('arm')} make install`

  puts '= Building for x86'
  git.clean({force: true, d: true, x:true})
  `#{chain_env('x86')} cmake -DMSGPACK_ENABLE_SHARED=ON -DMSGPACK_ENABLE_CXX=ON -DMSGPACK_BOOST=ON -DMSGPACK_CXX11=ON -DMSGPACK_BUILD_EXAMPLES=OFF -DCMAKE_INSTALL_PREFIX=#{@build_dir}/natives/x86/ .`
  `#{chain_env('x86')} make`
  `#{chain_env('x86')} make install`
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

check_lock()

init()
check_env()
setup_paths()
prepare_chains()

build_OpenSSL()
build_curl()
build_msgpack()

set_lock()

exit 0
