#!/usr/bin/env python
import os, argparse, SCons

def printerr(string):
	print >> sys.stderr, string

#
# Define options
# Options are not exclusive - it will build everything you specify
#

def maxLen(list):
	lenmax = 0;
	for s in list:
		lenmax = max(len(s), lenmax)
	return lenmax

def makeFixed(list, maxlen):
	fixed = []
	for s in list:
		fixed.append(s.ljust(maxlen))
	return fixed

build_descriptions        = ["Debug"                 , "Distribution"             ]
build_defines             = ["HW_BUILD_FOR_DEBUGGING", "HW_BUILD_FOR_DISTRIBUTION"]
build_options             = ["debug"                 ,"release"                   ]
build_bits                = [1 << 0                  , 1 << 1                     ]
build_default             = 0
build_description_max_len = maxLen(build_descriptions)
build_descriptions_fixed  = makeFixed(build_descriptions, build_description_max_len)

bits_descriptions        = ["32-bit", "64-bit"  ]
bits_defines             = ["_X86"   , "_X86_64"]
bits_options             = ["32"    , "64"      ]
bits_bits                = [1 << 8  , 1 << 9    ]
bits_default             = 1
bits_description_max_len = maxLen(bits_descriptions)
bits_descriptions_fixed  = makeFixed(bits_descriptions, bits_description_max_len)

game_descriptions        = ["Normal"           , "Demo"        ]
game_defines             = ["HW_GAME_HOMEWORLD", "HW_GAME_DEMO"]
game_options             = ["game"             , "demo"        ]
game_bits                = [1 << 16            , 1 << 17       ]
game_default             = 0
game_description_max_len = maxLen(game_descriptions)
game_descriptions_fixed  = makeFixed(game_descriptions, game_description_max_len)

#FIXME: NPAPI is linux only for now!!
#FIXME: Android is ARM only for now!!
platform_descriptions        = ["NaCL"    , "LLVM"    , "NPAPI"     , "Android"    , "IOS"    ]
platform_defines             = ["__nacl__", "__llvm__", "__np_api__", "__android__", "__ios__"]
platform_options             = ["nacl"    , "llvm"    , "npapi"     , "android"    , "ios"    ]
platform_bits                = [1 << 24   , 1 << 25   , 1 << 26     , 1 << 27      , 1 << 28  ]
platform_default             = 2
platform_description_max_len = maxLen(platform_descriptions)
platform_descriptions_fixed  = makeFixed(platform_descriptions, platform_description_max_len)

gl_descriptions        = ["OpenGL"   , "OpenGL ES 1"                  , "OpenGL ES 2"                  ]
gl_defines             = ["HW_USE_GL", ["HW_USE_GLES", "HW_USE_GLES1"], ["HW_USE_GLES", "HW_USE_GLES2"]]
gl_options             = ["gl"       , "gles1"                        , "gles2"                        ]
gl_bits                = [1 << 32    , 1 << 33                        , 1 << 34                        ]
gl_default             = 2
gl_description_max_len = maxLen(gl_descriptions)
gl_descriptions_fixed  = makeFixed(gl_descriptions, gl_description_max_len)

#
# Parse options
#

parser = argparse.ArgumentParser(description='Add build variants')
options = [gl_bits[gl_default]]

for i in range(0, len(build_bits), 1):
	parser.add_argument(
		build_options[i],
		metavar = 'options',
		action  = 'append_const',
		const   = build_bits[i],
		help    = 'Add build of ' + build_descriptions[i]
	)

for i in range(0, len(game_bits), 1):
	parser.add_argument(
		game_options[i],
		metavar = 'options',
		action  = 'append_const',
		const   = game_bits[i],
		help    = 'Add build of variant ' + game_descriptions[i]
	)

for i in range(0, len(platform_bits), 1):
	parser.add_argument(
		platform_options[i],
		metavar = 'options',
		action  = 'append_const',
		const   = platform_bits[i],
		help    = 'Add build of platform ' + platform_descriptions[i]
	)

for i in range(0, len(bits_bits), 1):
	parser.add_argument(
		bits_options[i],
		metavar = 'options',
		action  = 'append_const',
		const   = bits_bits[i],
		help    = 'Build everything for ' + bits_descriptions[i]
	)

parser.parse_args()

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

option_bitmap = 0 #Make sure it can handle more than bits

def getBuildIndex():
	return (option_bitmap >> 0) & 0xFF

def getBitsIndex():
	return (option_bitmap >> 8) & 0xFF

def getGameIndex():
	return (option_bitmap >> 16) & 0xFF
	
def getPlatformIndex():
	return (option_bitmap >> 24) & 0xFF

def getGLIndex():
	return (option_bitmap >> 32) & 0xFF

def is_debug():
	return getBuildIndex() == 0

def is_release():
	return not is_debug()
	
def is_32():
	return getBitsIndex() == 0

def is_64():
	return not is_32()


def is_full():
	return getGameIndex() == 0

def is_demo():
	return not is_full()

def is_platform(name):
	return platform_options[getPlatformIndex()] == name

def is_nacl():
	return is_platform("nacl")

def is_llvm():
	return is_platform("llvm")

def is_npapi():
	return is_platform("npapi")

def is_android():
	return is_platform("android")

def is_ios():
	return is_platform("ios")

def is_gles2():
	return getGLIndex() == 2

option_env = defaultEnv.Clone()

def getOptionEnv():
	return option_env

def getOptionString():
	buildName    = build_options[getBuildIndex()]
	bitsName     = bits_options[getBitsIndex()]
	gameName     = game_options[getGameIndex()]
	platformName = platform_options[getPlatformIndex()]
	
	return "_" + buildName + "_" + gameName + "_" + platformName + "_" + bitsName

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

Export('defaultEnv', 'getOptionEnv', 'descend', 'topDir', 'addProgram', 'addLibrary', 'tools', 'is_nacl', "is_npapi", "is_android", "is_gles2")

descend(['tools'])

for i in range(0, len(build_bits), 1):
	idefine = build_defines[i]
	home_defines.add(idefine)

	for j in range(0, len(bits_bits), 1):
		jdefine = bits_defines[j]
		home_defines.add(jdefine)
		
		for k in range(0, len(game_bits), 1):
			kdefine = game_defines[k]
			home_defines.add(kdefine)
	
			for l in range(0, len(platform_bits), 1):
				ldefine = platform_defines[l]
				home_defines.add(ldefine)
	 			
				#
				# Print what we are doing
				#
				
				game_desc  = game_descriptions_fixed[k]
				build_desc = build_descriptions_fixed[i]
				plat_desc  = platform_descriptions_fixed[l]
				bit_desc   = bits_descriptions_fixed[j]
				gl_desc    = gl_descriptions_fixed[gl_default]
				
				print "Configuring build [" + build_desc + " | " + bit_desc  + " | " + game_desc + " | " + plat_desc + " | "+ gl_desc + "]"
				
				home_defines = home_defines.union(gl_defines[gl_default])

				option_bitmap = i << 0 | j << 8 | k << 16 | l << 24 | gl_default << 32
				
				buildDir = 'build/' + getOptionString()
				
				if is_android() or is_nacl() or is_npapi() or is_llvm():
					subdir = platform_options[l]
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
				
				home_defines = home_defines.difference(gl_defines[gl_default])
				home_defines.remove(ldefine)
			home_defines.remove(kdefine)
		home_defines.remove(jdefine)
	home_defines.remove(idefine)

#Depends(prog, tools)

#DEFAULT_TARGETS.append("")

