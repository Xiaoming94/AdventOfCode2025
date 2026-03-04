project(
  'aoclibs',
  'cpp',
  version : '0.1',
  meson_version : '>= 1.3.0',
  default_options : ['warning_level=3', 'cpp_std=c++23'],
)

dependencies = [
]

# These arguments are only used to build the shared library
# not the executables that use the library.
lib_args = ['-DBUILDING_AOCLIBS']

sources = files('src/aoclibs.cpp')

exports = include_directories('exports')

lib = library(
  'aoclibs',
  sources,
  install : true,
  include_directories: exports,
  cpp_shared_args : lib_args,
  gnu_symbol_visibility : 'hidden',
  dependencies : dependencies,
)

# Setup GTest
gtest_proj = subproject(
  'gtest',
  default_options: ['warning_level=3', 'cpp_std=c++23']
)

gtest_dep = gtest_proj.get_variable('gtest_dep')
gtest_main = gtest_proj.get_variable('gtest_main_dep')
gmock_dep = gtest_proj.get_variable('gmock_dep')
gmock_main = gtest_proj.get_variable('gmock_main_dep')

test_dependencies = [gtest_dep, gtest_main, gmock_dep, gmock_main]

test_exe = executable(
  'aoclibs_test',
  'aoclibs_test.cpp',
  include_directories: exports,
  dependencies : test_dependencies,
  link_with : lib,
)

test('aoclibs', test_exe, env : ['GTEST_COLOR=yes'])

# Make this library usable as a Meson subproject.
aoclibs_dep = declare_dependency(
  include_directories : exports,
  dependencies : dependencies,
  link_with : lib,
)
meson.override_dependency('aoclibs', aoclibs_dep)

# Make this library usable from the system's
# package manager.
install_headers('exports/aoclibs.h', subdir : 'aoclibs')

pkg_mod = import('pkgconfig')
pkg_mod.generate(
  lib,
  description : 'Meson sample project.',
  subdirs : 'aoclibs',
)
