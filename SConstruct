#!/usr/bin/env python
import os, argparse, SCons

def printerr(string):
	print >> sys.stderr, string

#
# Define options
# Options are not exclusive - it will build everything you specify
#

def enumerate_bits(bits):
	add = 0
	for i in range(len(bits)):
		bits[i] += add
		add += 1
class Options:
	class OptionItem:
		def __init__(self, NAME, BIT, DESCRIPTION=None, DEFINES=[]):
			self.name = NAME
			self.bit = BIT
			self.description = DESCRIPTION
			
			if type(DEFINES) is str:
				self.defines = [DEFINES]
			else:
				self.defines = DEFINES
	
	def makeFixedDescription(self, list, maxlen):
		for item in list:
			item.fixed = item.description.ljust(maxlen)
	
	def maxDescriptionLen(self, list):
		lenmax = 0;
		for item in list:
			if isinstance(item, self.OptionItem):
				desc = item.description
			else:
				desc = item
			
			lenmax = max(len(desc), lenmax)
		
		return lenmax

	def __init__(self, SHIFT, NAMES, DESCRIPTIONS=[], DEFINES=[], DEFAULT = 0):
		self.items = []
		for i in range(len(NAMES)):
			try:
				description = DESCRIPTIONS[i]
			except:
				description = None
			
			try:
				define      = DEFINES[i]
			except:
				define      = None
			
			item = self.OptionItem(
				NAME        = NAMES[i],
				DESCRIPTION = description,
				DEFINES     = define,
				BIT         = SHIFT + i
			)
			
			self.items.append(item)
		
		max_len = self.maxDescriptionLen(self.items)
		self.makeFixedDescription(self.items, max_len)
		
platform_shift =  0
bits_shift     =  8
build_shift    = 16
game_shift     = 24
gl_shift       = 32

option_shift = [
	platform_shift,
	bits_shift,
	build_shift,
	game_shift,
	gl_shift,
]

options = [
	#FIXME: NPAPI is linux only for now!!
	Options(
		SHIFT        = 1 << platform_shift,
		DESCRIPTIONS = ["NaCL"    , "JavaScript"    , "Android"    , "IOS"    ],
		DEFINES      = ["__nacl__", "__emscripten__", "__android__", "__ios__"],
		NAMES        = ["nacl"    , "emsc"          , "android"    , "ios"    ]
	),
	Options(
		SHIFT        = 1 << bits_shift,
		DESCRIPTIONS = ["32-bit", "64-bit" , "ARM", "ARM v7a"],
		DEFINES      = ["_X86"  , "_X86_64", "ARM", "ARM7"   ],
		NAMES        = ["32"    , "64"     , "arm", "armv7"  ]
	),
	Options(
		SHIFT        = 1 << build_shift,
		DESCRIPTIONS = ["Debug"                 , "Distribution"             ],
		DEFINES      = ["HW_BUILD_FOR_DEBUGGING", "HW_BUILD_FOR_DISTRIBUTION"],
		NAMES        = ["debug"                 , "release"                  ]
	),
	Options(
		SHIFT        = 1 << game_shift,
		DESCRIPTIONS = ["Normal"           , "Demo"        ],
		DEFINES      = ["HW_GAME_HOMEWORLD", "HW_GAME_DEMO"],
		NAMES        = ["game"             , "demo"        ]
	),
	Options(
		SHIFT        = 1 << gl_shift,
		DESCRIPTIONS = ["OpenGL"   , "OpenGL ES 1"                  , "OpenGL ES 2"                  ],
		DEFINES      = ["HW_USE_GL", ["HW_USE_GLES", "HW_USE_GLES1"], ["HW_USE_GLES", "HW_USE_GLES2"]],
		NAMES        = ["gl"       , "gles1"                        , "gles2"                        ]
	)
]

platform_index = 0
bit_index      = 1
build_index    = 2
game_index     = 3
gl_index       = 4

