project('fucks_given', 'c')

gnome = import('gnome')
deps = [dependency('gtk4'),dependency('libadwaita-1')]
cflags = [ '-Wall', '-Wextra', '-Wpedantic', '-Werror' ]
resources = gnome.compile_resources('resources', 'src/resources.xml', source_dir: 'src')

executable('fucks_given', 'src/main.c', 'src/my-app.c', 'src/my-window.c', resources, c_args: [], dependencies: deps)
