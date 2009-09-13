SDL = require('sdl');
SDL.init(SDL.INIT_VIDEO);
var surface = SDL.setVideoMode(640, 480, 16, SDL.SDL_SWSURFACE);
var image = SDL.loadBMP("/tmp/flusspferd-logo.bmp");
SDL.blitSurface(image, surface);
SDL.updateRect(surface, 0, 0, image.w, image.h);
SDL.freeSurface(image);
// ...
SDL.quit();
quit();
