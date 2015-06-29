Gem::Specification.new do |s|
  s.name        = 'libemojidex'
  s.version     = '0.0.1'
  s.license     = 'emojiOL'
  s.summary     = 'emojidex libraries for using and interfacing with the emojidex service'
  s.description = 'emojidex emoji lookup, indexing, searching, login, account info, history, ' \
                  'favorites, etc.'
  s.authors     = ['Rei Kagetsuki']
  s.email       = 'info@emojidex.com'
  s.files       = ['ext/libemojidex/emojidexRUBY_wrap.cxx']
  s.require_paths = ['lib']
  s.homepage    = 'http://developer.emojidex.com'

  s.extensions = ['ext/libemojidex/extconf.rb']
end
