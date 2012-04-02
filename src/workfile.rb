#!/usr/bin/ruby

USE_NEWLIB = true

require File.expand_path(ENV['MOSYNCDIR']+'/rules/mosync_exe.rb')

sh 'cd c:/code/mosync-arm/libs/SDL/ && ruby workfile.rb USE_NEWLIB='

class KasTask < FileTask
	def initialize(work, srcTask)
		super(work, "Missions/Generated/#{File.basename(srcTask).noExt}.c")
		@kp = "Missions/Generated/#{File.basename(srcTask).noExt}.kp"
		@f = "Missions/Generated/#{File.basename(srcTask).noExt}.functions.c"
		@h = "Missions/Generated/#{File.basename(srcTask).noExt}.h"
		#@srcTask = srcTask
		@prerequisites << srcTask
	end
	def functions; @f; end
	def execute
		p = @prerequisites.join(' ')
		sh "gcc -E -x c -I Game #{p} > #{@kp}"
		sh "kas2c #{@kp} #{@NAME} #{@h} #{@f}"
	end
end

class GccWork
	# give C++ files different object names,
	# so they don't collide with our C files.
	def genfile(source, ending)
		if(source.to_s.getExt == '.c')
			return @BUILDDIR + File.basename(source.to_s).ext(ending)
		elsif(source.to_s.getExt == '.cpp')
			return @BUILDDIR + source.to_s.gsub('/','_') + ending
		else
			raise hell
		end
	end
end
class MoSyncArmExeWork
	alias :original_libTasks :libTasks
	def libTasks
		return [FileTask.new(self, "#{ARM_BASEDIR}/arm-elf/lib/libstdc++.a")] + original_libTasks
	end
end

work = PipeExeWork.new
work.instance_eval do
	incSrc = [
		'Ships',
		'Game',
		'SDL',
		'ThirdParty/CRC',
		'ThirdParty/LZSS',
	]
	@SOURCES = incSrc + [
		'GLES2/emul',
		'GLES2',
		'GLES1/emul',
		'mosync',
	]

	@EXTRA_INCLUDES = incSrc +
	[
		'.',
		'mosync',
		'c:/code/mosync-master/libs/SDL/include/',
	]
	@EXTRA_CFLAGS = ''+
		' -Wno-shadow'+
		' -Wno-strict-prototypes'+
		' -Wno-cast-qual'+
		' -Wno-missing-prototypes'+
		' -Wno-missing-declarations'+
		' -Wno-float-equal'+
		' -Wno-sign-compare'+
		' -Wno-unused-but-set-variable'+
		' -Wno-old-style-definition'+
		' -Wno-missing-format-attribute'+
		' -Wno-unused-variable'+
		' -Wno-parentheses'+
		' -Wno-declaration-after-statement'+
		' -include mosync/config.h'+
		''
	@SPECIFIC_CFLAGS = {
		'NetCheck.c' => ' -Wno-int-to-pointer-cast',
	}
	if(@GCC_IS_V4)
		@EXTRA_CFLAGS << ' -Wno-type-limits'
		@SPECIFIC_CFLAGS['SoundEvent.c'] = ' -Wno-logical-op'
		@SPECIFIC_CFLAGS['sstream.c'] = ' -Wno-pointer-sign'
	else
		@EXTRA_CFLAGS << ' -Wno-unreachable-code'
		@EXTRA_INCLUDES << ENV['MOSYNCDIR']+'/include/newlib/stlport'
	end
	@IGNORED_FILES = [
		'wave.c',
		'debugwnd.c',
		'KNITransform.c',
		'TitanInterfaceC.stub.c',
		'Matrix-mult.c',
	]
	@EXTRA_CPPFLAGS = ''+
		' -include mosync/config.h'+
		' -Wno-shadow'+
		' -Wno-unused-variable'+
		' -Wno-float-equal'+
		''

	@LIBRARIES = ['sdl']
	#@EXTRA_LINKFLAGS = " #{ARM_BASEDIR}/arm-elf/lib/libstdc++.a"

	@NAME = 'homeworld'

	@EXTRA_SOURCETASKS = []
	kasFiles = Dir['Missions/SinglePlayer/*.kas'] + Dir['Missions/Tutorials/*.kas']
	kasFiles.each do |file|
		k = KasTask.new(self, FileTask.new(self, file))
		@EXTRA_SOURCETASKS << k
		f = FileTask.new(self, k.functions)
		f.prerequisites << k
		@EXTRA_SOURCETASKS << f
	end
end

work.invoke
