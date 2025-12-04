project(
  'day3',
  'cpp',
  version : '0.1',
  meson_version : '>= 1.3.0',
  default_options : ['warning_level=3', 'cpp_std=c++23'],
)

aoc_includes = include_directories('inc')

dependencies = [
]

exe = executable(
  'day3',
  'day3.cpp',
  install : true,
  dependencies : dependencies,
)

gtest_proj = subproject(
  'gtest',
  default_options: ['warning_level=3', 'cpp_std=c++23']
)

gtest_dep = gtest_proj.get_variable('gtest_dep')
gtest_main = gtest_proj.get_variable('gtest_main_dep')

test_executable = executable(
  'day3_test',
  'tests.cpp',
  dependencies: [ gtest_dep, gtest_main ],
  include_directories: aoc_includes
)

test('basic', test_executable)
