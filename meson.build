project('fucks_given', 'c')

gnome = import('gnome')
deps = [dependency('gtk4'),dependency('libadwaita-1'),dependency('sqlite3')]
cflags = [ '-Wall', '-Wextra', '-Wpedantic', '-Werror' ]

blueprints = custom_target('blueprints',
  input: files(
    # LIST YOUR BLUEPRINT FILES HERE
    'src/my-window.blp',
  ),
  output: '.',
  command: [find_program('blueprint-compiler'), 'batch-compile', '@OUTPUT@', '@CURRENT_SOURCE_DIR@', '@INPUT@'],
)

resources = gnome.compile_resources('resources', 'src/resources.xml', dependencies: blueprints)

executable('fucks_given', 'src/main.c', 'src/my-app.c', 'src/my-window.c', resources, c_args: [], dependencies: deps)