# The configuration has to match the upper indexes!
configurations = [
	['android', '32'   , 'debug', 'game', 'gles2'],
	['android', 'arm'  , 'debug', 'game', 'gles2'],
	['android', 'armv7', 'debug', 'game', 'gles2'],
	['android', '32'   , 'debug', 'game', 'gles1'],
	['android', 'arm'  , 'debug', 'game', 'gles1'],
	['android', 'armv7', 'debug', 'game', 'gles1'],
	['emsc'   , None   , 'debug', 'game', 'gles2']
]

def getOption(index, name):
	for item in options[index].items:
		if item.name == name:
			return item
	return None
#
# Map names to options (strong typeing)
#
for configuration in configurations:
	for i in range(len(configuration)):
		configuration[i] = getOption(i, configuration[i])

#
# Parse options
#

'''
parser = argparse.ArgumentParser(description='Add build variants')
set_options = []

for option in options:
	for item in option.items:
		parser.add_argument(
			item.name,
			metavar = 'set_options',
			action  = 'append_const',
			const   = item.bit,
			help    = 'Add build of ' + item.description
		)

parser.parse_args()
'''
#
# Check which bits were set
#

#option_set = set(options)

#if option_set.isdisjoint(build_bits):
#	options.append(build_bits[build_default])

#if option_set.isdisjoint(game_bits):
#	options.append(game_bits[game_default])

#if option_set.isdisjoint(platform_bits):
#	options.append(platform_bits[platform_default])

#if option_set.isdisjoint(bits_bits):
#	options.append(bits_bits[bits_default])

home_defines = set(["HW_ENABLE_MOVIES", "_LINUX_FIX_ME", "_REENTRANT", "GENERIC_ETGCALLFUNCTION"])
#"HW_ENABLE_GLES2", "LLVM", "__native_client__", "HOME_BUILD_NPAPI"]

tools = []
libs = []

topDir = Dir('#')

defaultEnv = Environment()

def descend(subdirs, exports=[]):
	
#	if type(subdirs) is str:
#		subdirs += '/SConstruct'
#	else:
#		for i in range( 0, subdirs.__len__(), 1 ):
#			subdirs[i] += '/SConstruct'
	return SConscript(dirs=subdirs, exports=exports)

#conf = Configure(env)

defaultEnv.AppendUnique(CFLAGS="-std=gnu99")
defaultEnv.AppendUnique(CCFLAGS=["-Wall", "-Wstrict-aliasing", "-Wextra", "-Werror=uninitialized", "-Werror=trigraphs", "-Werror=init-self", "-Werror=format", "-Werror=format-security", "-Werror=implicit", "-Werror=sequence-point"]) # -O2 -S
defaultEnv.AppendUnique(CXXFLAGS="-std=gnu++0x")
defaultEnv.CacheDir("cache")

#env.ParseConfig('pkg-config libavcodec --cflags --libs')
#env.ParseConfig('pkg-config libavformat --cflags --libs')
#env.ParseConfig('pkg-config glesv2 --cflags --libs')
#env.ParseConfig('pkg-config glesv1_cm --cflags --libs')

#napath = "/home/andreas/Projects/native_client_sdk_0_5_1026/toolchain/linux_x86/x86_64-nacl/"

#env.Append(CPPPATH=[
	#napath + "include",
	#napath + "include/c++/4.4.3"
#])

#env.Append(CPPDEFINES=defi)

#top_srcdir = ".."
#env.Append(CPPPATH=["/usr/include/x86_64-linux-gnu", "/usr/include/GLES2"])


#Export("includedirs")

current = list(configurations[0])

def is_equal(val1, val2):
	eq = val1 == val2
	
	if not eq and (val1 == None or val2 == None):
		return False
	
	return eq

def is_name(val1, val2):
	if val1 == None and val2 != None:
		return False
	return is_equal(val1.name, val2)

def is_build(NAME):
	return is_name(current[build_index], NAME)

def is_debug():
	return is_build('debug')

def is_release():
	return is_build('release')

def is_bits(NAME):
	return is_name(current[bit_index], NAME)

def is_32():
	return is_bits('32')

def is_64():
	return is_bits('64')

def is_arm():
	return is_bits('arm')

def is_armv7():
	return is_bits('armv7')

def is_game(NAME):
	return is_name(current[game_index], NAME)

def is_full():
	return is_game('game')

def is_demo():
	return is_game('demo')

