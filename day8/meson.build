project(
  'AocDay8',
  'cpp',
  version : '0.1',
  meson_version : '>= 1.3.0',
  default_options : ['warning_level=3', 'cpp_std=c++23'],
)

# Source files and headers
aoc_includes = include_directories('inc')

cpp_sourcefiles = files('src/solution.cpp')

# Main executable
aoclibs = subproject('aoclibs')
aoclibs_dep = aoclibs.get_variable('aoclibs_dep')
dependencies = [
  aoclibs_dep
]

exe = executable(
  'day8',
  'day8.cpp',
  cpp_sourcefiles,
  install : true,
  dependencies : dependencies,
  include_directories : aoc_includes,
)

run_target('run', command: exe)

# Test setup

# Setup Google test
gtest_proj = subproject(
  'gtest',
  default_options: ['warning_level=3', 'cpp_std=c++23']
)

gtest_dep = gtest_proj.get_variable('gtest_dep')
gtest_main = gtest_proj.get_variable('gtest_main_dep')

test_dependencies = [gtest_dep, gtest_main]

# Create Test executable
test_executable = executable(
  'day8_test',
  'tests.cpp',
  cpp_sourcefiles,
  dependencies : test_dependencies,
  include_directories : aoc_includes,
)

test('basic', test_executable, env : ['GTEST_COLOR=yes'])
