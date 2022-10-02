#!/usr/bin/env python

from waflib.TaskGen import feature, after_method

def options(opt):
	pass

def configure(conf):
	noexceptions = {
		'default': ['-fno-exceptions']
	}
	conf.env.append_unique('CXXFLAGS', conf.get_flags_by_compiler(noexceptions, conf.env.COMPILER_CC))

	if conf.env.DEST_OS != 'android':
		if conf.env.cxxshlib_PATTERN.startswith('lib'):
			conf.env.cxxshlib_PATTERN = conf.env.cxxshlib_PATTERN[3:]

def build(bld):
	if bld.env.DEST_OS == 'win32':
		platform = 'win32'
	elif bld.env.DEST_OS == 'darwin':
		platform = 'apple'
	else:
		platform = 'posix'

	bld.shlib(
		source   = bld.path.ant_glob([
			'miniutl/utlmemory.cpp',
			'miniutl/strtools.cpp',
			'src/vgui/*.cpp',
			'src/platform/%s/*.cpp' % platform
		]),
		target   = 'vgui',
		features = 'cxx',
		includes = 'miniutl/ include/',
		export_includes = 'include/',
		rpath    = '$ORIGIN',
		install_path = bld.env.LIBDIR,
		subsystem = bld.env.MSVC_SUBSYSTEM
	)
