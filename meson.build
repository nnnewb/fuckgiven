project('fucks_given', 'c')

gnome = import('gnome')
deps = [dependency('gtk4'), dependency('libadwaita-1'), dependency('sqlite3')]
cflags = ['-Wall', '-Wextra', '-Wpedantic', '-Werror', '-DG_LOG_DOMAIN="fucks-given"']

blueprints = custom_target(
  'blueprints',
  input : files(
    # LIST YOUR BLUEPRINT FILES HERE
    'src/my-window.blp',
    'src/my-fuck.blp',
  ),
  output : '.',
  command : [
    find_program('blueprint-compiler'),
    'batch-compile',
    '@OUTPUT@',
    '@CURRENT_SOURCE_DIR@',
    '@INPUT@',
  ],
)

resources = gnome.compile_resources('resources', 'src/resources.xml', dependencies : blueprints)

executable(
  'fucks_given',
  'src/main.c',
  'src/my-app.c',
  'src/my-window.c',
  'src/my-fuck.c',
  'src/my-storage.c',
  resources,
  c_args : cflags,
  dependencies : deps,
)
