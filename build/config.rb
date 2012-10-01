require 'rake/clean'

def frameworks(*fs)
  (['-framework'] * fs.size).zip(fs.map{|f| f.to_s}).join(' ')
end

def app_recipe(context, name, *frameworks)
  context.instance_eval do
    cc = 'clang'
    cflags = frameworks(*frameworks)

    CLEAN.include('*.o')
    CLEAN.include(name)

    task :default => [name]

    src = FileList['**/*.m']
    framework = FileList['../framework/**/*.m']
    obj = src.ext('o') + framework.ext('o')

    rule '.o' => '.m' do |t|
      sh "#{cc} -c -o #{t.name} #{t.source}"
    end

    file name => obj do
      sh "#{cc} #{cflags} -o #{name} #{obj}"
    end
  end
end

def lib_recipe(context, name)
  context.instance_eval do
    cc = 'clang'
    CLEAN.include('**/*.o')
    CLEAN.include(name)

    task :default => [name]

    src = FileList['**/*.m']
    obj = src.ext('o')

    rule '.o' => '.m' do |t|
      sh "#{cc} -c -o #{t.name} #{t.source}"
    end

    file name => obj

    file 'framework.o' => FileList['gui/*.m']
  end
end
