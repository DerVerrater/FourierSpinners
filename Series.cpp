
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
const char* title = "Fourier Spinners! - 3nd Prototype";

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

//gracefully release all system resources before exiting. (Especially important for SDL_Surfaces on the GPU)
void close(){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(disp);
	SDL_FreeSurface(waveCanvas);
	renderer = NULL;
	disp = NULL;
	waveCanvas = NULL;
	SDL_Quit();
}

int main(){
	if(!init()){
		printf("A fatal init error has occurred");
		return -1;
	}
	running = true;
	SDL_Event e;
	CircularBuffer traceBuffer = CircularBuffer(1000); // points drawn by the epicycles
	CircularBuffer drawing = CircularBuffer(1000); // points drawn by the user


	#define DFT_DEPTH 50  // the number of epicycles the discrete Fourier transform will produce
	// CREATE vertiChain INPUT SIGNAL
	int sigLen = 100;
	Point2D sig[sigLen] = {};
	printf("Created Point2D array\n");
	for(int i = 0; i < sigLen; i++){
		sig[i] = {(double)(i + 100.0), (double)i};
	}
	Chain vertiChain = *Fourier::createDFT(sig, sigLen, DFT_DEPTH);

	// CREATE horizChain INPUT SIGNAL
	int sig2Len = 250;
	Point2D sig2[sig2Len];
	for(int i = 0; i < sig2Len/2; i++){
		sig2[i] = {i, 200.0};
	}
	for(int i = sig2Len/2; i < sig2Len; i++){
		sig2[i] = {i, 100.0};
	}
	Chain horizChain =  *Fourier::createDFT(sig2, sig2Len, DFT_DEPTH);// Chain(horizLength, Spinner::fromCartesian(winWidth/2, winHeight/4));
	for(int i = 0; i < horizChain.chainLength; i++){
		horizChain.spinners[i].theta -= M_PI/2;
	}


	// this spinner acts as a position vector for anchoring
	//all the actual spinners to a point that isn't (0,0)
	vertiChain.anchor = Spinner::fromCartesian(winWidth/2, 0);
	horizChain.anchor = Spinner::fromCartesian(0, winHeight/2);

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
				case SDLK_SPACE:
					// USE DRAWN LINE AS PATH FOR DFT
					vertiChain = *Fourier::createDFT(drawing.data, drawing.size, DFT_DEPTH);
					Point2D swaps[drawing.size]; // swap x & y positions.
					for(int i = 0; i < drawing.size; i++){
						swaps[i] = {drawing.data[i].y, drawing.data[i].x};
					}
					horizChain = *Fourier::createDFT(swaps, drawing.size, DFT_DEPTH);
					for(int i = 0; i < horizChain.chainLength; i++){
							horizChain.spinners[i].theta -= M_PI/2;
					}
					break;
				};
			case SDL_MOUSEBUTTONDOWN:
				if(e.button.button == SDL_BUTTON_LEFT){
					printf("Mouse down\n");
					printf("Was Drawing? %d\n", isDrawing);
					isDrawing = isDrawing ? false : true;
					printf("Now Drawing? %d\n", isDrawing);
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
					printf("tracePoint: %d, %d\n", (int)p.x, (int)p.y);
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

		offset = vertiChain.anchor; // move draw point to that of the anchor
		for(int i = 0; i < vertiChain.chainLength; i++){
			//draw spinner circles
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
			DrawCircle(renderer, offset.getX(), offset.getY(), vertiChain.spinners[i].rho);
			// draw spinner vector lines (relative to previous vector -- relative to the "offset" spinner)
			SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderDrawLine(renderer,
					(int)(offset.getX()),
					(int)(offset.getY()),
					(int)(offset.getX() + vertiChain.spinners[i].getX()),
					(int)(offset.getY() + vertiChain.spinners[i].getY())
			);
			offset = offset+vertiChain.spinners[i];
		}
		tracePoint.y = offset.getY();

		offset = horizChain.anchor;
		for(int i = 0; i < horizChain.chainLength; i++){
			//draw spinner circles
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
			DrawCircle(renderer, offset.getX(), offset.getY(), horizChain.spinners[i].rho);
			// draw spinner vector lines (relative to previous vector -- relative to the "offset" spinner)
			SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderDrawLine(renderer,
					(int)(offset.getX()),
					(int)(offset.getY()),
					(int)(offset.getX() + horizChain.spinners[i].getX()),
					(int)(offset.getY() + horizChain.spinners[i].getY())
			);
			offset = offset+horizChain.spinners[i];
		}
		tracePoint.x = offset.getX(); // add x-component to the new point
		traceBuffer.push(tracePoint); // push the point into the ring buffer

		//RENDER TRACE POINTS
		//TODO: consider using splines for particularly sparse areas
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
		Point2D p2;
		Point2D prev = traceBuffer.pop();
		for(int i = 1; i < traceBuffer.size; i++){
			p2 = traceBuffer.pop();
			if(!(p2.x < 0 || p2.y < 0 || prev.x < 0 || prev.y < 0)){
				SDL_RenderDrawLine(renderer,
						(int)prev.x,
						(int)prev.y,
						(int)p2.x,
						(int)p2.y);
			}
			prev = p2;
		}


		// RENDER USER DRAWING
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
		prev = drawing.pop();
		for(int i = 1; i < drawing.size; i++){
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
		for(int i = 0; i < vertiChain.chainLength; i++){
			vertiChain.spinners[i].theta += vertiChain.spinners[i].freq * 0.1 * (M_PI/DFT_DEPTH);
		}
		for(int i = 0; i < horizChain.chainLength; i++){
			horizChain.spinners[i].theta += horizChain.spinners[i].freq * 0.1 * (M_PI/DFT_DEPTH);
		}
		SDL_Delay(16);
	}
	close();
	return 0;
}
