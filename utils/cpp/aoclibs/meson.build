project(
  'aoclibs',
  'cpp',
  version : '0.1',
  meson_version : '>= 1.3.0',
  default_options : ['warning_level=3', 'cpp_std=c++14'],
)

dependencies = [
]

# These arguments are only used to build the shared library
# not the executables that use the library.
lib_args = ['-DBUILDING_AOCLIBS']

sources = [
  'aoclibs.cpp',
]

lib = library(
  'aoclibs',
  sources,
  install : true,
  cpp_shared_args : lib_args,
  gnu_symbol_visibility : 'hidden',
  dependencies : dependencies,
)

test_exe = executable(
  'aoclibs_test',
  'aoclibs_test.cpp',
  dependencies : dependencies,
  link_with : lib,
)
test('aoclibs', test_exe)

# Make this library usable as a Meson subproject.
aoclibs_dep = declare_dependency(
  include_directories : include_directories('.'),
  dependencies : dependencies,
  link_with : lib,
)
meson.override_dependency('aoclibs', aoclibs_dep)

# Make this library usable from the system's
# package manager.
install_headers('aoclibs.hpp', subdir : 'aoclibs')

pkg_mod = import('pkgconfig')
pkg_mod.generate(
  lib,
  description : 'Meson sample project.',
  subdirs : 'aoclibs',
)
