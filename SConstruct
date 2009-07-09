# inspired from http://www.scons.org/wiki/SimultaneousVariantBuilds

release_env = Environment(CCFLAGS = ['-O2'])
debug_env = release_env.Clone(CCFLAGS = ['-g'])

SConscript('src/SConscript', build_dir='release', exports={'env':release_env})
SConscript('src/SConscript', build_dir='debug', exports={'env':debug_env})

