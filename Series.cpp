
#include <SDL2/SDL.h>
#include <stdio.h>
#include <cmath>

#include "Spinner.h"
#include "CircularBuffer.h"
#include "Helpers.h"
#include "Fourier.h"

void DrawCircle(SDL_Renderer *Renderer, int32_t _x, int32_t _y, int32_t radius)
{
   int32_t x = radius - 1;
   int32_t y = 0;
   int32_t tx = 1;
   int32_t ty = 1;
   int32_t err = tx - (radius << 1); // shifting bits left by 1 effectively
                                 // doubles the value. == tx - diameter
   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(Renderer, _x + x, _y - y);
      SDL_RenderDrawPoint(Renderer, _x + x, _y + y);
      SDL_RenderDrawPoint(Renderer, _x - x, _y - y);
      SDL_RenderDrawPoint(Renderer, _x - x, _y + y);
      SDL_RenderDrawPoint(Renderer, _x + y, _y - x);
      SDL_RenderDrawPoint(Renderer, _x + y, _y + x);
      SDL_RenderDrawPoint(Renderer, _x - y, _y - x);
      SDL_RenderDrawPoint(Renderer, _x - y, _y + x);

      if (err <= 0)
      {
         y++;
         err += ty;
         ty += 2;
      }
      if (err > 0)
      {
         x--;
         tx += 2;
         err += tx - (radius << 1);
      }
   }
}

const int winWidth = 800;
const int winHeight = 600;
const char* title = "Fourier Spinners! - 5th Prototype";

SDL_Window* disp;
SDL_Renderer* renderer;
SDL_Surface* waveCanvas; // surface on which to draw the scrolling waveform.
bool running;

bool init(){
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("SDL_Init err: %s\n", SDL_GetError());
		return false;
	}
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	// vvv disables the X11 window-manager compositing.
	// No compositing = no extra GPU work = better performance
	// (but also weird things switching in and out of window focus)

#ifdef BYPASS_WM_COMP
	SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");
#endif
	disp = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, winWidth, winHeight, SDL_WINDOW_SHOWN);
	if(disp == NULL){
		printf("Error creating SDL_Window disp! It is NULL -- %s\n", SDL_GetError());
		return false;
	}
	renderer = SDL_CreateRenderer(disp, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL){
		printf("Error creating SDL_Renderer renderer! It is NULL -- %s\n", SDL_GetError());
		return false;
	}
	waveCanvas = SDL_CreateRGBSurface(0, winWidth, winHeight, 32, 0, 0, 0, 0);
	if(waveCanvas == NULL){
		printf("Error creating SDL_Surface waveCanvas! It is NULL -- %s\n", SDL_GetError());
		return false;
	}
	return true;
}

// gracefully release all system resources before exiting.
// (Especially important for SDL_Textures on the GPU)
void close(){
	printf("Freeing wave surface...\n");
	SDL_FreeSurface(waveCanvas);
	printf("Freed!\n");

	printf("Destroying renderer...\n");
	SDL_DestroyRenderer(renderer);
	printf("Destroyed!\n");

	printf("Destroying window...\n");
	SDL_DestroyWindow(disp);
	printf("Destroyed!\n");

	printf("setting handles to NULL...");
	renderer = NULL;
	disp = NULL;
	waveCanvas = NULL;
	printf("NULL'd!\n");
	printf("Quitting SDL...\n");
	SDL_Quit();
	printf("DONE!\n");
}