def is_platform(NAME):
	return is_name(current[platform_index], NAME)

def is_nacl():
	return is_platform("nacl")

def is_emsc():
	return is_platform("js")

def is_android():
	return is_platform("android")

def is_ios():
	return is_platform("ios")

def is_gl(NAME = None):
	if NAME == None:
		return is_gl('gl')
	
	return is_name(current[gl_index], NAME)

def is_gles1():
	return is_gl('gles1')

def is_gles2():
	return is_gl('gles2')

option_env = defaultEnv.Clone()

def getOptionEnv():
	return option_env

def append_underscore(buf, val):
	if val is None:
		return buf

	if len(buf) == 0:
		return val.name
	
	return buf + '_' + val.name

def getOptionString():

	out = ''

	out = append_underscore(out, current[build_index]   )
	out = append_underscore(out, current[game_index]    )
	out = append_underscore(out, current[platform_index])
	out = append_underscore(out, current[bit_index]     )
	out = append_underscore(out, current[gl_index]      )
	
	return out

def addLibrary(target, source, ignored = [], env = None, addPaths = [], LIBS = [], LIBPATH = []):

	if env is None:
		env = getOptionEnv()

	if type(source) is str:
			source = [source]

	validSources = []

	for s in source:
		valid = True
		for ign in ignored:
			if SCons.Util.is_String(s):
				if s == ign:
					valid = False
					break
					
			elif s.name == ign:
				valid = False
				break
	
		if valid:
			validSources.append(s);
			
	env.AppendUnique(CPPPATH=addPaths)
	slib = env.Library(
		target,# + getOptionString(),
		validSources,
		LIBS = LIBS,
		LIBPATH = LIBPATH
	)
	
	for n in slib:
		libs.append(n)
	
	return slib

def addProgram(target, source, env = None, LIBS=[], LIBPATH=[]):

	if env is None:
		env = getOptionEnv()
	
	#env.AppendUnique(CPPPATH=addPaths)
	#name = target + getOptionString()
	
	#if type(source) is str:
	#	source = [source]
	
	#object_files = []
	
	# This is necessary because SCons is too dumb to recognize Variant usage
	# So targets have to globally unique
	#for s in source:
	#	object_files = env.Object('foo-opt', s)

	return env.Program(
		target,
		source = source,
		LIBS = LIBS,
		LIBPATH = LIBPATH
	)
#end addProgram

Export('defaultEnv', 'getOptionEnv', 'descend', 'topDir', 'addProgram', 'addLibrary', 'tools', 'is_nacl', 'is_llvm', 'is_android', 'is_gles2', 'is_gles1')

descend(['tools'])

# build all configurations
for configuration in configurations:

	for i in range(len(configuration)):
		opt = configuration[i]
		# Add defines
		current[i] = opt
		
		if not opt is None:
			home_defines = home_defines.union(opt.defines)
	
	#
	# Print what we are doing
	#
	def joinFixed(seper, seq):
		joinseq = []
		for opt in seq:
			if not opt is None:
				joinseq.append(opt.fixed)
		return " | ".join(joinseq)

	desc = joinFixed(" | ", tuple(current))
	print "Configuring build [" + desc + "]"
	
	buildDir = getOptionString()
	
	if buildDir != None:
		buildDir = 'build/' + buildDir
		
		if is_android() or is_nacl() or is_npapi() or is_llvm():
			subdir = current[platform_index].name
		elif is_ios():
			subdir = ""
		else:
			raise EnvironmentError
	
		option_env = defaultEnv.Clone()
		option_env.AppendUnique(CPPDEFINES = list(home_defines))
	
		if len(subdir) != 0:
			#option_env.VariantDir(buildDir,  subdir, duplicate = 0)

			#subdir = buildDir + "/" + subdir
		
			# TODO find a way to remove duplicates
			SConscript(dirs=subdir, variant_dir=buildDir, src_dir=subdir, duplicate=1)
			#descend(subdir)

	# Remove defines again
	for opt in configuration:
		if not opt is None:
			home_defines = home_defines.difference(opt.defines)

#Depends(prog, tools)

#DEFAULT_TARGETS.append("")

