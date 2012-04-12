#!/usr/bin/ruby

require File.expand_path(ENV['MOSYNCDIR']+'/rules/exe.rb')

work = ExeWork.new
work.instance_eval do
	@SOURCES = ['.',
		'../../src/ThirdParty/CRC',
		'../../src/ThirdParty/LZSS',
	]
	@EXTRA_INCLUDES = ['.',
		'../../src/ThirdParty/CRC',
		'../../src/SDL',
		'../../src/ThirdParty/LZSS',
		#"#{mosync_include}/SDL",
		'/MinGW/include/SDL',
	]
	@EXTRA_SOURCEFILES = [
		'../../src/Game/BigFile.c',
	]
	@EXTRA_CFLAGS = ' -Wno-old-style-definition'
	@SPECIFIC_CFLAGS = {
		'lexer.c' => ' -Wno-unused-function',
	}
	@NAME = "biggie"
	@TARGETDIR = '.'
end

work.invoke
