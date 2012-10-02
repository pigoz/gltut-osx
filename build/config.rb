require 'rake/clean'

class RukeConfig
  attr_accessor :compiler
end

module Ruke
  def self.config
    @config ||= RukeConfig.new
  end
end

Ruke.config.compiler ||= 'clang'

def compile_object(target, source)
  sh "#{Ruke.config.compiler} -c -o #{target} #{source}"
end

def compile_and_link_object(target, source, cflags)
  sh "#{Ruke.config.compiler} #{cflags} -o #{target} #{source}"
end

def frameworks(*fs)
  (['-framework'] * fs.size).zip(fs.map{|f| f.to_s}).join(' ')
end

def add_clean(binary)
  CLEAN.include('**/*.o')
  CLEAN.include(binary)
end

def build_recipe(name)
  task :default => [name] do
    sh "./#{name}"
  end

  add_clean(name)

  rule '.o' => '.m' do |t|
    compile_object(t.name, t.source)
  end
end

def target_objects(src_glob, deps_glob)
  srcs = FileList[src_glob]
  deps = deps_glob.map {|dg| FileList[dg]}
  deps.reduce(srcs.ext('o')) {|accu, el| accu + el.ext('o')}
end

def app_recipe(name, frameworks)
  cflags = frameworks(*frameworks)
  obj = target_objects('**/*.m', ['../framework/**/*.m'])
  build_recipe(name)

  file name => obj do
    compile_and_link_object(name, obj, cflags)
  end
end

def lib_recipe(name)
  build_recipe(name)
  obj = target_objects('**/*.m', [])
  file name => obj
end
