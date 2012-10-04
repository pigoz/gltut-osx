require 'rake/clean'

CC  ||= 'clang'
CPP ||= 'clang++'

def compile_object(target, source, compiler=CC)
  if compiler == CC
    sh "#{compiler} -c -o #{target} #{source}"
  else
    sh "#{compiler} -std=c++0x -stdlib=libc++ -c -o #{target} #{source}"
  end
end

def link_object(target, source, cflags, compiler=CC)
  if compiler == CC
    sh "#{compiler} #{cflags} -o #{target} #{source}"
  else
    sh "#{compiler} -stdlib=libc++ #{cflags} -o #{target} #{source}"
  end
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

  rule '.o' => '.cpp' do |t|
    compile_object(t.name, t.source, CPP)
  end
end

def target_objects(src_glob, deps_glob)
  srcs = FileList[src_glob]
  deps = deps_glob.map {|dg| FileList[dg]}
  deps.reduce(srcs.ext('o')) {|accu, el| accu + el.ext('o')}
end

def app_recipe(name, frameworks)
  cflags = frameworks(*frameworks)
  obj = target_objects(['**/*.m', '**/*.cpp'],
                       ['../framework/**/*.m', '../framework/**/*.cpp'])
  build_recipe(name)

  file name => obj do
    link_object(name, obj, cflags, CPP)
  end
  file name => obj
end

def lib_recipe(name)
  build_recipe(name)
  obj = target_objects(['**/*.m', '**/*.cpp'], [])
  file name => obj
end