int main(int argc, char* argv[]){
	if(!init()){
		printf("A fatal init error has occurred");
		return -1;
	}
	running = true;
	SDL_Event e;
	CircularBuffer traceBuffer = CircularBuffer(1000); // points drawn by the epicycles
	CircularBuffer drawing = CircularBuffer(1000); // points drawn by the user

	#define DFT_DEPTH 1000 // the number of epicycles the discrete Fourier transform will produce
	printf("creating chains\n");
	Chain chains[2] = {
			Chain(DFT_DEPTH, Spinner(0, 0, 0)),
			Chain(DFT_DEPTH, Spinner(0, 0, 0))
	};
	// CREATE INPUT SIGNALS
	int sigLen = 1000;
	Point2D sig[sigLen] = {};
	for(int i = 0; i < sigLen; i++){
		double theta = (2*M_PI)*(double)i/sigLen;
		double x = 100*(theta - M_PI);
		double y = 100*sin(theta);
		sig[i] = { x, y };
//		printf("input signal: (%f, %f)\n", x, y);
	}
	printf("Performing transform...\n");
	createDFT(chains, sig, sigLen, DFT_DEPTH);

	// this spinner acts as a position vector for anchoring
	//all the actual spinners to a point that isn't (0,0)
	chains[0].anchor = Spinner::fromCartesian(winWidth/2, 100);
	chains[1].anchor = Spinner::fromCartesian(100, winHeight/2);
	printf("Anchors set. Starting main loop!\n");
	bool isDrawing = false;
	while(running){
		while(SDL_PollEvent(&e)){
			switch(e.type){
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYUP:
				//exit on key release (not key press)
				switch(e.key.keysym.sym){
				case SDLK_ESCAPE:
				case SDLK_q:
					running = false;
					break;
				case SDLK_SPACE:
					// USE DRAWN LINE AS PATH FOR DFT
					createDFT(chains, drawing.data_mut(), drawing.size(), DFT_DEPTH);
					break;
				};
				break;
			case SDL_MOUSEBUTTONDOWN:
				if(e.button.button == SDL_BUTTON_LEFT){
//					printf("Mouse down\n");
//					printf("Was Drawing? %d\n", isDrawing);
					isDrawing = isDrawing ? false : true;
//					printf("Now Drawing? %d\n", isDrawing);
				}else if(e.button.button == SDL_BUTTON_RIGHT){
					SDL_WarpMouseInWindow(disp, drawing.peek().x, drawing.peek().y);
				}
				break;
			case SDL_MOUSEBUTTONUP:
//				printf("Mouse up\n");
//				isDrawing = false;
//				printf("Drawing? %d\n", isDrawing);
				break;
			case SDL_MOUSEMOTION:
				if(isDrawing){
					Point2D p;
					p.x = e.button.x;
					p.y = e.button.y;
//					printf("tracePoint: %d, %d\n", (int)p.x, (int)p.y);
					drawing.push(p);
				}
				break;
			default:
//				printf("Recv evt! : %d\n", e.type);
				break;
			};
		}

		//clear screen on update
		SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderClear(renderer);

		Spinner offset = Spinner(0, 0); // start offset at origin (uses Spinner because the operators are overloaded for convenience)
		Point2D tracePoint; // the convergence of each set of spinners. This is where the next dot will be drawn
		Point2D antiTracePoint; // the vertical & horizontal position for the start of each intersection arms -- like the tracePoint, but holds the opposite variable: instead keeps y-val from horizChain, and x-val from vertiChain
		offset = chains[1].anchor; // move draw point to that of the anchor
		for(int i = 0; i < chains[1].chainLength; i++){
			//draw spinner circles]
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
			DrawCircle(renderer, offset.getX(), offset.getY(), chains[1].spinners[i].rho);
			// draw spinner vector lines (relative to previous vector -- relative to the "offset" spinner)
			SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderDrawLine(renderer,
					(int)(offset.getX()),
					(int)(offset.getY()),
					(int)(offset.getX() + chains[1].spinners[i].getX()),
					(int)(offset.getY() + chains[1].spinners[i].getY())
			);
			offset = offset+chains[1].spinners[i];
		}
		tracePoint.y = offset.getY();
		antiTracePoint.x = offset.getX();
		offset = chains[0].anchor;

		for(int i = 0; i < chains[0].chainLength; i++){
			//draw spinner circles
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
			DrawCircle(renderer, offset.getX(), offset.getY(), chains[0].spinners[i].rho);
			// draw spinner vector lines (relative to previous vector -- relative to the "offset" spinner)
			SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderDrawLine(renderer,
					(int)(offset.getX()),
					(int)(offset.getY()),
					(int)(offset.getX() + chains[0].spinners[i].getX()),
					(int)(offset.getY() + chains[0].spinners[i].getY())
			);
			offset = offset+chains[0].spinners[i];
		}
		antiTracePoint.y = offset.getY();
		tracePoint.x = offset.getX(); // add x-component to the new point
		traceBuffer.push(tracePoint); // push the point into the ring buffer

		//RENDER TRACE POINTS
		//TODO: consider using (sp)lines for particularly sparse areas
		char blue = 0;
		char notBlue = 0;
		SDL_SetRenderDrawColor(renderer, notBlue, notBlue, blue, 0xFF);
		Point2D p2;
		Point2D prev = traceBuffer.pop();
		for(int i = 1; i < traceBuffer.size(); i++){
			p2 = traceBuffer.pop();
			if(!(p2.x < 0 || p2.y < 0 || prev.x < 0 || prev.y < 0)){
				SDL_SetRenderDrawColor(renderer, notBlue, notBlue, blue, 0xFF);
				SDL_RenderDrawLine(renderer,
						(int)prev.x,
						(int)prev.y,
						(int)p2.x,
						(int)p2.y);
			}
			prev = p2;
			notBlue = 1024*i/traceBuffer.size();
		}

		// RENDER INTERSECTION ARMS
		SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderDrawLine(renderer, (int)tracePoint.x, (int)antiTracePoint.y, (int)tracePoint.x, (int)tracePoint.y);
		SDL_RenderDrawLine(renderer, (int)antiTracePoint.x, (int)tracePoint.y, (int)tracePoint.x, (int)tracePoint.y);


		// RENDER USER DRAWING
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
		prev = drawing.pop();
		for(int i = 1; i < drawing.size(); i++){
			p2 = drawing.pop();
			if(!(p2.x < 0 || p2.y < 0 || prev.x < 0 || prev.y < 0)){
				SDL_RenderDrawLine(renderer,
						(int)prev.x,
						(int)prev.y,
						(int)p2.x,
						(int)p2.y);
			}
			prev = p2;
		}

		SDL_RenderPresent(renderer);

		// move the things for the next cycle
		for(int i = 0; i < chains[1].chainLength; i++){
			chains[1].spinners[i].theta +=  chains[1].spinners[i].freq * 2*M_PI / sigLen;
		}
		for(int i = 0; i < chains[0].chainLength; i++){
			chains[0].spinners[i].theta +=  chains[0].spinners[i].freq * 2*M_PI / sigLen;
		}
		SDL_Delay(16);
	}
	close();
	return 0;
}
