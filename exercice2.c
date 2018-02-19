#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*EXERCICE 2*/

static unsigned int WINDOW_WIDTH = 400;
static unsigned int WINDOW_HEIGHT = 400;


/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

/*fonctions*/
void drawSquare();
void drawLandmark();
void drawCircle();
void draw();

void resize(int width , int height ){
  glViewport(0,0,width,height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-1,1.,-1.,1.);
  SDL_SetVideoMode(width,height,BIT_PER_PIXEL,SDL_OPENGL|SDL_RESIZABLE);
}



 
int main(int argc, char** argv) {
  int key=SDLK_l;


    /* Initialisation de la SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    
    /* Ouverture d'une fenêtre et création d'un contexte OpenGL */
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    
    /* Titre de la fenêtre */
    SDL_WM_SetCaption("CHANGEMENT DU TITRE :D", NULL);
    glClear(GL_COLOR_BUFFER_BIT);
    /* Boucle d'affichage */
    int loop = 1;
    while(loop) {

        /* Récupération du temps au début de la boucle */
        Uint32 startTime = SDL_GetTicks();
        
        /* Placer ici le code de dessin */
	//	glClear(GL_COLOR_BUFFER_BIT);

		   /* Echange du front et du back buffer : mise à jour de la fenêtre */
        SDL_GL_SwapBuffers();
    
        /* Boucle traitant les evenements */
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
	  

            /* L'utilisateur ferme la fenêtre : */
            if(e.type == SDL_QUIT) {
                loop = 0;
                break;
            }
            
            /* Quelques exemples de traitement d'evenements : */
            switch(e.type) {

                /* Clic souris */
                case SDL_MOUSEBUTTONUP:
		  draw(key);
		 
                    break;


	        /* Redimentionnement fenêtre */
	        
	        case SDL_VIDEORESIZE:
		  WINDOW_WIDTH = e.resize.w;
		  WINDOW_HEIGHT = e.resize.h;
		  resize(WINDOW_WIDTH,WINDOW_HEIGHT);
     
		  
		  break;
	      
	      
	     
                /* Touche clavier */
                case SDL_KEYDOWN:
		  key = e.key.keysym.sym;
		  /*Touche q pour quitter*/
		  if (e.key.keysym.sym == SDLK_q){
		    loop = 0;
		    break;
		  }
		 
		   printf("touche pressée (code = %d)\n", e.key.keysym.sym);
                    break;

                default:
                    break;
            }
        }

        /* Calcul du temps écoulé */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;

        /* Si trop peu de temps s'est écoulé, on met en pause le programme */
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
	   /* Echange du front et du back buffer : mise à jour de la fenêtre */
        SDL_GL_SwapBuffers();

    }

    /* Liberation des ressources associées à la SDL */ 
    SDL_Quit();

    return EXIT_SUCCESS;
}






void drawSquare(){
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,0);
  glBegin(GL_LINES);
  glVertex2f(-0.5,0.5);
  glVertex2f(0.5,0.5);
  glVertex2f(0.5,0.5);
  glVertex2f(0.5,-0.5);
  glVertex2f(0.5,-0.5);
  glVertex2f(-0.5,-0.5);
  glVertex2f(-0.5,-0.5);
  glVertex2f(-0.5,0.5);
  glEnd();
}

void drawLandmark(){
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,0);
  glColor3ub(255,0,0);
  glBegin(GL_LINES);
  glVertex2f(-0.5,0);
  glVertex2f(0.5,0);
  glEnd();
  glColor3ub(0,255,0);
  glBegin(GL_LINES);
  glVertex2f(0,0.5);
  glVertex2f(0,-0.5);
  glEnd();
}


void drawCircle(){
 SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,0);
 glBegin(GL_POINTS);
 for(int i=0;i<1000;++i)
  {
  glVertex2f(cos(2*3.14159*i/1000.0)*0.5,sin(2*3.14159*i/1000.0)*0.5);
  }
 glEnd();
}


void draw(int key){
 
  if (key == SDLK_s){
    drawSquare();
  }
  if (key == SDLK_l){
    drawLandmark();
  }
  if (key == SDLK_c){
    drawCircle();
  }
}

  
  
