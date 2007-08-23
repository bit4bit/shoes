//
// main.c
// The generic launcher for Shoes.
//
#include <stdio.h>
#include "shoes/app.h"
#include "shoes/internal.h"

#ifdef SHOES_WIN32
int WINAPI
WinMain(HINSTANCE inst, HINSTANCE inst2, LPSTR arg, int style)
#else
int
main(argc, argv)
  int argc;
  char *argv[];
#endif
{
  shoes_init();
  shoes_app *app = shoes_app_new();
#ifdef SHOES_WIN32
  int argc;
  char **argv;
  app->kit.instance = inst;
  app->kit.style = style;
  app->path = SHOE_ALLOC_N(char, SHOES_BUFSIZE);
  argc = rb_w32_cmdvector(GetCommandLine(), &argv);
  GetModuleFileName(NULL, (LPSTR)app->path, SHOES_BUFSIZE);
#else
  app->path = argv[0];
#endif
  ruby_set_argv(argc - 1, &argv[1]);
  if (shoes_app_load(app) != SHOES_QUIT)
  {
    shoes_app_open(app);
    shoes_app_loop(app, "/");
    shoes_app_close(app);
  }
#ifdef SHOES_WIN32
  SHOE_FREE(app->path);
#endif
  shoes_app_free(app);
  return 0;
}
