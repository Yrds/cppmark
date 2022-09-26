project('cppmark', 'cpp', version: '0.0.1', default_options: ['cpp_std=c++20'])

src = files(
  'src/cppmark.cpp'
  )

inc = include_directories('src')

libcppmark = library('cppmark', src, include_directories: inc)

libcppmark_dep = declare_dependency(include_directories: inc, link_with: libcppmark)

libut_subproj = subproject('ut')

spec_test = executable('spec_test', 'test/spec_test.cpp', dependencies: [libcppmark_dep, libut_subproj.get_variable('boostut_dep')])

test('spec test', spec_test)
