#!/usr/bin/ruby

require File.expand_path(ENV['MOSYNCDIR']+'/rules/exe.rb')

class LexTask < FileTask
	def initialize(work, srcTask)
		super(work, "build/#{File.basename(srcTask).noExt}.c")
		@prerequisites << srcTask
	end
	def execute
		sh "flex -i -o#{@NAME} #{@prerequisites.join(' ')}"
	end
end

class YaccTask < FileTask
	def initialize(work, srcTask)
		super(work, "build/#{File.basename(srcTask).noExt}.c")
		@prerequisites << srcTask
	end
	def execute
		sh "bison -d -o #{@NAME} #{@prerequisites.join(' ')}"
	end
end

work = ExeWork.new
work.instance_eval do
	@SOURCES = ['.']
	@EXTRA_INCLUDES = ['.']
	@EXTRA_SOURCETASKS = [
		LexTask.new(self, FileTask.new(self, 'lexer.l')),
		YaccTask.new(self, FileTask.new(self, 'parser.y')),
	]
	@SPECIFIC_CFLAGS = {
		'lexer.c' => ' -Wno-unused-function',
	}
	@NAME = "kas2c"
	@TARGETDIR = '.'
end

work.invoke
