# Building for web

`emcc -o onda_cuerda.html onda_cuerda.c -Os -Wall ./web/libraylib.a -I./web/ -L./web/ -s USE_GLFW=3 -s ASYNCIFY --shell-file web/minshell.html -DPLATFORM_WEB`
